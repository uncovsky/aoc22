#include "../utils/load_lines.hpp"
#include <vector>
#include <iostream>
#include <tuple>
#include <set>
#include <string>
#include <algorithm>


// for the sake of completion i will upload this abomination as well
// i am sorry

bool check_visible(const std::vector<std::string> &lines, size_t row, size_t col){
    char target = lines[row][col];
    bool visible = true;

    for (size_t i = 0; i < row; i++)
        if (lines[i][col] >= target)
            visible = false;
    if (visible)
        return true;

    visible = true;

    for (size_t i = row + 1; i < lines.size(); i++)
        if (lines[i][col] >= target)
            visible = false;

    if (visible)
        return true;
    visible = true;

    for (size_t i = 0; i < col; i++)
        if (lines[row][i] >= target)
            visible = false;
    if (visible)
        return true;

    visible = true;
    for (size_t i = col + 1; i < lines[0].size(); i++)
        if (lines[row][i] >= target)
            visible = false;
    if (visible)
        return true;

    return false;
}

int scenic_score(const std::vector<std::string> &lines, size_t row, size_t col){
    char target = lines[row][col];
    int total = 1;
    int tempsum = 0;

    for (size_t i = 0; i < row; i++){
        tempsum++;
        if (lines[row-1-i][col] >= target)
            break;
    }

    total *= tempsum;
    tempsum = 0;

    for (size_t i = row + 1; i < lines.size(); i++){
        tempsum++;
        if (lines[i][col] >= target)
            break;
    }

    total *= tempsum;
    tempsum = 0;

    for (size_t i = 0; i < col; i++){
        tempsum++;
        if (lines[row][col - 1 - i] >= target)
            break;
    }

    total *= tempsum;
    tempsum = 0;

    for (size_t i = col + 1; i < lines[0].size(); i++){
        tempsum++;
        if (lines[row][i] >= target)
            break;
    }

    total *= tempsum;

    return total;
}

int task1(const std::vector<std::string> &lines){
    // naive horrible solution
    size_t height = lines.size();
    size_t width = lines[0].size();

    int best = 0;

    for (size_t i = 0; i < height; i++){
        for (size_t it = 0; it < width; it++){
            best = std::max(best, scenic_score(lines, i, it));
        }
    }
    return best;
}

int main(){
    auto lines = load_input_strings("input.txt");
    std::cout << task1(lines);
    return 0;
}

