//
// Created by carol on 1/21/19.
//

#include <random>
#include "GA.h"

//#define IMPRIME

bool myfunction(Gene i, Gene j) { return (i.task < j.task); }

bool sort_fitness(Chromosome i, Chromosome j) { return (i.fitness < j.fitness); }

void GA_E::Initialize(vector<Agent> agents, vector<Task *> taskset) {
    this->copy_agents = agents;
    sizeTaskset = taskset.size();
    sizeAgents = agents.size();
    int j = 0;
    vector<int> t;


    for (int i = 0; i < sizePopulation_E; i++) {
        t.clear();

        for (int k = 0; k < sizeTaskset; k++) {
            int p = taskset[k]->id;
            t.push_back(p);

        }
        std::random_shuffle(begin(t), end(t));

        vector<Gene> genes;
        for (vector<Task *>::iterator it = taskset.begin(); it != taskset.end(); it++) {
            int id_agent = rand() % agents.size();
            Gene ind = Gene(id_agent, t[j], j);
            j++;

            genes.push_back(ind);
        }
        j = 0;
        Chromosome c = Chromosome(genes);
        pop.push_back(c);
    }

}
void GA_TA::Initialize(vector<Agent> agents, vector<Task *> taskset) {
    this->copy_agents = agents;
    sizeTaskset = taskset.size();
    sizeAgents = agents.size();
    int j = 0;
    vector<int> t;


    for (int i = 0; i < sizePopulation_TA; i++) {
        t.clear();

        for (int k = 0; k < sizeTaskset; k++) {
            int p = taskset[k]->id;
            t.push_back(p);

        }
        std::random_shuffle(begin(t), end(t));

        vector<Gene> genes;
        for (vector<Task *>::iterator it = taskset.begin(); it != taskset.end(); it++) {
            int id_agent = rand() % agents.size();
            Gene ind = Gene(id_agent, t[j], j);
            j++;

            genes.push_back(ind);
        }
        j = 0;
        Chromosome c = Chromosome(genes);
        pop.push_back(c);
    }

}
int GA_TA::Tournament() {
    float k = TOURNAMENT; //5% da populacao
    int size = (int) ceil(sizePopulation_TA * k);
    int ind, best = rand() % sizePopulation_TA;
    for (int i = 0; i < size; i++) {
        ind = rand() % sizePopulation_TA;
        if (pop[ind].fitness < pop[best].fitness) {
            best = ind;
        }
    }
    return best;
}

int GA_E::Tournament() {
    float k = TOURNAMENT; //5% da populacao
    int size = (int) ceil(sizePopulation_E * k);
    int ind, best = rand() % sizePopulation_E;
    for (int i = 0; i < size; i++) {
        ind = rand() % sizePopulation_E;
        if (pop[ind].fitness < pop[best].fitness) {
            best = ind;
        }
    }
    return best;
}

void GA::showPopulation() {

    for (int i = 0; i < pop.size(); i++) {
         cout << endl << "Cromossomo " << i << " -> ";
        for (int j = 0; j < pop[i].Individual.size(); j++) {
              cout <<pop[i].Individual[j].task<<"\t";
             cout <<pop[i].Individual[j].agent<<"\t";

        }
        cout << " " << pop[i].fitness;

    }
    cout << endl;
}

void GA::showPopulation(vector<Chromosome> p) {

    for (int i = 0; i < p.size(); i++) {
        // cout << endl << "Cromossomo " << i << " -> ";
        for (int j = 0; j < p[i].Individual.size(); j++) {
            //  cout <<pop[i].Individual[j].task<<"\t";
            // cout <<pop[i].Individual[j].agent<<"\t";

        }
        cout << " " << p[i].fitness;

    }
    cout << endl;
}

void GA::showIndividual(vector<Gene> ind) {
    cout << endl;

    for (int i = 0; i < ind.size(); i++) {
        cout << ind[i].task << "\t";

    }
    cout << "\t |";
    for (int i = 0; i < ind.size(); i++) {
        cout << ind[i].agent << "\t";


    }
    cout << endl;
}
int GA_E::getBestChromosome() {

    int best_ind = 0;
    int best_score = -1;

    for (int i = 0; i < sizePopulation_E; i++) {
        if (best_score == -1) {
            best_score = pop[i].fitness;
        }
        if (pop[i].fitness < best_score) {
            best_ind = i;
            best_score = pop[i].fitness;
        }
    }
    return best_ind;
}

