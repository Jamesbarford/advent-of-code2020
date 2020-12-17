#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <vector>

#include "BagMap.h"

#define DELIMITER ","
#define BAG_STRS std::regex(" bags contain | bags, | bag, | bags.| bag.")
#define SINGLE_SPACE std::regex(" ")

void insert(std::string delimiter, std::string str, BagMap *bag_map);

int main(void)
{
    std::ifstream infile("input.txt");
    std::string line;
    BagMap bag_map;

    while (std::getline(infile, line))
        insert(DELIMITER, regex_replace(line, BAG_STRS, DELIMITER), &bag_map);

    std::cout << "bag count :::" << bag_map.get_bag_count(SHINY_GOLD) << std::endl;
}

void insert(std::string delimiter, std::string str, BagMap *bag_map)
{
    size_t pos = 0;
    int counter = 0;
    int bag_count = 0;
    std::string bag_str;
    std::string current_bag;

    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        bag_str = regex_replace(str.substr(0, pos), SINGLE_SPACE, "");

        if (counter == 0)
        {
            bag_map->insert(bag_str);
            bag_map->set_current_key(bag_str);
            ++counter;
        }

        else if (bag_str == NO_BAGS)
        {
            str.erase(0, pos + delimiter.length());
            continue;
        }

        else
        {
            bag_count = std::stoi(bag_str.substr(0, 1)) + 1;
            current_bag = bag_str.substr(1, pos - 1);

            while (--bag_count > 0)
                bag_map->add(current_bag);
        }

        str.erase(0, pos + delimiter.length());
    }
    bag_map->unset_current_key();
}
