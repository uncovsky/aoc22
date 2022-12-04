#include "../utils/load_lines.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>



int get_priority(char error){
    if (error < 'a')
        return error - 'A' + 27;
    return error - 'a' + 1;
}


int task1_sol(const std::vector< std::string > &input){
    int result = 0;
    for ( const std::string & line : input ){

        int n = line.length() / 2;
        char error = line[0];
        int i = 0;

        while (std::find(line.begin() + n, line.end(), error) == line.end()){
            error = line[++i];
        }

        result += get_priority(error);
    }

    return result;
}

int task2_sol(const std::vector< std::string > &input){
    int result = 0;
    for ( size_t i = 0; i < input.size(); i+=3 ){
        const std::string &line1 = input[i], &line2 = input[i+1], &line3 = input[i+2];
        for (char c : line1){
            if ( (std::find(line2.begin(), line2.end(), c) != line2.end()) && 
                 (std::find(line3.begin(), line3.end(), c) != line3.end()) ){
                result += get_priority(c);
                break;
           } 
        }
    }
    return result;
}

int main(){

    auto res = load_input_strings("input.txt");
    int sum = task1_sol(res);
    int sum2 = task2_sol(res);
    std::cout << sum << " " << sum2 << std::endl;
    return 0;
}
