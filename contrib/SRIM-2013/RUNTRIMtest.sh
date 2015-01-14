#!/bin/bash                                                                                     


for energies in {10000..40000..5000}  ## energies
do
    for j in {0.5..3..0.5}  ##sample thickness
    do
	for k in {0.5..3..0.5} ##coolant thickness
        do
	    sed "s/<BEAMENERGY>/$energies/"  TRIM-Script-sample-SS316.IN > TRIM1.IN
            sed "s/<SAMPTHICK>/$j/" TRIM1.IN > TRIM2.IN
            sed "s/<COOLTHICK>/$k/" TRIM2.IN > TRIM.IN
            wine TRIM.exe
	    touch vacancy_files/VAC-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$energies".txt
            cp VACANCY.txt vacancy_files/VAC-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$energies".txt
	    touch range_files/RANGE-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$energies".txt
            cp RANGE.txt range_files/RANGE-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$energies".txt
	done
    done
done
