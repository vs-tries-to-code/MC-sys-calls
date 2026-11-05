#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int N = 450;
const double SMOOTH = 1;

vector<vector<double>> tpm(N, vector<double>(N, 0.0));

vector<int> getFile(string path){
    vector<int> calls;
    ifstream file(path);

    if(!file.is_open()){
        cout << "Couldn't open" << endl;
        return calls;
    }

    int num;
    while(file >> num){
        calls.push_back(num);
    }

    return calls;
}

vector<vector<int>> loadDir(string dir){
    vector<vector<int>> trace;
    for (const auto& entry : filesystem::directory_iterator(dir)){
        trace.push_back(getFile(entry.path().string()));
    }
    return trace;
}

void countTransitions(vector<vector<int>>& trace){
    for(int i = 0; i < trace.size(); i++){
        for(int j = 0; j+1 < trace[i].size(); j++){
                int from  = trace[i][j];
                int to = trace[i][j+1];
                tpm[from][to]++;
        }
    }
}

void calcProbability(){
    for(int i = 0; i < tpm.size(); i++){
        int rCount = 0;
        for(int j = 0; j < N; j++){
            tpm[i][j] += SMOOTH;
            rCount += tpm[i][j];
        }

        for(int k = 0; k < N; k++){
            tpm[i][k] = tpm[i][k] / rCount;
        }
    }
}

int main(){
    vector<vector<int>> traces = loadDir("ADFA-LD/Attack_Data_Master/Adduser_1");
    for(int i=0; i < traces.size(); i++){
        for(int j = 0; j < traces[i].size(); j++){
            cout << traces[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}