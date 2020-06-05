#!/bin/bash
#freq = ["0.2","0.5","1","2","5","10"]
#agents = ["10","20","30","40","50"]
#seed = [1..30]
#problem = ["SCOL_E", "SCOL_TA", "CBS_E", "CBS_TA", "AS_E", "AS_TA"]
#bestInd = 0 (nao cria um melhor individuo) 
#          1 (cria melhor individuo)


# ./exec_mapd agents freq seed problem bestInd

for se in {1..25};do
	for s in "10" "20" "30" "40" "50"; do
	    ./exec_mapd $s 10 $se CBS_TA 1
	    ./exec_mapd $s 10 $se AS_TA 1
	  #  ./exec_mapd $s 10 $se SCOL_TA 1
	done
done

for se in {1..25};do
	for s in "10" "20" "30" "40" "50"; do
	    ./exec_mapd $s 5 $se CBS_TA 1
	    ./exec_mapd $s 5 $se AS_TA 1
	  #  ./exec_mapd $s 5 $se SCOL_TA 1
	done
done

for se in {1..25};do
	for s in "10" "20" "30" "40" "50"; do
	    ./exec_mapd $s 2 $se CBS_TA 1
	    ./exec_mapd $s 2 $se AS_TA 1
	    #./exec_mapd $s 2 $se SCOL_TA 1
	done
done

for se in {1..25};do
	for s in "10" "20" "30" "40" "50"; do
	    ./exec_mapd $s 1 $se CBS_TA 1
	    ./exec_mapd $s 1 $se AS_TA 1
	    #./exec_mapd $s 2 $se SCOL_TA 1
	done
done
