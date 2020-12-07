#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

int main(void)
{
    int count;
    set<char> uniq_chars;
    ifstream infile("input.txt");
    string line;

    while (getline(infile, line))
    {
        if (line == "") {
            count += uniq_chars.size();    
            uniq_chars.clear();
            continue;
        }

        for(char& c : line) {
            uniq_chars.insert(c);
        }
    }
    
    count += uniq_chars.size();

    cout << count << '\n';
}
