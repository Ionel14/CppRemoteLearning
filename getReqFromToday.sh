#!/bin/bash

# name of the log file
log_file="server/logFile.txt"

# today's date in format 'YYYY-MM-DD'
today=$(date +%F)

while IFS= read -r line; do
    date=$(echo "$line" | awk '{print $3}')
    if [ "$date" == "$today" ]; then
        echo "$line"
    fi
done < "$log_file"