int GA_TA::getBestChromosome() {

    int best_ind = 0;
    int best_score = -1;

    for (int i = 0; i < sizePopulation_TA; i++) {
        if (best_score == -1) {
            best_score = pop[i].fitness;
        }
        if (pop[i].fitness < best_score) {
            best_ind = i;
            best_score = pop[i].fitness;
        }
    }
    return best_ind;
}

void GA_TA::Mutation(vector<Gene> &individual) {
    double prob = ((double) rand() / ((double) RAND_MAX + 1));

    if (prob < MUTATION_RATE) {
        int pos1 = rand() % individual.size();
        int pos2 = rand() % individual.size();

        int task = individual[pos1].task;
        individual[pos1].task = individual[pos2].task;
        individual[pos2].task = task;
        //   cout<<endl<<"\t Mutacao de tarefa --------> Pos1: "<<pos1<<" Pos2: "<<pos2<<" Task1: "<<individual[pos1].task<<" Task2: "<<individual[pos2].task<<" ";

    } else {

        int pos1 = rand() % individual.size();
        // int ag = rand() % sizeAgents; ///aleatorio
        unsigned seed = rand();
        std::default_random_engine e(seed);
        int viz = (MUTATION_AGENT * sizeAgents);
        std::uniform_int_distribution<int> dis(-viz, viz);
        int myNumber=0;
        while(myNumber==0) myNumber= dis(e);
        //  int t  = rand() %  viz;           //entre os vizinhos de agente
        int ag = individual[pos1].agent;
       // showIndividual(individual);
        //cout<<endl<<"\t Mutacao de agente --------> Pos1: "<<pos1<<" antes: "<<individual[pos1].agent<<" vizinho: "<<myNumber<<" ";
        int id = ag + myNumber;
        if (id >= sizeAgents) {
            int id_agent = id % sizeAgents;
            individual[pos1].agent = copy_agents[id_agent].id;
        } else if (id < 0) {
            int id_agent = id * -1;
            individual[pos1].agent = copy_agents[id_agent].id;
        } else {
            individual[pos1].agent = copy_agents[id].id;
        }

    }

}

void GA_E::Mutation(vector<Gene> &individual) {
    double prob = ((double) rand() / ((double) RAND_MAX + 1));

    if (prob < MUTATION_RATE) {
        int pos1 = rand() % individual.size();
        int pos2 = rand() % individual.size();

        int task = individual[pos1].task;
        individual[pos1].task = individual[pos2].task;
        individual[pos2].task = task;
        //   cout<<endl<<"\t Mutacao de tarefa --------> Pos1: "<<pos1<<" Pos2: "<<pos2<<" Task1: "<<individual[pos1].task<<" Task2: "<<individual[pos2].task<<" ";

    }
}

