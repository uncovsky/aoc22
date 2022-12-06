#include "../utils/load_lines.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <set>


int find_distinct_packet(const std::string &line, size_t window_size){

    if (line.length() < window_size)
        return -1;

    for (size_t i = 0; i < line.length() - window_size; i++){
        std::set<char> window(line.begin() + i, 
                              line.begin() + i + window_size);
        if (window.size() == window_size)
            return i + window_size;
    }

    return -1;
}

int main(){
    std::string input = load_input_strings("input.txt")[0];
    std::cout << find_distinct_packet(input, 4) << std::endl;
    std::cout << find_distinct_packet(input, 14) << std::endl;
}


