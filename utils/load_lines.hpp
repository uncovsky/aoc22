#pragma once
#include <vector>
#include <string>
#include <fstream>

std::vector< std::string > load_input_strings(std::string filename){
	std::vector< std::string > result = {};
	std::string line;

	std::ifstream input(filename);
	while (getline(input, line)){
		result.emplace_back(line);
	}
	return result;
}
