#include <iostream>
#include <fstream>
#include <string>

#define WINDOW 26

void shift_window(int window[], int value);
bool is_valid_window(int window[]);

int main(void)
{
    std::ifstream infile("../input.txt");
    std::string line;
    int current_window[WINDOW], line_count = 0;

    while (std::getline(infile, line))
    {
        if (line_count < WINDOW)
            current_window[line_count] = std::stoi(line);

        if (line_count >= WINDOW)
        {
            if (!is_valid_window(current_window))
                break;
            shift_window(current_window, std::stoi(line));
        }

        ++line_count;
    }

    std::cout << "invalid :: " << current_window[WINDOW - 1] << std::endl;
}

void shift_window(int window[], int value)
{
    for (int i = 0; i < WINDOW; ++i)
        window[i] = window[i + 1];
    window[WINDOW - 1] = value;
}

bool is_valid_window(int window[])
{
    int len = WINDOW - 1, value = window[len];

    for (int i = 0; i < len; ++i)
        for (int j = 1; j < len; ++j)
            if (window[i] + window[j] == value)
                return true;

    return false;
}