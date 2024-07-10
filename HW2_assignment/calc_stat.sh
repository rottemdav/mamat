#!/bin/bash

#----errors check and environment setup----#


# Check if the amount of arguments is legal
if [[ "$#" != 1 ]]; then
    echo "Wrong number of arguments"
    exit 1
fi

# Get the course_file.txt file
#course_file=$("[0-9]{6}.txt")
course_file=$1


# Get the course number from the file neame of the course
course_number="${course_file%.txt}"

#* Check if the file course_number.txt exists
if [ ! -f "${course_file}" ]; then
    echo "Course not found" >&2
    exit 1
fi

# Create course directory name
result_directory="${course_number}_stat"

# Check if directory exists, if so deletes it
if [ -d "${course_number}_stat" ]; then
    rm -rf "$result_directory"
fi

# Create new directory called {course_number}_stat
mkdir "$result_directory"

#----finished errors check and environment setup----#

echo $1 | ./hist.exe $1 -nbins > "$result_directory/histogram.txt"

mean=$(./mean.exe "$1")
min=$(./min.exe "$1")
max=$(./max.exe "$1")
median=$(./median.exe "$1")

echo -e "$mean\t$min\t$max\t$median" > "statistics.txt"