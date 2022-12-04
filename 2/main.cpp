#include "../utils/load_lines.hpp"
#include <iostream>
#include <unordered_map>

int sum_score(const std::vector<std::string> &res){

    std::unordered_map<char, char> winning = {{'Y', 'A'}, {'Z' , 'B'}, {'X', 'C'}};
    std::unordered_map<char, char> losing = {{'Z', 'A'}, {'X' , 'B'}, {'Y', 'C'}};

    int result = 0;
    for (const std::string &line : res){
        char play = line[2];
        char opponent = line[0];

        if (play == 'X')
            result += 1;
        else if (play == 'Y')
            result += 2;
        else
            result += 3;

        if (opponent == winning[play])
            result += 6;
        else if (opponent != losing[play])
            result += 3;
    }

    return result;
}

int sum_score_second(const std::vector<std::string> &res){

    std::unordered_map<char, char> winning = {{'A', 'Y'}, {'B' , 'Z'}, {'C', 'X'}};
    std::unordered_map<char, char> drawing = {{'A', 'X'}, {'B' , 'Y'}, {'C', 'Z'}};
    std::unordered_map<char, char> losing = {{'A', 'Z'}, {'B' , 'X'}, {'C', 'Y'}};

    int result = 0;
    for (const std::string &line : res){
        char play = line[2];
        char opponent = line[0];
        char chosen_move = losing[opponent];
        if (play == 'Z'){
            chosen_move = winning[opponent];
            result += 6;
        }
        else if (play == 'Y'){
            chosen_move = drawing[opponent];
            result += 3;
        }

        if (chosen_move == 'X')
            result += 1;
        else if (chosen_move == 'Y')
            result += 2;
        else
            result += 3;
    }

    return result;
}


int main(){
	auto res = load_input_strings("input.txt");
    
    int res1 = sum_score(res);
    int res2 = sum_score_second(res);

    std::cout << res1 << " " << res2 << std::endl;



	return 0;
}
