#!/bin/bash

input="./input.txt"
counter=0

while IFS= read -r line
do
    arr=(${line//[-,:]/ })
    lower_bounds=${arr[0]}
    upper_bounds=${arr[1]}
    char=${arr[2]}
    char_seq=${arr[3]}

    count=$(awk -F"(${char})" '{print NF-1}' <<< "${char_seq}")

    if (( $count >= $lower_bounds && $count <= $upper_bounds )); then
        (( ++counter ))
    fi

done < $input

echo $counter

