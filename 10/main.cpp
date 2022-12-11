#include "../utils/load_lines.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


// returns vector of same length as clock cycles of program
// each cell result[i] is register X value at clock cycle i
std::vector<int> register_value_map(const std::vector<std::string> &program){
    std::vector<int> result_cells;
    int register_x = 1;

    for (const std::string &instruction : program){
        auto arguments = split_line(instruction);

        if (arguments[0] == "noop"){
            result_cells.push_back(register_x);
        }

        else if (arguments[0] == "addx"){
            // two clock cycles
            result_cells.push_back(register_x);
            result_cells.push_back(register_x);

            int operand = std::stoi(arguments[1]);
            register_x += operand;
        }
    }

    return result_cells;

}
int sum_signals(const std::vector<std::string> &program, 
                const std::vector<unsigned> &indices){

    int result = 0;
    auto register_values = register_value_map(program);
    for (unsigned index : indices){
        result += register_values[index-1] * index;
    }

    return result;
}

void draw_sprite(const std::vector<std::string> &program){
    auto reg_vals = register_value_map(program);
    for (int row = 0; row < 6; row++){
        std::string line;
        for (int col = 0; col < 40; col++){
            if (std::abs(reg_vals[row * 40 + col] - col) <= 1)
                line.push_back('#');
            else
                line.push_back('.');
        }

        std::cout << line << '\n';
        line.clear();
    }
}

int main(){
    auto lines = load_input_strings("input.txt");
    std::cout << sum_signals(lines, {20, 60, 100, 140, 180, 220}) << std::endl;
    draw_sprite(lines);
    return 0;

}

