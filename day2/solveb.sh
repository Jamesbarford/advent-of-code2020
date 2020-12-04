#!/bin/bash

input="./input.txt"
counter=0

while IFS= read -r line
do
    arr=(${line//[-,:]/ })
    position1=${arr[3]:${arr[0]}-1:1}
    position2=${arr[3]:${arr[1]}-1:1}
    char=${arr[2]}

    if [[ ($position1 == $char && $position2 != $char) || ($position2 == $char && $position1 != $char) ]]; then
        (( ++counter ))
    fi
done < $input

echo $counter

