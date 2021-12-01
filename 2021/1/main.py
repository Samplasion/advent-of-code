# Copyright (c) 2021 Samplasion <samplasion@gmail.com>
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

def main():
    print("=============")
    print("= AoC Day 1 =")
    print("=============")
    print()

    with open("input.txt") as f:
        file = f.read()
        numbers = list(map(int, file.split("\n")))

        phase1(numbers)
        phase2(numbers)


def phase1(numbers):
    """[...] count the number of times a depth
    measurement increases from the previous measurement."""

    prev: int = None
    increases = 0

    for i in numbers:
        if (prev is not None):
            if (i > prev):
                increases += 1

        prev = i

    print(
        f"[Part 1] Within your input, the depth increases {increases} times.")


def phase2(numbers):
    windows = []
    prev: int = None
    increases = 0

    i = 0
    while (i < len(numbers) - 2):
        windows.append((numbers[i], numbers[i + 1], numbers[i + 2]))
        i += 1

    for window in windows:
        sum = window[0] + window[1] + window[2]

        if (prev is not None):
            if (sum > prev):
                increases += 1

        prev = sum

    print(
        f"[Part 2] Within your input, the depth of the windows increases {increases} times.")


if __name__ == '__main__':
    main()
