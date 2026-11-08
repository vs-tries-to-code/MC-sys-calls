#pragma once
#include "loader.h"
#include <vector>

int main(){
    vector<Trace> training   = loadDirRecursive("ADFA-LD/Training_Data_Master");
    vector<Trace> validation = loadDirRecursive("ADFA-LD/Validation_Data_Master");
    vector<Trace> attack     = loadDirRecursive("ADFA-LD/Attack_Data_Master");
    
    printSummary("training", training);
    printSummary("validation", validation);
    printSummary("attack", attack);

    return 0;
}