#include <iostream>
#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>      /* printf, NULL */
#include <iomanip>
#include <ostream>
#include <fstream>
#include <string>
#include "include/Timer.hpp"
#include "Simulation.h"

using namespace std;


int run(string ag, string fr,  int seed, string problem, int bestInd) {


    Simulation *simu;
    srand(seed);
    string ind ="sI";

    if(bestInd == 1) ind = "cI";

    cout <<"SEED: "<<seed<< " | " << problem <<" | "<< ind << " ============= AG: " << ag << " - F: " << fr << " =============" << endl;

    string map_file = " ";
    string task_file = " ";
    string res_file = " ";
    string p = "/home/carol/Desktop/MAPD";
    if(stoi(ag)> 50){
      cout << "LARGE" << endl;
      map_file = p + "/Instances/large/kiva-" + ag + "-1000-50.map";     //LARGE
      task_file = p+"/Instances/large/kiva-1000-50.task";              //LARGE
      res_file = p+"/Resultados/large" + ind + "-" + problem + ".csv"; //LARGE
    }else{
      cout << "SMALL" << endl;
      map_file = p+"/Instances/small/kiva-" + ag + "-500-5.map";       //SMALL
      task_file = p+"/Instances/small/kiva-" + fr + ".task";           //SMALL
      res_file = p+"/Resultados/small" + ind + "-" + problem + ".csv"; //SMALL
    }
    simu = new Simulation(map_file, task_file, 0);
    std::clock_t c_start = std::clock();

//    simu->run_HungarianMethod();

    if(problem == "SCOL_E") simu->run_SCol_E(bestInd);
    else if(problem == "SCOL_TA") simu->run_SCol_TA(bestInd);
    else if(problem == "CBS_E") simu->run_CBS_E(bestInd);
    else if(problem == "CBS_TA") simu->run_CBS_TA(bestInd);
    else if(problem == "AS_E") simu->run_AS_E(bestInd);
    else if(problem == "AS_TA") simu->run_AS_TA(bestInd);

    std::clock_t c_end = std::clock();

    int mksn = simu->mkspn();
    cout<<"Mksn: "<<mksn<<endl;
    float service_time = simu->service_time();
    cout<<"Service time: "<<service_time<<endl;
    double tempoTotalGA = simu->tempoGA();
    cout<<"Tempo GA: "<<tempoTotalGA<<endl;
    double tempoTotalPathPlan = simu->tempoPathPlan();
    cout<<"Tempo Path: "<<tempoTotalPathPlan<<endl;
    std::cout << std::fixed << std::setprecision(2) << "CPU time used: " << (c_end - c_start) / CLOCKS_PER_SEC <<endl;


   ofstream fout(res_file, ios::app);
   if (!fout) cout << "ERR0 - salvar arquivo";
   fout << fr << "," << ag << "," << seed << "," << mksn << "," <<service_time<<","<< (c_end - c_start) / CLOCKS_PER_SEC << ","<<tempoTotalGA <<","<<tempoTotalPathPlan<< endl;
   fout.close();

    delete simu;
    return 0;
}

int main(int argc, char *argv[]) {

   // run("10", "10", 1, "SCOL_E", 1 );
 run( argv[1], argv[2], atoi(argv[3]), argv[4], atoi(argv[5]));


   return 0;
}
