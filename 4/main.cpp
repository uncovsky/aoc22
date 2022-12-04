#include "../utils/load_lines.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <array>

std::array<int, 4> parse_line(const std::string& line){
    std::array<int, 4> result = { {0} };
    std::string current;
    int it = 0;

    for (size_t i = 0; i < line.length(); i++){
        current.push_back(line[i]);

        if ((line[i] == ',') || (line[i] == '-')){
            result[it] = std::stoi(current);
            it++;
            current.clear();
        }
    }

    result[3] = std::stoi(current);
    return result;
}

bool is_subinterval(int x1, int x2, int y1, int y2){
    return ((x1 >= y1) && (x2 <= y2)) || ((y1 >= x1) && (y2 <= x2));
}

bool overlap(int x1, int x2, int y1, int y2){
    return (x1 <= y2) && (y1 <= x2);
}

int solution1(const std::vector<std::string> &lines){
    int result = 0;

    for (const auto &line : lines){
        std::array<int, 4> intervals = parse_line(line);

        if (is_subinterval(intervals[0], intervals[1], 
                           intervals[2], intervals[3]))
            result += 1;
    }
    
    return result;
}

int solution2(const std::vector<std::string> &lines){
    int result = 0;

    for (const auto &line : lines){
        std::array<int, 4> intervals = parse_line(line);

        if (overlap(intervals[0], intervals[1], intervals[2], intervals[3]))
            result += 1;
    }
    return result;
}

int main(){
    auto lines = load_input_strings("input.txt");
    std::cout << solution1(lines) << " - " << solution2(lines) << std::endl;
    return 0;
}
