#include <iostream>
#include "loader.h"
#include "model.h"
#include "scoring.h"
#include <cmath>
#include <vector>
#include <string>

double scoreTrace(const Trace &trace){
    double total = 0.0;
    // skip transitions with 0 or 1 calls (edge case)
    if (trace.calls.size() < 2){
        return total;
    }
        for(int i=0; i+1<trace.calls.size(); i++){
        int from = trace.calls[i];
        int to = trace.calls[i+1];
        total += log(tpm[from][to]);
    }
    //divided by the number of transitions, otherwise one trace will be scored higher just because it is longer
    // n states -> n-1 transitions
    int transitions = trace.calls.size()-1;
    return total/transitions;
}


// mean score over a group of traces
double averageScore(const vector<Trace> &traces){
    double total = 0.0;
    int scored = 0;
    for(int i=0; i<traces.size(); i++){
        // skip transitions with 0 or 1 calls (edge case)
        if (traces[i].calls.size() < 2){
            continue;
        }

        total += scoreTrace(traces[i]);
        scored++;        
    }

    if (!scored){
        return 0.0;
    }
    
    double mean = total/scored;

    return mean;
}

void printScoreStats(string name, const vector<Trace> &traces){
    double total = 0.0;
    double lowest = 0.0;
    double highest = 0.0;
    int scored = 0;

    for(int i = 0; i < traces.size(); i++){
        if(traces[i].calls.size() < 2){
            continue;
        }

        double score = scoreTrace(traces[i]);
        total += score;

        if(scored == 0){
            lowest = score;
            highest = score;
        }
        if(score < lowest){
            lowest = score;
        }
        if(score > highest){
            highest = score;
        }
        scored++;
    }

    if(scored == 0){
        cout << name << ": nothing to score" << endl;
        return;
    }

    cout << name << ": " << scored << " scored, "
         << "average = " << total / scored << ", "
         << "lowest = " << lowest << ", "
         << "highest = " << highest << endl;
}

vector<double> scoreAll(const vector<Trace> &traces){
    vector<double> scores;
    for(int i = 0;  i < traces.size(); i++){
        if (traces[i].calls.size() < 2){
            continue;
        }

        scores.push_back(scoreTrace(traces[i]));
    } 

    return scores;
}
