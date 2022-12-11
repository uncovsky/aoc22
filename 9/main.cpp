#include "../utils/load_lines.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <sstream>
#include <tuple>

int simulate_knots(const std::vector<std::string> &lines, size_t knots){

    int head_pos[] = {0, 0}; 
    std::vector<std::array<int, 2>> tails(knots, {{0, 0}});
    std::set<std::tuple<int, int>> visited = {{0, 0}};

    for (const auto & line : lines){
        auto tokens = split_line(line, ' ');
        char direction = tokens[0][0];
        int steps = std::stoi(tokens[1]);
        int direction_vec[] = {0, 0};

        switch(direction){
            case 'U':
                direction_vec[1] = 1;
                break;
            case 'D':
                direction_vec[1] = -1;
                break;
            case 'L':
                direction_vec[0] = -1;
                break;
            case 'R':
                direction_vec[0] = 1;
                break;
            default:
                return -1;
        }

        for (int i = 0; i < steps; i++){
            head_pos[0] += direction_vec[0]; 
            head_pos[1] += direction_vec[1];

            for (size_t i = 0; i < knots; i++){
                int x_dist = 0, y_dist = 0;
                if (i == 0){
                    x_dist = head_pos[0] - tails[0][0];
                    y_dist = head_pos[1] - tails[0][1];
                }
                else{
                    x_dist = tails[i-1][0] - tails[i][0];
                    y_dist = tails[i-1][1] - tails[i][1];
                }

                if ((std::abs(x_dist) < 2) && (std::abs(y_dist) < 2))
                    break;

                tails[i][0] += (x_dist != 0) ? x_dist / std::abs(x_dist) : 0;
                tails[i][1] += (y_dist != 0) ? y_dist / std::abs(y_dist) : 0;

            }
            
            visited.emplace(tails.back()[0], tails.back()[1]);
        }
    }

    return visited.size(); 
    
}


int main(){
    auto lines = load_input_strings("input.txt");
    std::cout << simulate_knots(lines, 1) << std::endl;
    std::cout << simulate_knots(lines, 9);
    return 0;
}

