#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <numeric>

#include "BagMap.h"

void BagMap::insert(std::string key, BagCountCollection bags)
{
    bag_map.insert_or_assign(key, bags);
}

void BagMap::insert(std::string key)
{
    bag_map.insert(std::pair(key, std::vector<std::string>()));
}

bool BagMap::has(std::string key)
{
    return bag_map.count(key);
}

void BagMap::add(std::string key, std::string bag)
{
    bag_map.at(key).push_back(bag);
}

void BagMap::add(std::string bag)
{
    if (current_key.has_value())
        this->add(current_key.value(), bag);
    else
        std::cout << "current_key is NULL" << std::endl;
}

void BagMap::set_current_key(std::string key)
{
    current_key = key;
}

void BagMap::unset_current_key()
{
    current_key.reset();
}

bool BagMap::is_empty_value(std::string key)
{
    return bag_map.at(key).size() == 0;
}

void BagMap::print()
{
    for (auto &entry : bag_map)
    {
        std::cout << "key :: " << entry.first << std::endl;

        if (this->is_empty_value(entry.first) == 1)
            std::cout << "  empty" << std::endl;
        else
        {

            for (auto &bag : entry.second)
            {
                std::cout << bag << ", ";
            }
            std::cout << std::endl;
        }
    }
}

BagCountCollection BagMap::at(std::string key)
{
    return bag_map.at(key);
}

int BagMap::get_bag_count(std::string current_bag)
{
    if (current_bag.empty() || !this->has(current_bag))
        return 0;

    std::vector<int> bag_counts;
    BagCountCollection bags = this->at(current_bag);
    int count = bags.size();

    for (auto &child_bag : bags)
        bag_counts.push_back(this->get_bag_count(child_bag));

    return std::accumulate(bag_counts.begin(), bag_counts.end(), 0) + count;
}
