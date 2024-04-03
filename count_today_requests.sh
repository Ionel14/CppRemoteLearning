#!/bin/bash

today=$(date +'%Y-%m-%d')

file="server/data_files/LogFile.txt"

count=0

while IFS= read -r line; do
    date=$(echo "$line" | awk -v FS=Date: '{print $2}')
    
    if [[ "$date" == "$today" ]]; then
        ((count++))
    fi
done < "$file"

echo "Number of requests recevied today ($today): $count"

