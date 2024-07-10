#!/bin/bash
read -p "enter the file name: " filename

exe_file="${filename}.c"

if [ -f "$exe_file" ]; then
    echo "compiling $exe_file..."

    gcc -g -Wall -std=c99 "$exe_file" -o "${filename}.exe"

    if [ $? -eq 0 ]; then
        echo "Compiled successefully. Executable created: ${filename}."

        echo "You may run the file."

    else 
        echo "Didn't pass compilation."
    fi
else 
    echo "Couldn't find the file. try again."
fi

