# Copyright (c) 2020 Samplasion <samplasion@gmail.com>
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

TARGET = 2020

def main():
    print("=============")
    print("= AoC Day 1 =")
    print("=============")
    print()

    with open("input.txt") as f:
        file = f.read()
        numbers = sorted(list(map(int, file.split("\n"))))
        
        phase1(numbers)
        phase2(numbers)

def phase1(numbers):
    min = 0
    max = -1
    number = numbers[min] + numbers[max]
    while number != TARGET:

        if number > TARGET:
            max -= 1
        else:
            min += 1
        number = numbers[min] + numbers[max]
    # else: print("There's no pair of numbers that amounts to {}".format(TARGET))

    print(f"[Phase 1] {numbers[min]} and {numbers[max]} are the numbers that amount to {TARGET}. " +
        f"Their product is {numbers[min]*numbers[max]}")

def phase2(numbers):
    for i in numbers:
        for j in numbers:
            for k in numbers:
                if i + j + k == TARGET:
                    print(f"[Phase 2] {i}, {j} and {k} are the numbers that amount to {TARGET}. " +
                        f"Their product is {i*j*k}")
                    return
    print(f"There's no group of 3 numbers that sums to {TARGET}.")

if __name__ == '__main__':
    main()