#include "loader.h"
#include<fstream>
#include <ostream>
#include<vector>
#include<iostream>
#include<filesystem>
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

vector<Trace> loadDirRecursive(string dir){
    vector<Trace> traces;
    for (const auto& entry : filesystem::recursive_directory_iterator(dir)){
        if (!entry.is_regular_file()){
            continue;
        }

        Trace t;
        t.calls = getFile(entry.path().string());
        t.folder = entry.path().parent_path().filename().string();

        traces.push_back(t);
    }
    
    return traces;
}

void printSummary(string name, const vector<Trace> &traces){
    int largestCall = 0;
    int emptyTraces = 0;
    for (int i =0; i < traces.size(); i++){
        if (traces[i].calls.size() == 0){
            emptyTraces++;
        }
        for(int j=0; j < traces[i].calls.size(); j++){
            if (traces[i].calls[j] > largestCall){
                largestCall = traces[i].calls[j];
            }
        }
    }

    cout << "Folder name : " << name << endl; 
    cout << "Largest call : " << largestCall << endl;
    cout << "Empty traces : " << emptyTraces << endl;
    return;
}