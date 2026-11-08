#include "loader.h"
#include "model.h"
#include <vector>
#include <iostream>

int main(){
    vector<Trace> training   = loadDirRecursive("data/ADFA-LD/Training_Data_Master");
    vector<Trace> validation = loadDirRecursive("data/ADFA-LD/Validation_Data_Master");
    vector<Trace> attack     = loadDirRecursive("data/ADFA-LD/Attack_Data_Master");
    
    printSummary("training", training);
    printSummary("validation", validation);
    printSummary("attack", attack);

    countTransitions(training);
    calcProbability();

    double worstError = 0.0;
    for (int i = 0; i < N; i++) {
        double rowSum = 0.0;
        for (int j = 0; j < N; j++) {
            rowSum += tpm[i][j];
        }
        double error = rowSum - 1.0;
        if (error < 0) error = -error;      // absolute value
        if (error > worstError) worstError = error;
    }
    
    cout << "Worst row-sum error: " << worstError << endl;   // should be tiny, like 1e-15
    int from = 6;
    int bestTo = 0;
    for (int j = 0; j < N; j++) {
        if (tpm[from][j] > tpm[from][bestTo]) bestTo = j;
    }
    cout << "From " << from << ", most likely next call is " << bestTo
         << " with probability " << tpm[from][bestTo] << endl;
    
    return 0;
}