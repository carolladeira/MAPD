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

for s in  "29" "28" "27" "26" "25" "24" "23" "22" "21"; do
  for p in "CBS_E"; do
   for i in "0.2" "0.5" "1" "2" "5" "10"; do
      for j in "10" "20" "30" "40" "50"; do
         for k in 0 1; do
    	    ./exec_mapd $j $i $s $p $k
         done
      done
    done
  done
done
