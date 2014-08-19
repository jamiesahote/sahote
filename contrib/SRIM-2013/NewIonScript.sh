#!/bin/bash

##wine TRIM.exe


tail -100 E2RECOIL.txt > Energy-List.txt
FILE="Energy-List.txt"
while read line; do
     range=$(echo $line | awk '{print ($1 / 10000000000)}')
     energy=$(echo $line | awk '{print $3}')
    string1=$range
    string2=$energy
done <$FILE

##rm IonBeamEnergy.txt
touch IonBeamEnergy.txt
Rbeam=$(grep -r "beam_radius" ~/projects/sahote/problems/SahoteTestLocal.i | awk '{print $3}')

echo "Beam radius is "$Rbeam;

echo "AXIS Z" >> IonBeamEnergy.txt
##need to present string "range" rather than as a column, as a row of number seperated by a space
while read line; do
     range=$(echo $line | awk '{print (($1 / 10000000000) - 0.0025)}')
     printf "%.5f " $range >> IonBeamEnergy.txt
done <$FILE
printf "\n" >> IonBeamEnergy.txt

echo "AXIS Y" >> IonBeamEnergy.txt
awk 'BEGIN{ for (i=-0.01; i <= 0.0105; i+=0.0005) printf("%.4f ", i); }' >> IonBeamEnergy.txt
printf "\n" >> IonBeamEnergy.txt

echo "AXIS X" >> IonBeamEnergy.txt
awk 'BEGIN{ for (i=-0.01; i <= 0.0105; i+=0.0005) printf("%.4f ", i); }' >> IonBeamEnergy.txt
printf "\n" >> IonBeamEnergy.txt

echo "DATA" >> IonBeamEnergy.txt
##require a for loop which iterates between the x and y coordinates in the fashion of the piecewise multilinear data matrix input which states that if the coordinates are within the radius (Rbeam) pulled in above from the input file pull in the SRIM energies and if it is outside Rbeam, output 100 zeros

for x in {-20..20}
do
  for y in {-20..20}
  do
    circrad=$(echo "sqrt(($x/2000)^2 + ($y/2000)^2)" | bc -l)
    if (( $(echo "$Rbeam > $circrad" | bc -l) )); then
## Here, the current point is inside the beam, so dump the actual energies from SRIM
      FILE="Energy-List.txt"
      while read line; do
        energy=$(echo $line | awk '{print $3}')
        echo "$energy" >> IonBeamEnergy.txt
      done <$FILE
    else
## Here, the current point is outside the beam, so just dump one hundred zeroes
      for z in {1..100}
      do
        echo 0 >> IonBeamEnergy.txt
      done
    fi
  done
done


mv IonBeamEnergy.txt /home/jamie/projects/sahote/problems