void GA::Crossover(vector<Gene> &offspring1, vector<Gene> &offspring2) {

    double prob = ((double) rand() / ((double) RAND_MAX + 1));
    if (prob < CROSSOVER_RATE) {
//               cout<<endl<<" -----------CROSSOVER-------- "<<" ";
//
//        showIndividual(offspring1);
//        showIndividual(offspring2);

        vector<Gene> temp;
        temp.resize(sizeTaskset);
        int p = rand() % sizeTaskset;
        temp = offspring1;

        int number1 = rand() % sizeTaskset;
        int number2 = rand() % sizeTaskset;

        int start = fmin(number1, number2);
        int end = fmax(number1, number2);

        std::vector<int> child1;
        std::vector<int> child2;
         // cout<<start<<" "<<end<<endl;

        for (int i = start; i < end; i++) {
            child1.push_back(offspring1[i].task);
            child2.push_back(offspring2[i].task);
        }

        int geneIndex = 0;
        int geneInparent1 = 0;
        int geneInparent2 = 0;

        for (int i = 0; i < sizeTaskset; i++) {
            geneIndex = (end + i) % sizeTaskset;
            geneInparent1 = offspring1[geneIndex].task;
            geneInparent2 = offspring2[geneIndex].task;

            bool is_there = false;
            for (int i1 = 0; i1 < child1.size(); i1++) {
                if (child1[i1] == geneInparent2) {
                    is_there = true;
                }
            }
            if (!is_there) {
                child1.push_back(geneInparent2);
            }

            bool is_there1 = false;
            for (int i1 = 0; i1 < child2.size(); i1++) {
                if (child2[i1] == geneInparent1) {
                    is_there1 = true;
                }
            }
            if (!is_there1) {
                child2.push_back(geneInparent1);
            }
        }

        std::rotate(child1.rbegin(), child1.rbegin() + start, child1.rend());
        std::rotate(child2.rbegin(), child2.rbegin() + start, child2.rend());

        for (int i = 0; i < start; i++) {
            offspring1[i].agent = offspring2[i].agent;
            offspring2[i].agent = temp[i].agent;
        }

        for (int i = 0; i < sizeTaskset; i++) {
            offspring1[i].task = child2[i];
            offspring2[i].task = child1[i];
        }

//        showIndividual(offspring1);
//        showIndividual(offspring2);

    }
}

void GA_E::Crossover(vector<Gene> &offspring1, vector<Gene> &offspring2) {

    double prob = ((double) rand() / ((double) RAND_MAX + 1));
    if (prob < CROSSOVER_RATE) {
       //cout<<endl<<" -----------CROSSOVER-------- "<<" ";
       //showIndividual(offspring1);
       //showIndividual(offspring2);

        vector<Gene> temp;
        temp.resize(sizeTaskset);
        int p = rand() % sizeTaskset;
        temp = offspring1;

        int number1 = rand() % sizeTaskset;
        int number2 = rand() % sizeTaskset;

        int start = fmin(number1, number2);
        int end = fmax(number1, number2);

        std::vector<int> child1;
        std::vector<int> child2;
          //cout<<start<<" "<<end<<endl;

        for (int i = start; i < end; i++) {
            child1.push_back(offspring1[i].task);
            child2.push_back(offspring2[i].task);
        }

        int geneIndex = 0;
        int geneInparent1 = 0;
        int geneInparent2 = 0;

        for (int i = 0; i < sizeTaskset; i++) {
            geneIndex = (end + i) % sizeTaskset;
            geneInparent1 = offspring1[geneIndex].task;
            geneInparent2 = offspring2[geneIndex].task;

            bool is_there = false;
            for (int i1 = 0; i1 < child1.size(); i1++) {
                if (child1[i1] == geneInparent2) {
                    is_there = true;
                }
            }
            if (!is_there) {
                child1.push_back(geneInparent2);
            }

            bool is_there1 = false;
            for (int i1 = 0; i1 < child2.size(); i1++) {
                if (child2[i1] == geneInparent1) {
                    is_there1 = true;
                }
            }
            if (!is_there1) {
                child2.push_back(geneInparent1);
            }
        }

        std::rotate(child1.rbegin(), child1.rbegin() + start, child1.rend());
        std::rotate(child2.rbegin(), child2.rbegin() + start, child2.rend());

        for (int i = 0; i < sizeTaskset; i++) {
            offspring1[i].task = child2[i];
            offspring2[i].task = child1[i];
        }

     //   showIndividual(offspring1);
      //  showIndividual(offspring2);

    }
}

