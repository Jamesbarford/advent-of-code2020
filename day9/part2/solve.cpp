#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define WINDOW 25
#define INVALID 138879426

void shift_window(int window[], int value);
void reduce_window(int window[], int index, std::vector<int> *invalid_window);

int main(void)
{
    std::ifstream infile("../input.txt");
    std::string line;
    std::vector<int> invalid_window;
    int current_window[WINDOW], line_count = 0;

    while (std::getline(infile, line))
    {
        if (line_count < WINDOW)
            current_window[line_count] = std::stol(line);

        if (line_count >= WINDOW)
        {
            shift_window(current_window, std::stol(line));
            reduce_window(current_window, 0, &invalid_window);

            if (invalid_window.size() > 0)
                break;
        }

        ++line_count;
    }

    int max = *std::max_element(invalid_window.begin(), invalid_window.end());
    int min = *std::min_element(invalid_window.begin(), invalid_window.end());

    std::cout << "sum :: " << max + min << std::endl;
}

void shift_window(int window[], int value)
{
    for (int i = 0; i < WINDOW; ++i)
        window[i] = window[i + 1];
    window[WINDOW - 1] = value;
}

void reduce_window(int window[], int index, std::vector<int> *invalid_window)
{
    int accumulator = 0, len = WINDOW - 1;

    for (int i = index; i < len; ++i)
    {
        accumulator = window[i];
        invalid_window->push_back(window[i]);
        for (int j = i + 1; j < len; ++j)
        {
            int next = window[j];
            invalid_window->push_back(next);
            accumulator += next;

            if (accumulator == INVALID)
                return;
        }

        accumulator = 0;
        invalid_window->clear();
    }

    if (index < len)
    {
        invalid_window->clear();
        return reduce_window(window, index + 1, invalid_window);
    }

    return;
}