#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readFile()
{
    std::vector<std::string> v;
    std::ifstream in("input.txt");

    std::string action;
    std::string value;
    while (in >> action >> value)
    {
        v.push_back(action + " " + value);
    }

    return std::move(v);
}

void part1(std::vector<std::string> actions)
{
    int horizontal = 0;
    int depth = 0;

    for (std::string i : actions)
    {
        int space = i.find_first_of(" ");
        std::string action = i.substr(0, space);
        std::string value = i.substr(space + 1);

        if (action == "forward")
        {
            horizontal += std::stoi(value);
        }
        else if (action == "up")
        {
            depth -= std::stoi(value);
        }
        else if (action == "down")
        {
            depth += std::stoi(value);
        }
    }

    std::cout << "[Part 1] The product of the horizontal position and depth is: " << horizontal * depth << std::endl;
}

void part2(std::vector<std::string> actions)
{
    int horizontal = 0;
    int depth = 0;
    int aim = 0;

    for (std::string i : actions)
    {
        int space = i.find_first_of(" ");
        std::string action = i.substr(0, space);
        std::string value = i.substr(space + 1);

        if (action == "forward")
        {
            horizontal += std::stoi(value);
            depth += std::stoi(value) * aim;
        }
        else if (action == "up")
        {
            aim -= std::stoi(value);
        }
        else if (action == "down")
        {
            aim += std::stoi(value);
        }
    }

    std::cout << "[Part 2] The final product of the horizontal position and depth is: " << horizontal * depth << std::endl;
}

int main()
{
    std::vector<std::string> v = readFile();

    part1(v);
    part2(v);

    return 0;
}