float GA::getFitness(vector<Gene> &individual, Token token) {

    vector<vector<int>> list_task;
    list_task.resize(sizeAgents);

    for (int i = 0; i < individual.size(); i++) {
        int n_task = individual[i].task;
        int n_agent = individual[i].agent;
        list_task[n_agent].push_back(n_task);
    }

    Task n;
    int start = 0, makespan = 0;
    for (int i = 0; i < list_task.size(); i++) {

        int loc = copy_agents[i].loc;
        int time = copy_agents[i].finish_time;
        for (int j = 0; j < list_task[i].size(); j++) {
            n = task_total[list_task[i][j]];
            if (j == 0) {
                //int release_time = n.release_time;
                int dist = n.start->h_val[loc];
                start = time + dist;
                loc = n.start->loc;
                if (j + 1 != list_task[i].size()) continue;
            } else if (j <= list_task[i].size() - 1) {
                Task n = task_total[list_task[i][j - 1]];
                Task n2 = task_total[list_task[i][j]];
                int release_time = n2.release_time;
                int dist_t1 = n.goal->h_val[loc];
                loc = n.goal->loc;
                int dist_t2 = n2.start->h_val[loc];
                loc = n2.start->loc;
                start = start + dist_t1 + dist_t2;
                // start = max(start + dist_t1 + dist_t2, release_time);
                if (j + 1 != list_task[i].size()) continue;

            }
            int dist_t1 = n.goal->h_val[loc];
            start = start + dist_t1;
            // makespan = start;
        }
        if (start > makespan) makespan = start;

    }
   // cout<<" mks: "<<makespan ;

    return makespan;
}

int GA_E::escalonamento(vector<Gene> &individual) {
    vector<Agent> agents = copy_agents;
    Task n;
    int id_agent;
    for(int i = 0; i < individual.size(); i++){
        int id_task = individual[i].task;
        n = task_total[id_task];
        int release_time = n.release_time;
        int loc_start_task = n.start->loc;
        int loc_goal_task = n.goal->loc;
        id_agent = findAgentCloser(release_time, loc_start_task, agents);
        individual[i].agent = id_agent;
        int ft =  Dis[agents[id_agent].loc][loc_start_task] + agents[id_agent].finish_time;
       // int ft =  max(Dis[agents[id_agent].loc][loc_start_task] + agents[id_agent].finish_time, release_time);

        // cout<<endl<<"Agente "<<id_agent<<" pega tarefa "<<id_task <<" Rt: "<<release_time<<" loc: "<<agents[id_agent].loc<<" -> "<<loc_start_task<<"[";
       // cout<<ft<<"] -> "<<loc_goal_task<<"["<<Dis[loc_start_task][loc_goal_task]<<"] = "<< ft+ Dis[loc_start_task][loc_goal_task];

        agents[id_agent].finish_time = ft+ Dis[loc_start_task][loc_goal_task] ;
        agents[id_agent].loc = loc_goal_task;
    }
    int fitness = 0 ;
    Agent ag;
    for(int i =0; i <agents.size(); i++){
        ag = agents[i];
        int finish_time = ag.finish_time;
        if(finish_time > fitness){
            fitness = finish_time;
        }
    }
    //cout<<"ft: "<<fitness ;
    return fitness;
}

int GA_E::findAgentCloser(int release_time, int loc_start, vector<Agent> agents) {
    Agent ag;
    int best_ag, best_t = 1000000 ;
    for(int i =0 ; i < copy_agents.size(); i++){
        ag = agents[i];
        int finish_time = ag.finish_time;
        int loc = ag.loc;
        int dist = Dis[loc][loc_start];
       // int t_ateTask = max(dist + finish_time, release_time);
        int t_ateTask = dist + finish_time;
        if(t_ateTask < best_t){
            best_ag = ag.id;
            best_t = t_ateTask;
        }
    }
    return  best_ag;
}

