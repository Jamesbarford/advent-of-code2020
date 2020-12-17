#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#define SINGLE_SPACE " "

enum command
{
    nop,
    acc,
    jmp,
};

std::pair<command, int> create_pair(std::string *str, std::map<std::string, command> *command_map, std::string delimiter);
std::string create_key(std::pair<command, int> instruction, int position);
int sum_acc(std::vector<std::pair<command, int>> *instructions);

int main(void)
{
    std::map<std::string, command> command_map{
        {"acc", command::acc},
        {"jmp", command::jmp},
        {"nop", command::nop}};
    std::vector<std::pair<command, int>> instructions;
    std::ifstream infile("../input.txt");
    std::string line;

    while (std::getline(infile, line))
        instructions.push_back(create_pair(&line, &command_map, SINGLE_SPACE));

    int x = sum_acc(&instructions);
    std::cout << "answer :: " << x << std::endl;
}

std::pair<command, int> create_pair(std::string *str, std::map<std::string, command> *command_map, std::string delimiter)
{
    size_t pos = 0;
    std::pair<command, int> new_pair;

    while ((pos = str->find(delimiter)) != std::string::npos)
    {
        new_pair.first = command_map->at(str->substr(0, pos));
        new_pair.second = std::stoi(str->substr(pos, str->size() - 1));

        str->erase(0, pos + delimiter.length());
    }

    return new_pair;
}

int sum_acc(std::vector<std::pair<command, int>> *instructions)
{
    int position = 0;
    int acc = 0;
    std::set<std::string> visited;
    std::pair<command, int> current_instruction = instructions->at(position);
    std::string key;

    while (true)
    {
        key = create_key(current_instruction, position);

        if (visited.find(key) != visited.end())
            break;
        else
            visited.insert(key);

        switch (current_instruction.first)
        {
        case command::acc:
            position += 1;
            acc += current_instruction.second;
            current_instruction = instructions->at(position);
            continue;

        case command::nop:
            position += 1;
            current_instruction = instructions->at(position);
            continue;

        case command::jmp:
            position += current_instruction.second;
            current_instruction = instructions->at(position);
            continue;

        default:
            std::cout << " invalid instruction " << std::endl;
            break;
        }
    }

    return acc;
}

std::string create_key(std::pair<command, int> instruction, int position)
{
    return std::to_string(instruction.first) + "__" + std::to_string(instruction.second) + "__" + std::to_string(position);
}