#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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