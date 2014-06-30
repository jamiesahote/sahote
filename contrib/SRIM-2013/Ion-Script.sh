#!/bin/sh

wine TRIM.exe
tail -100 E2RECOIL.txt > Energy-List.txt

rm MOOSE-Ions.csv

FILE="Energy-List.txt"
while read line; do
     range=$(echo $line | awk '{print ($1 / 10000000000)}')
     energy=$(echo $line | awk '{print $3}')
     string=$range" "$energy
     echo $string >> MOOSE-Ions.csv
done < $FILE

mv MOOSE-Ions.csv /home/jamie/projects/sahote/problems/
