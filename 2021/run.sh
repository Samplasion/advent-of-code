#!/bin/bash

echo "================================"
echo "= Samplasion's AoC 2021 runner ="
echo "================================"
echo

day="$([[ -p /dev/stdin ]] && cat - || echo "$1")"
if [[ -z "$day" ]]; then
    read -p "What day's challenge do you want to run? [1-25] Please enter a number without leading zeros: " day
else
    echo "Running the solution for day ${day}..."
fi

echo

pushd "./$day" > /dev/null
./run.sh "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
popd > /dev/null