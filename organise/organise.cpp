#include <cstdio>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <vector>

/*******************************************************
* Compile this with these flags :-std=c++17 -lstdc++fs *
********************************************************/

const std::string DELIMITER = "/";

/**
    Function to create a directory.
    @param t_folder The folder name that you want.
    @return void.
*/
void createDirectory(std::string t_folder);

/**
    Function to move a file to a specified directory.
    @param t_filename The filename that you want to move.
    @param t_folder The folder that you want to move the file to.
    @return void.
*/
void moveFile(std::string t_filename, std::string t_folder);

/**
    Function to check if a folder already exists.
    @param t_folder The name of the folder that you want to check exists.
    @return bool True if folder exists, false if the folder doesn't exist.
*/
bool checkFolderExists(std::string t_folder);

/**
    Function to get the extension of a file.
    @param t_filename The filename that you want to get the extension of.
    @return string The extension of the file.
*/
std::string getFileExtension(std::string t_filename);

/**
    Function to get a vector of all files in a directory.
    @param t_directory A string of the path you want to get the files of.
    @return vector A vector of all the files in the directory.
*/
std::vector<std::string> getFilesInFolder(std::string t_directory);

/**
    Function to get the relative path of a given file.
    @param t_absolutePath A string of the absolute path.
    @return string A string of the relative path.
*/
std::string getRelativePath(std::string t_absolutePath);

/**
    Function to organise the current directory.
    @param t_directory the directory you want to organise.
    @return void.
*/
void organise(std::string t_directory);

int main(int argc, char* argv[])
{	
    // Call the organise method on the current directory. 
    organise(".");
	return 0;
}

void createDirectory(std::string t_folder)
{
    try
    {
        // Create a directory with a name of the folder variable.
        std::filesystem::create_directory(t_folder);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        // If it cannot create a directory it prints an error.
        std::perror("");
    }
}

void moveFile(std::string t_filename, std::string t_folder)
{
    // Create a new destination string with the folder included.
    std::string destination = t_folder + DELIMITER + t_filename;
    try
    {
        // Move the file.
        std::filesystem::rename(t_filename, destination);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        // If it cannot move the file it prints an error.
        std::perror("");
    }
}

bool checkFolderExists(std::string t_folder)
{
    if ( !std::filesystem::exists(t_folder) )
    {
        // If the folder does not exist, return false.
        return false;
    }
    else 
    {
        // If the folder does exist, return true.
        return true;
    }
}

std::string getFileExtension(std::string t_filename)
{
    // Get the index of where the last period is, where the extension starts.
    int position = t_filename.find_last_of(".");
    // Get the substring one of the index one after the final period.
    std::string extension = t_filename.substr(position+1);
    return extension;
}

std::string getRelativePath(std::string t_absolutePath)
{
    // The code in here is very similar to the getFileExtension method.
    int position = t_absolutePath.find_last_of(DELIMITER);
    std::string relativePath = t_absolutePath.substr(position+1);
    return relativePath;
}

std::vector<std::string> getFilesInFolder(std::string t_directory)
{
    std::vector<std::string> result;
    std::filesystem::path absolutePath;
    std::string absolutePathString, fileString;
    // Loop through the files in the given directory.
    for (auto& entry : std::filesystem::directory_iterator(t_directory))
    {
        // Convert from std::filesystem::directory_entry to string.
        absolutePath = std::filesystem::absolute(entry.path());
        absolutePathString = absolutePath.string();
        fileString = getRelativePath(absolutePathString);
        // If the file is not a normal file, ignore it.
        if (!entry.is_regular_file()) continue;
        // If the file is the same as the executeable, ignore it.
        if (fileString == "organise") continue;
        // If the relative path does not have a period in it, ignore it.
        if (fileString.find('.') == std::string::npos) continue;
        result.push_back(fileString);
    }
    return result;
}

void organise(std::string t_directory)
{
    std::vector<std::string> files = getFilesInFolder(t_directory);
    std::string extension;
    // Loop through the vector files.
    for ( std::string file : files )
    {
        // Get the extension of the file within the files vector.
        extension = getFileExtension(file);
        // Check if the folder that it must go in to exists, if not, create it.
        if (!checkFolderExists(extension))
        {
            createDirectory(extension);
        }
        // The file is always moved regardless of the creation of the directory.
        moveFile(file, extension);
    }
}
