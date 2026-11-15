#include "model.h""
#include "scoring.h"
#include <cmath>

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