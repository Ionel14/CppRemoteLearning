#!/bin/bash
if [ "$#" -eq  "0" ]; then
  f="./resources/log.txt"
else
  f=$1
fi

if ! [ -f $f ]; then
  echo "File does not exist."
elif ! [ -r $f ]; then 
  echo "File is not readable."
else
  grep -c $(date -I) $f
fi
