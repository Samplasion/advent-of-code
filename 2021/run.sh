#!/bin/bash

echo "================================"
echo "= Samplasion's AoC 2021 runner ="
echo "================================"
echo

day="$([[ -p /dev/stdin ]] && cat - || echo "$@")"
if [[ -z "$day" ]]; then
    read -p "What day's challenge do you want to run? [1-25] Please enter a number without leading zeros: " day
else
    echo "Running the solution for day ${day}..."
fi

echo

pushd "./$day" > /dev/null
./run.sh
popd > /dev/null