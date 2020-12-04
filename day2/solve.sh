#!/bin/bash

input="./input.txt"
counter=0

while IFS= read -r line
do
    arr=(${line//[-,:]/ })
    count=$(awk -F"(${arr[2]})" '{print NF-1}' <<< "${arr[3]}}" )

    if (($count >= ${arr[0]} && $count <= ${arr[1]})); then
        ((counter++))
    fi

done < $input

echo $counter

