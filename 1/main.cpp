#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>



std::vector< int > load_input(std::string filename){
	std::vector<int> res = {0};
	std::string line;

	std::ifstream input(filename);
	while (getline(input, line)){
		if (line.empty()){
			res.push_back(0);
		}
		else {
			res.back() += std::stoi(line);
		}
	}
	return res;
}


std::vector< std::string > load_input_strings(std::string filename){
	std::vector< std::string > result = {};
	std::string line;

	std::ifstream input(filename);
	while (getline(input, line)){
		result.push_back(line);
	}
	return result;
}

int main(){

	std::vector<int> results = load_input("input.txt");
	std::sort(results.begin(), results.end(), std::greater<int>());
	std::cout << results[0] << " " << results[0] + results[1] + results[2];
	
	return 0;
}
