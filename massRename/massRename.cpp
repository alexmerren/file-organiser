#include <vector> 
#include <iostream> 
#include <chrono> 
#include <cstdio>
#include <cstring>

/**
    Splits the input string into the individual files.
    @param filesString A string of files delimited by a comma. 
    @return A vector of all the file names.
*/
std::vector<std::string> listFiles(std::string filesString); 

/**
    Renames the files given by the listFiles function.
    @param inputs A vector of the existing file names in the directory. 
    @param outputs A vector of the wanted file names in the directory.
    @param print Boolean of whether to print diagnostics of the function.
    @return void
*/
void renameFiles(std::vector<std::string> inputs, std::vector<std::string> outputs, bool print);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::printf("Please enter a file name.\n");
        return 1;
    }

    int start = 1;
    bool verbose = false;
    
    if ((strcmp(argv[1],"-v")) == 0) 
    {
        start = 2;
        verbose = true;
    }
    
    std::vector<std::string> inputs = listFiles(argv[start]); 
    std::vector<std::string> outputs = listFiles(argv[start+1]); 
    renameFiles(inputs, outputs, verbose);
    return 0;
}

std::vector<std::string> listFiles(std::string t_filesString) 
{
	// This is the array of all the files we are returning.
	std::vector<std::string> filesArr; 
	std::string file; 
	std::string delimiter = ","; 
	int pos = 0;

	while ((pos = t_filesString.find(delimiter)) != std::string::npos) 
	{
		file = t_filesString.substr(0,pos); 
		filesArr.push_back(file);
		t_filesString.erase(0, pos + delimiter.length()); 
	}
	filesArr.push_back(t_filesString); 
	return filesArr;
}

void renameFiles(std::vector<std::string> t_inputs, std::vector<std::string> t_outputs, bool t_print)
{
	try
    {
        // Get the first element in the t_inputs and t_outputs vectors.
		auto inputsBegin = t_inputs.cbegin(); 
		auto outputsBegin = t_outputs.cbegin(); 
		// This starts the timing clock.
		auto start = std::chrono::high_resolution_clock::now(); 
        // This for loop goes through the input and t_outputs vectors, and renames them.
		for (; inputsBegin != t_inputs.end() and outputsBegin != t_outputs.end(); inputsBegin++, outputsBegin++ ) 
		{
			// Convert std::string to const char*
			const char* inputsBeginChar = inputsBegin->c_str(); 
		    const char* outputsBeginChar = outputsBegin->c_str(); 
            try 
            {
                std::rename(inputsBeginChar, outputsBeginChar);
				if (t_print)
                {
                    std::printf("%s -> %s\n", inputsBeginChar, outputsBeginChar);  
                }
            }
            catch (const std::exception& e)
            {
                std::perror("");
            }
        }
		auto finish = std::chrono::high_resolution_clock::now(); 
		std::chrono::duration<double> elapsed = finish - start; 
        if (t_print) 
        {
		    std::printf( "Renaming took %f seconds.\n", elapsed.count() ); 
        }
    }
    catch (const std::exception& e) 
    {	
		std::printf("");
	}
}
