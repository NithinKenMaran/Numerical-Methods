#!/bin/bash

gcc ee23b050_hem.c -o hem
for i in {2..35}; do
 
    j=$(( $i + 1 ))
 
    result_i=$(./hem $i)
    result_i1=$(./hem $j)

    
    ratio=$(echo "scale=2; $result_i1/$result_i" | bc)
    
    echo "$i $result_i $ratio" >> ee23b050_hem.txt

    
    

done

gnuplot -p ee23b050_hemgp.txt