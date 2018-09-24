#!/bin/bash

for file in testdata/* /bin/bash;
do
    #echo "$file"
    ./huffman -c "tmp" "$file"
    ./huffman -d "out" "tmp"
    d="$(diff $file out -q)"
    if [ "$d" != "" ]
    then
        echo -e "\e[31m$file: Test fail :c\e[39m"
    else
        size1="$(stat -c %s $file)"
        size2="$(stat -c %s tmp)"
        echo -e "\e[92m$file: Test passed c: $size1 -> $size2\e[39m"
    fi
    rm "out" "tmp"
done