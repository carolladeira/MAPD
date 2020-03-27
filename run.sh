#!/bin/bash
#freq = ["0.2","0.5","1","2","5","10"]
#agents = ["10","20","30","40","50"]
#problem = ["SCOL_E", "SCOL_TA", "CBS_E", "CBS_TA", "AS_E", "AS_TA"]
#bestInd = 0 (nao cria um melhor individuo) 
#          1 (cria melhor individuo)


freq="10"
agents="10"
seed=3
problem="SCOL_E"

for s in  "22" "23" "24" "25" "26" "27" "28" "29" "30"; do
  for p in "SCOL_E"; do
   for i in "2"; do
      for j in "30"; do
         for k in 1; do
    	    ./exec_mapd $j $i $s $p $k
         done
      done
    done
  done
done
