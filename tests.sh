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
        echo -e "\e[92m$file: Test past c:\e[39m"
    fi
    rm "out" "tmp"
done