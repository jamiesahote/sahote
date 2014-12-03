#!/bin/bash


for i in {10000..40000..5000}; do  ## energies
	for j in {0.5..3..0.5}; do ##sample thickness
		for k in {0.5..3..0.5}; do  ##coolant thickness

 			sed \"s/<BEAMENERGY\>/"$i"/\" TRIM-Script-sample-SS316.IN > TRIM1.IN
			sed \"s/<SAMPTHICK\>/"$j”/\” TRIM1.IN > TRIM2.IN
			sed \"s/<COOLTHICK\>/"$k”/\” TRIM2.IN > TRIM.IN
			wine TRIM.exe
			cp VACANCY.txt vacancy_files/VAC-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i”.txt
			cp RANGE.txt range_files/RANGE-SS316COOLANT-CTHICK-"$k"-SAMPLETHICK-"$j"-E-"$i”.txt
		done
	done
done