vector<vector<int>> GA_E::run_GA(vector<Agent> agents, vector<Task *> taskset, Token token, vector<Task> task_total,
                                 vector<vector<int> > Dis, bool bestInd) {
    pop.clear();
    this->task_total = task_total;
    this->taskset = taskset;
    this->Dis = Dis;
    vector<Agent> order_agents;
    Token token_ag = token;

    std::clock_t start;
    double duration = 0;
    start = std::clock();

    Initialize(agents, taskset);

    if(bestInd){
        pop.pop_back();
        createBestInd();
    }

#ifdef IMPRIME
    string res_file = "/home/carol/Documents/result-ga-e.csv ";
    ofstream fout(res_file, ios::app);
    if (!fout)
        cout << "ERR0";
#endif

    for (int i = 0; i < sizePopulation_E; i++) {
        pop[i].fitness = escalonamento(pop[i].Individual);

    }
    int i = 0;
    while (i < GENERATIONS) {
        int cPop = 0;
        vector<Chromosome> temp;
        temp = pop;
        vector<Chromosome> newPop;
        Chromosome off1;
        Chromosome off2;

        while (cPop < sizePopulation_E) {
            int offspring1 = Tournament();
            int offspring2 = Tournament();

            off1 = pop[offspring1];
            off2 = pop[offspring2];
            Crossover(off1.Individual, off2.Individual);
            Mutation(off1.Individual);
            Mutation(off2.Individual);
            cPop++;
            cPop++;
            newPop.push_back(off1);
            newPop.push_back(off2);
        }

        for (int i = 0; i < sizePopulation_E; i++) {
            newPop[i].fitness =  escalonamento(newPop[i].Individual);
        }

        std::sort(pop.begin(), pop.end(), sort_fitness);
        std::sort(newPop.begin(), newPop.end(), sort_fitness);


        int e = 0;
        for(int i = ceil(sizePopulation_E * ELITISM) ; i <sizePopulation_E; i++){
            pop[i] = newPop[e];
            e++;
        }
        //duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        i++;
#ifdef IMPRIME
        int id = getBestChromosome();
        double best_fitness = pop[id].fitness;
        fout << cont << "," << i << "," << best_fitness << "," << GENERATIONS << "," << sizePopulation_E << "," << CROSSOVER_RATE << "," << MUTATION_RATE << "," << MUTATION_AGENT << "," << TOURNAMENT << "," << ELITISM << endl;
   //fout.close();
    #endif
    }
    int id = getBestChromosome();
    //cout <<"Duration: "<<duration<< " Fitness: " << pop[id].fitness <<" Generations:" <<i<<endl;

    vector<vector<int>> list_task;
    list_task.resize(sizeAgents);

    for(int i = 0; i < pop[id].Individual.size(); i++){
        int n_task = pop[id].Individual[i].task;
        int n_agent = pop[id].Individual[i].agent;
        list_task[n_agent].push_back(n_task);
    }
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    tempo_GA = duration;
    this->cont = cont + 1;
    return list_task;
}

void GA_E::createBestInd() {
    int menor = INT_MAX;
    int id_agent;
    int id_task;
    int loc_i, loc_f, c = 0;
    vector<Task *> copy_taskset = taskset;
    vector<Gene> genes;
    vector<Agent> agents = copy_agents;

    while (c < sizeTaskset) {
        for (int i = 0; i < copy_taskset.size(); i++) {
            for (int j = 0; j < sizeAgents; j++) {
                loc_i = agents[j].loc;
                loc_f = copy_taskset[i]->start->loc;
                if (Dis[loc_i][loc_f] + agents[j].finish_time < menor) {
                    menor = Dis[loc_i][loc_f] + agents[j].finish_time;
                    id_agent = agents[j].id;
                    id_task = i;
                }
            }
        }
        menor = INT_MAX;
        Gene ind;
        int id = copy_taskset[id_task]->id;
       // cout<<"Agente "<<id_agent<<" com tarefa "<<id<<endl;
        ind = Gene(id_agent, id, c);
        genes.push_back(ind);
        c++;
        agents[id_agent].finish_time = Dis[agents[id_agent].loc][copy_taskset[id_task]->start->loc] +
                                       Dis[copy_taskset[id_task]->start->loc][copy_taskset[id_task]->goal->loc] +
                                       agents[id_agent].finish_time;
        agents[id_agent].loc = copy_taskset[id_task]->goal->loc;
        //  cout<<" tempo final "<<copy_agents[id_agent].finish_time<<endl;
        copy_taskset.erase(copy_taskset.begin() + id_task);
    }
    Chromosome novo = Chromosome(genes);
    pop.push_back(novo);
}

