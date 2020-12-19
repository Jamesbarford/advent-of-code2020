#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>

#include "LinkedList.cpp"

#define SINGLE_SPACE " "
#define DOUBLE_DASH "__"

enum command
{
    nop,
    acc,
    jmp,
};

std::map<std::string, command> command_map{
    {"nop", command::nop},
    {"acc", command::acc},
    {"jmp", command::jmp}};

std::map<int, command> int_to_command{
    {0, command::nop},
    {1, command::acc},
    {2, command::jmp}};

std::pair<command, int> create_pair(std::string *str, std::string delimiter);
std::string create_key(command instruction, int value, int position);
int sum_acc(std::vector<std::pair<command, int>> *instructions, LinkedList<std::string> *previous_attempts, int previous_index);

int main(void)
{
    std::vector<std::pair<command, int>> instructions;
    std::ifstream infile("../input.txt");
    std::string line;
    LinkedList<std::string> previous_attempts;

    while (std::getline(infile, line))
        instructions.push_back(create_pair(&line, SINGLE_SPACE));

    std::cout << "answer :: " << sum_acc(&instructions, &previous_attempts, 0) << std::endl;
}

std::pair<command, int> create_pair(std::string *str, std::string delimiter)
{
    size_t pos = 0;
    std::pair<command, int> new_pair;

    while ((pos = str->find(delimiter)) != std::string::npos)
    {
        new_pair.first = command_map.at(str->substr(0, pos));
        new_pair.second = std::stoi(str->substr(pos, str->size() - 1));

        str->erase(0, pos + delimiter.length());
    }

    return new_pair;
}

int sum_acc(std::vector<std::pair<command, int>> *instructions, LinkedList<std::string> *previous_attempts, int current_index)
{
    int position = 0;
    int acc = 0;
    LinkedList<std::string> visited;
    std::pair<command, int> current_instruction = instructions->at(position);
    std::string key;

    while (true)
    {
        key = create_key(current_instruction.first, current_instruction.second, position);
        int index = visited.get_index(key);
        if (index == -1)
            visited.insert(key);
        else
        {
            if (previous_attempts->tail != nullptr)
            {
                std::string previous_command_str = previous_attempts->tail->data.substr(0, 1);
                instructions->at(current_index).first = int_to_command.at(std::stoi(previous_command_str));
            }

            int new_index = current_index;

            for (; new_index < instructions->size(); ++new_index)
            {
                std::pair<command, int> pair = instructions->at(new_index);
                if (pair.first == command::acc)
                    continue;

                command new_command = pair.first == command::nop ? command::jmp : command::nop;

                if (new_command == command::jmp && pair.second == 0)
                    continue;

                std::string new_key = create_key(new_command, pair.second, new_index);

                if (previous_attempts->has(new_key) == false)
                {
                    instructions->at(new_index).first = new_command;
                    previous_attempts->insert(new_key);
                    break;
                }
            }

            return sum_acc(instructions, previous_attempts, new_index);
        }

        switch (current_instruction.first)
        {
        case command::acc:
            position += 1;
            acc += current_instruction.second;
            break;

        case command::nop:
            position += 1;
            break;

        case command::jmp:
            position += current_instruction.second;
            break;

        default:
            std::cout << " invalid instruction " << std::endl;
            break;
        }

        if (position >= instructions->size())
            return acc;
        else
            current_instruction = instructions->at(position);
    }

    return acc;
}

std::string create_key(command instruction, int value, int position)
{
    return std::to_string(instruction) + DOUBLE_DASH + std::to_string(value) + DOUBLE_DASH + std::to_string(position);
}