//
// Created by carol on 12/17/18.
//

#ifndef MAPD_SIMULATION_H
#define MAPD_SIMULATION_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include "dlib/optimization/max_cost_assignment.h"
#include "ICBSSearch.h"
#include "egraph_reader.h"

#include "Agent.h"
#include "Endpoint.h"
#include "GA.h"
#include "map_loader.h"

using namespace std;

class Simulation {
public:
    int time;
    float computation_time;

    int row, col;
    int maxtime;
    Token token;
    int num_agents;
    int num_endpoint;

    vector<bool> my_map;
    int timestep;

    double tempoTotalGA;
    double tempoTotalPathPlan;

    string tour_file;
    string out_file;
    string tsp_file;

    vector<queue<Task*> > TSP_seqs;
    vector<int> TSP_len;
    vector<int> TSP_agent;
    vector<vector<int> > Dis;
    vector<Task> tasks_total;

    int t_task, num_task, sizeTaskset;

    vector<vector<int>> list_agents;

    vector<Agent> agents_order;

    vector<Agent> agents;
    vector<Endpoint> endpoints;

    vector<vector<Task>> taskset;
    vector<Task*> list_taskset;
    vector<int>score;

    void readTourFile(string tourFile);
    void BFS();

    Simulation(string map, string task, float frequency);

    void LoadMap(string arq);
    void LoadTask(string arq, float frequency);

    void run_AS_E(bool bestInd);
    void run_AS_TA(bool bestInd);


    void run_SCol_E(bool bestInd);
    void run_SCol_TA(bool bestInd);

    void run_CBS_E(bool bestInd);
    void run_CBS_TA(bool bestInd);


    void run_HungarianMethod();
    int nearestAgent();

    bool PathFinding(vector<Agent*> &ags, const vector<vector<int> > &cons_paths);

    vector<int> CalcCost(Agent* ag);


    void printPaths();
    void printMap();
    void printTasks();
    void printList_taskset();

    int getShortTime();

    void run_TP();

    void showTask(string arq, float t, int c, string tam);
    void showPathAgents(string arq);

    ///save
    void SavePath();
    void SaveTask(string file, string arq);

    int mkspn();
    float service_time();
    double tempoGA() { return this->tempoTotalGA; }
    double tempoPathPlan()  { return this->tempoTotalPathPlan; }

    bool sort_assignment(Chromosome i, Chromosome j) { return (i.fitness < j.fitness); }

    void deleteTask_id(int id);

    ///Para eu conferir
    bool testCollision();
    bool TestConstraints();


};


#endif //MAPD_SIMULATION_H
