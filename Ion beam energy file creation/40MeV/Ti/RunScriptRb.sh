#!/bin/bash

# Beginning of outer loop.
for a in {3..9}
do  
  # ===============================================
  # Beginning of inner loop.
  for b in 99800 99820 99840 99860 99880 99900 99920 99940 99960 99980
  do
    mpiexec -n 2 ~/projects/sahote/sahote-opt -i ~/projects/sahote/problems/SahoteTestLocalRb.i BCs/Coolant_Exit/value="$b" Outputs/file_base=velocity_"$b"_beam_current_1e-"$a"_Rb AuxKernels/HeatGenerationRate/beam_current=1e-"$a"
  done
  # End of inner loop.
  # ===============================================
done               
# End of outer loop.

