#!/bin/bash

##wine TRIM.exe


tail -100 E2RECOIL40CuslabTi.txt > Energy-List40CuslabTi.txt
FILE="Energy-List40CuslabTi.txt"
while read line; do
     range=$(echo $line | awk '{print ($1 / 10000000000)}')
     energy=$(echo $line | awk '{print $3}')
    string1=$range
    string2=$energy
done <$FILE

##rm IonBeamEnergy.txt
touch IonBeamEnergy40CuslabTi.txt
Rbeam=$(grep -r "beam_radius" ~/projects/sahote/problems/SahoteTestLocal.i | awk '{print $3}')

echo "Beam radius is "$Rbeam;

echo "AXIS Z" >> IonBeamEnergy40CuslabTi.txt
##need to present string "range" rather than as a column, as a row of number seperated by a space
while read line; do
     range=$(echo $line | awk '{print (($1 / 10000000000) - 0.0025)}')
     printf "%.5f " $range >> IonBeamEnergy40CuslabTi.txt
done <$FILE
printf "\n" >> IonBeamEnergy40CuslabTi.txt

echo "AXIS Y" >> IonBeamEnergy40CuslabTi.txt
awk 'BEGIN{ for (i=-0.01; i <= 0.0105; i+=0.0005) printf("%.4f ", i); }' >> IonBeamEnergy40CuslabTi.txt
printf "\n" >> IonBeamEnergy40CuslabTi.txt

echo "AXIS X" >> IonBeamEnergy40CuslabTi.txt
awk 'BEGIN{ for (i=-0.01; i <= 0.0105; i+=0.0005) printf("%.4f ", i); }' >> IonBeamEnergy40CuslabTi.txt
printf "\n" >> IonBeamEnergy40CuslabTi.txt

echo "DATA" >> IonBeamEnergy40CuslabTi.txt
##require a for loop which iterates between the x and y coordinates in the fashion of the piecewise multilinear data matrix input which states that if the coordinates are within the radius (Rbeam) pulled in above from the input file pull in the SRIM energies and if it is outside Rbeam, output 100 zeros

for x in {-20..20}
do
  for y in {-20..20}
  do
    circrad=$(echo "sqrt(($x/2000)^2 + ($y/2000)^2)" | bc -l)
    if (( $(echo "$Rbeam > $circrad" | bc -l) )); then
## Here, the current point is inside the beam, so dump the actual energies from SRIM
      FILE="Energy-List40CuslabTi.txt"
      while read line; do
        energy=$(echo $line | awk '{print $3}')
        echo "$energy" >> IonBeamEnergy40CuslabTi.txt
      done <$FILE
    else
## Here, the current point is outside the beam, so just dump one hundred zeroes
      for z in {1..100}
      do
        echo 0 >> IonBeamEnergy40CuslabTi.txt
      done
    fi
  done
done


mv IonBeamEnergy40CuslabTi.txt /home/jamie/projects/sahote/problems
