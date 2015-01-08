#!/bin/bash                                                                                      


for i in {1..2..1}  ## energies
do         
        for j in {1..2..1}  ##sample thickness
	do
	    for k in {1..2..1} ##coolant thickness
            do
                        sed 's/<BEAMENERGY>/"$i"/'  TRIM-Script-sample-SS316.IN > TRIM1.IN
                        sed 's/<SAMPTHICK>/"$j"/' TRIM1.IN > TRIM2.IN
                        sed 's/<COOLTHICK>/"$k"/' TRIM2.IN > TRIM.IN
                        wine TRIM.exe
			touch vacancy_files/VAC-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i".txt
                        cp VACANCY.txt vacancy_files/VAC-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i".txt
			touch range_files/RANGE-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i".txt
                        cp RANGE.txt range_files/RANGE-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i".txt
                done
        done
done
