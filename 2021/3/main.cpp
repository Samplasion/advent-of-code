// Copyright (c) 2021 Samplasion <samplasion@gmail.com>
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <algorithm>
#include <compare>
#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::bitset<12> bitset12;
typedef std::vector<bitset12> bitsetVec;

template <typename T, typename F>
std::vector<T> filterVector(std::vector<T> &v, F f)
{
    std::vector<T> result;
    for (auto &e : v)
    {
        if (f(e))
        {
            result.push_back(e);
        }
    }
    return result;
}

template <typename T>
std::vector<T> copyVector(std::vector<T> const &v)
{
    std::vector<T> ret;
    ret.reserve(v.size());
    std::copy(v.begin(), v.end(), std::back_inserter(ret));
    return ret;
}

bitsetVec readFile()
{
    bitsetVec v;
    std::ifstream in("input.txt");

    std::string bits;
    while (in >> bits)
    {
        bitset12 b(bits);
        v.push_back(b);
    }

    return v;
}

bitset12 mostCommon(bitsetVec const &bitsets)
{
    bitset12 mostCommon(0);

    for (int i = bitsets[0].size() - 1; i >= 0; i--)
    {
        int countZeros = 0;
        int countOnes = 0;
        for (auto &bitset : bitsets)
        {
            if (bitset[i] == 0)
            {
                countZeros++;
            }
            else
            {
                countOnes++;
            }
        }

        if (countZeros > countOnes)
        {
            mostCommon[i] = 0;
        }
        else
        {
            mostCommon[i] = 1;
        }
    }

    return mostCommon;
}

void part1(bitsetVec bitsets)
{
    bitset12 gamma(0);
    bitset12 epsilon(0);
    bitset12 base = mostCommon(bitsets);

    auto finalGamma = base.to_ulong();
    auto finalEpsilon = base.flip().to_ulong();

    std::cout << "[Part 1] The power consumption of the submarine is: " << finalGamma * finalEpsilon << std::endl;
}

// Part 2 partly based on https://www.reddit.com/r/adventofcode/comments/r7r0ff/2021_day_3_solutions/hn2r5qx/
bitset12 lifeReport(bitsetVec bitsets, bool complement, int bit)
{
    if (bitsets.size() == 1)
    {
        return bitsets[0];
    }

    auto target = mostCommon(bitsets)[bit] ^ complement;
    bitsetVec res = filterVector(bitsets, [&target, bit](bitset12 const &b)
                                 { return b[bit] == target; });

    return lifeReport(res, complement, bit - 1);
}

void part2(bitsetVec bitsets)
{
    auto oxygen = lifeReport(bitsets, 0, bitsets[0].size() - 1);
    auto carbon = lifeReport(bitsets, 1, bitsets[0].size() - 1);

    std::cout << "[Part 2] The final life support rating is: " << (oxygen.to_ullong() * carbon.to_ullong()) << std::endl;
}

int main(int argc, const char *argv[])
{
    auto v = readFile();

    part1(v);
    part2(v);

    return 0;
}