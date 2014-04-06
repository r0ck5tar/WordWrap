#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std; 

static const int max_width = 76;

/*
 * This program takes the text of the paragraphs in the given text file, wraps it
 * and the wrapped text to an output file.
 *
 * Usage: WordWrap [path_to_file]
 * Prerequisites: The text file given must contain unwrapped paragraphs (i.e. paragraphs
                  without line breaks) for the word wrapping to work correctly. This is
				  because the line breaks of the input text are conserved. 
 */

void wrap(ofstream *output, vector<string> input);

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Error: insufficient arguments.\nUsage: WordWrap [path_to_text_file]");
		return -1;
	}

	ifstream original_text;
	ofstream wrapped_text;

	original_text.open(argv[1], ios::out);

	string filename_string = string("wrapped_") + argv[1];
	const char * output_filename = filename_string.c_str();
	
	//Create a file and clear it for writing the wrapped text to.
	wrapped_text.open(output_filename);
	wrapped_text.clear();
	//wrapped_text.close();
	
	//String buffer for each paragraph of the original text.
	string paragraph;
	//String buffer for the words of the paragraph.
	string word_buffer;
	//Vector of the words of the paragraph.
	vector<string> words; 
	

	if (original_text.is_open())
	{
		while (getline(original_text, paragraph))
		{
			//Insert the paragraph into a stringstream, to split the words by spaces.
			stringstream ss(paragraph);

			while (ss >> word_buffer) { words.push_back(word_buffer); }
			cout << "number of words " << words.size();

			wrap(&wrapped_text, words);
			wrapped_text << "\n";
			words.clear();

		}
		original_text.close();
	}

	else cout << "Unable to open file";

	return 0;
}

void wrap(ofstream *output, vector<string> input) {
	string line;
	//cout << "filename : " << filename;
	string output_filename_string;
	//char* output_filename = filename.c_str;
	 
	//Reopen the output file for appending the wrapped paragraphs. 
	//output.open(filename, ios::out | ios::app);
	for (int i = 0; i < input.size(); i++) {
		if (line.size() + input[i].size() <= max_width) {
			line = line + input[i] + " ";
		}
		else {
			line = line + "\n";
				cout << line;
				*output << line;
				line = input[i] + " ";
		}
	}
	*output << line; //append the last line.
}
