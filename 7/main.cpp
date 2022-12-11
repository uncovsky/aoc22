#include "../utils/load_lines.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>


struct node_t {
    size_t size;

    std::map< std::string, std::unique_ptr< node_t > > children = {};

    node_t (size_t s) : size(s){};

    void insert(std::string name, size_t s){
        children.emplace(name, new node_t(s));
    }
};

void parse_filedata(const std::vector< std::string > &lines, node_t& root, 
                                                             size_t &line_num){
    // while there are lines to parse
    while(line_num < lines.size()){
        std::vector< std::string > tokens = split_line(lines[line_num]);

        // change levels with cd command
        if ((tokens[0] == "$") && (tokens[1] == "cd")){
            if (tokens[2] == ".."){
                return;
            }

            else{
                line_num += 1;
                // taking a reference into the map is fine, since no
                // insertions/deletions will be done on it in the recursive call
                root.size -= root.children[tokens[2]]->size;
                parse_filedata(lines, *(root.children[tokens[2]]), line_num);
                // update new size
                root.size += root.children[tokens[2]]->size;
            }
        }

        // ignore the ls command, add children
        else if (tokens[0] != "$"){
            size_t size = 0;
            // if file add size to current dir
            if (tokens[0] != "dir"){
                size = std::stoul(tokens[0]);
                root.size += size;
            }
            root.insert(tokens[1], size);
        }

        // move to next line
        line_num++;
    }
}

node_t build_filetree(const std::vector< std::string > &lines){
    size_t line_num = 1;
    node_t root(0);
    parse_filedata(lines, root, line_num);
    return root;
}


size_t task1(const node_t &root){

    if (root.children.empty())
        return 0;
    size_t size = root.size > 100000 ? 0 : root.size;
    for (const auto &[name, child] : root.children){
        size += task1(*child);
    }
    return size;
}


void task2_find(const node_t &root, size_t target_size, size_t &best_size){
    // file
    if (root.children.size() == 0)
        return;

    if (root.size > target_size && root.size < best_size){
        best_size = root.size;
    }

    for (const auto &[name, child] : root.children){
        task2_find(*child, target_size, best_size);
    }
}

size_t task2(const node_t &root, size_t fs_capacity, size_t space_needed){
    size_t used_space = root.size;
    size_t available_space = (fs_capacity - used_space);

    if (space_needed <= available_space){
        std::cout << "enough free space." << std::endl;
        return 0;
    }

    size_t best_size = fs_capacity;
    task2_find(root, space_needed - available_space, best_size);
    
    return best_size;
}

int main(){
    auto lines = load_input_strings("input.txt");
    node_t res = build_filetree(lines);
    std::cout << task1(res) << "\n";
    std::cout << task2(res, 70000000, 30000000);
    return 0;
}

