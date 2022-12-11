#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector< std::string > load_input_strings(std::string filename){
	std::vector< std::string > result = {};
	std::string line;

	std::ifstream input(filename);
	while (getline(input, line)){
		result.emplace_back(line);
	}
	return result;
}

std::vector< std::string > split_line(std::string line, char delim=' '){
    std::istringstream input;
    input.str(line);
    int i = 0;
    
    std::string word;
    std::vector< std::string > result;
    while (getline(input, word, delim)){
        result.push_back(word);
        i++;
    }

    return result;
}

