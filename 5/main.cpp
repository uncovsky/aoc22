#include "../utils/load_lines.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <memory>
#include <sstream>
#include <deque>


using crates_container_t = std::vector< std::unique_ptr< std::deque< char > > >;



void move_crane9000(crates_container_t &crates, const std::array<int, 3> &arguments){
    for (int i = 0; i < arguments[0]; i++){
        char c = crates[arguments[1] - 1]->front();
        crates[arguments[1] - 1]->pop_front();
        crates[arguments[2] - 1]->push_front(c);
    }
}

void move_crane9001(crates_container_t &crates, const std::array<int, 3> &arguments){
    auto src_it = crates[arguments[1]-1]->begin();
    auto target_it = crates[arguments[2]-1]->begin();
    crates[arguments[2] - 1]->insert(target_it, src_it, src_it + arguments[0]);
    crates[arguments[1] - 1]->erase(src_it, src_it + arguments[0]);
}


std::string parse_crate_instr(const std::string &line, bool &empty){
    empty = true;
    std::string result;
    for (size_t i = 0; i < line.length(); i += 4){
        if ((line[i] == '[') && (line[i+2] == ']')){
           result.push_back(line[i+1]);
           empty = false;
        }
        else
            result.push_back(' ');
    }

    return result;
}

void parse_move_instr(
        const std::string &line, 
        crates_container_t &crates,
        bool new_crane){

    std::array<int, 3> arguments = { {0} };
    int i = 0; 
    std::istringstream input;
    input.str(line);
    
    std::string word;
    while (getline(input, word, ' ')){
        if (i % 2 == 1)
            arguments[i / 2] = std::stoi(word);
        i++;
    }

    if (arguments[0] < 1)
        return;

    if (new_crane)
        move_crane9001(crates, arguments);
    else
        move_crane9000(crates, arguments);
}


void add_crate_floor(crates_container_t &crates, const std::string &floor){
    for (size_t c_it = 0; c_it < floor.size(); c_it++){
        if (floor[c_it] != ' ')
            crates[c_it]->push_back(floor[c_it]);
    }
}

std::string move_crates(const std::vector<std::string> &lines, bool new_crane){

    bool crates_done = false;
    size_t it = 0;

    // parse first line and get num of crates
    size_t crate_number = parse_crate_instr(lines[0], crates_done).length();
    crates_container_t crates;
    
    // initialize crates
    for (size_t i = 0; i < crate_number; i++) {
        crates.emplace_back(std::make_unique<std::deque<char>>());
    }

    // first phase, scan crate lines
    while (!crates_done){
        std::string crate_floor = parse_crate_instr(lines[it], crates_done);
        add_crate_floor(crates, crate_floor);
        it++;
    }

    // snd phase, scan & exec moves of crates
    for (; it < lines.size(); it++){
        parse_move_instr(lines[it], crates, new_crane);
    }

    std::string result;
    for (size_t i = 0; i < crates.size(); i++)
        result.push_back(crates[i]->front());

    return result;
}

int main(){
    auto result = load_input_strings("input.txt");

    std::cout << move_crates(result, false) << std::endl;
    std::cout << move_crates(result, true) << std::endl;

    return 0;
}

