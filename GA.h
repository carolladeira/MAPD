
#ifndef MAPDAG_GA_H
#define MAPDAG_GA_H

#include "Agent.h"
#include <iostream>
#include "dlib/optimization/max_cost_assignment.h"


#define sizePopulation_TA           20
#define sizePopulation_E            20

#define CROSSOVER_RATE            0.8
#define MUTATION_RATE             0.5
#define TOURNAMENT                0.01
#define ELITISM                   0.04
#define MUTATION_AGENT            0.3
#define GENERATIONS               50
#define TIMEOUT                   180


class Gene{
public:
    int agent;
    int task;
    int order;

    Gene(int ag, float t, int o):  agent(ag), task(t), order(o) {}

    Gene() {}
};
class Chromosome{
public:
    double fitness;
    vector<Gene> Individual;

    Chromosome(vector<Gene> Individual): fitness(-1), Individual(Individual) {}
    Chromosome () {};
};

class GA {
public:
    int sizeTaskset;
    int sizeAgents;

    vector<Agent>copy_agents;
    vector<Task *> taskset;

   vector<Chromosome> pop;
    vector<int>score;

    vector<vector<int> > Dis;

    vector<Task> task_total;

    double tempo_GA;


    void Crossover(vector<Gene> &offspring1, vector<Gene> &offspring2);
    float getFitness(vector<Gene> &individual, Token token);

    //void createBestInd();

    void showPopulation();
    void showPopulation(vector<Chromosome> temp);
    void showIndividual(vector<Gene> ind);

    };

class GA_E: public GA{
public:
    int cont = 0;
    int escalonamento(vector<Gene> &individual);
    int findAgentCloser(int release_time, int loc_start, vector<Agent> agents);

    vector<vector<int>> run_GA(vector<Agent> agents, vector<Task*> taskset, Token token, vector<Task> task_total, vector<vector<int> > Dis, bool bestInd);
    void createBestInd();
    void Crossover(vector<Gene> &offspring1, vector<Gene> &offspring2);
    void Mutation(vector<Gene> &individual);
    int Tournament();
    int getBestChromosome();
    void Initialize(vector<Agent> agents, vector<Task*> taskset);
};

class GA_TA:public GA{
public:
    int cont = 0;

    vector<vector<int>> run_GA(vector<Agent> agents, vector<Task*> taskset, Token token, vector<Task> task_total, vector<vector<int> > Dis, bool bestInd);
    void createBestInd();
    int Tournament();
    void Mutation(vector<Gene>& individual);

    int getBestChromosome();
    void Initialize(vector<Agent> agents, vector<Task*> taskset);
};


#endif //MAPDAG_GA_H
