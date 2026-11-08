#include "model.h"
#include <vector>

vector<vector<double>> tpm(N, vector<double>(N, 0.0));
void countTransitions(vector<Trace>& traces){
    for(int i = 0; i < traces.size(); i++){
        for(int j = 0; j+1 < traces[i].calls.size(); j++){
                int from  = traces[i].calls[j];
                int to = traces[i].calls[j+1];
                tpm[from][to]++;
        }
    }
}

void calcProbability(){
    for(int i = 0; i < tpm.size(); i++){
        double rCount = 0;
        for(int j = 0; j < N; j++){
            tpm[i][j] += SMOOTH;
            rCount += tpm[i][j];
        }

        for(int k = 0; k < N; k++){
            tpm[i][k] = tpm[i][k] / rCount;
        }
    }
}
