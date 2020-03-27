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

for s in "1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15"; do
  for p in "AS_TA"; do
      for j in "100" "200" "300" "400" "500"; do
         for k in 0 1; do
    	    ./exec_mapd $j 1 $s $p $k
         done
      done
    done
  done
done