void GA_TA::createBestInd() {
    int menor = INT_MAX;
    int id_agent;
    int id_task;
    int loc_i, loc_f, c = 0;
    vector<Task *> copy_taskset = taskset;
    vector<Gene> genes;
    vector<Agent> agents = copy_agents;

    while (c < sizeTaskset) {
        for (int i = 0; i < copy_taskset.size(); i++) {
            for (int j = 0; j < sizeAgents; j++) {
                loc_i = agents[j].loc;
                loc_f = copy_taskset[i]->start->loc;
                if (Dis[loc_i][loc_f] + agents[j].finish_time < menor) {
                    menor = Dis[loc_i][loc_f] + agents[j].finish_time;
                    id_agent = j;
                    id_task = i;
                }
            }
        }
        menor = INT_MAX;
        Gene ind;
        int id = copy_taskset[id_task]->id;
        //  cout<<"Agente "<<id_agent<<" com tarefa "<<id;
        ind = Gene(id_agent, id, c);
        genes.push_back(ind);
        c++;
        agents[id_agent].finish_time = Dis[agents[id_agent].loc][copy_taskset[id_task]->start->loc] +
                                       Dis[copy_taskset[id_task]->start->loc][copy_taskset[id_task]->goal->loc] +
                                       agents[id_agent].finish_time;
        agents[id_agent].loc = copy_taskset[id_task]->goal->loc;
        //  cout<<" tempo final "<<copy_agents[id_agent].finish_time<<endl;
        copy_taskset.erase(copy_taskset.begin() + id_task);
    }
    Chromosome novo = Chromosome(genes);
    pop.push_back(novo);
}

vector<vector<int>> GA_TA::run_GA(vector<Agent> agents, vector<Task *> taskset, Token token, vector<Task> task_total,
                                  vector<vector<int> > Dis, bool bestInd) {
    pop.clear();
    this->task_total = task_total;
    this->taskset = taskset;
    this->Dis = Dis;
    vector<Agent> order_agents;
    Token token_ag = token;

    std::clock_t start;
    double duration =0;
    start = std::clock();

    Initialize(agents, taskset);
    if(bestInd){
        pop.pop_back();
        createBestInd();
    }


#ifdef IMPRIME
    string res_file = "/home/carol/Documents/result-ga-ta.csv "; 
    ofstream fout(res_file, ios::app);
    if (!fout) cout << "ERR0";
#endif

    for (int i = 0; i < sizePopulation_TA; i++) {
        pop[i].fitness = getFitness(pop[i].Individual, token_ag);
    }
    int i = 0;
    while (i < GENERATIONS) {
        int cPop = 0;
        vector<Chromosome> temp;
        temp = pop;
        vector<Chromosome> newPop;
        Chromosome off1;
        Chromosome off2;

        while (cPop < sizePopulation_TA) {
            int offspring1 = Tournament();
            int offspring2 = Tournament();

            off1 = pop[offspring1];
            off2 = pop[offspring2];

            Crossover(off1.Individual, off2.Individual);
            Mutation(off1.Individual);
            Mutation(off2.Individual);
            cPop++;
            cPop++;
            newPop.push_back(off1);
            newPop.push_back(off2);
        }

        for (int i = 0; i < sizePopulation_TA; i++) {
            newPop[i].fitness = getFitness(newPop[i].Individual, token_ag);
        }
        std::sort(pop.begin(), pop.end(), sort_fitness);
        std::sort(newPop.begin(), newPop.end(), sort_fitness);

        int e = 0;
        for (int i = ceil(sizePopulation_TA * ELITISM); i < sizePopulation_TA; i++) {
            pop[i] = newPop[e];
            e++;
        }

        i++;
#ifdef IMPRIME
        int id = getBestChromosome();
        double best_fitness = pop[id].fitness;
        fout <<cont<<","<< i << ","<< best_fitness <<","<<GENERATIONS<<","<<sizePopulation_TA<<","<<CROSSOVER_RATE<<","<<MUTATION_RATE<<","<<MUTATION_AGENT<<","<<TOURNAMENT<<","<< ELITISM<< endl;
   fout.close();
    #endif
    }

    int id = getBestChromosome();

   // cout << " Fitness: " << pop[id].fitness <<endl;

    vector<vector<int>> list_task;
    list_task.resize(sizeAgents);
    for (int i = 0; i < pop[id].Individual.size(); i++) {
        int n_task = pop[id].Individual[i].task;
        int n_agent = pop[id].Individual[i].agent;
        list_task[n_agent].push_back(n_task);
    }
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    tempo_GA = duration;
    this->cont = cont + 1;
    return list_task;
}
