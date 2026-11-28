#include "evaluate.h"
#include "scoring.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <random>
#include <cmath>

void ROCValues(const vector<double> &normalScores, const vector<double> &attackScores, string csvPath){
   ofstream out(csvPath);

   if(!out.is_open()){
       cout << "Error opening file" << endl;
       return;
   }

   vector<double> sorted = normalScores;
   sort(sorted.begin(), sorted.end());

   out << "threshold,false_alarm_rate,detection_rate" << endl;

   for(int i=0; i<sorted.size(); i++){
       double threshold = sorted[i];
       double fp = fractionBelow(sorted, threshold); // false alarms
       double tp = fractionBelow(attackScores, threshold); // detected proportion
       out << threshold << "," << fp << "," << tp << endl;
   }

   return;
}


string getAttackType(string folder){
    int last_ = folder.rfind('_');
    if(last_ == string::npos){
        return folder;
    }

    return folder.substr(0, last_);
}

void typewiseDetection(const vector<Trace> &attackTraces, double threshold){
    map<string, int>total;
    map<string, int>flagged;

    for(int i=0; i < attackTraces.size(); i++){
        if(attackTraces[i].calls.size() < 2){
            continue;
        }

        string type = getAttackType(attackTraces[i].folder);
        double score = scoreTrace(attackTraces[i]);

        total[type]++;
        if(score < threshold){
            flagged[type]++;
        }
    }

    cout << "type, traces, flagged, detection rate" << endl;
        for(auto entry : total){
            string type = entry.first;
            int count = entry.second;
            int caught = flagged[type];
            cout << type << ", " << count << ", " << caught << ", "
                 << (double)caught / count << endl;
        }
}


double findThreshold(vector<double> scores, double targetRate){
    sort(scores.begin(), scores.end());

    int index = targetRate * scores.size();

    //guard against 100&
    if(index >= scores.size()){
        index = scores.size() - 1;
    }

    return scores[index];
}

void splitScores(vector<double> scores, vector<double> &A, vector<double> &B){
    mt19937 rng(42);

    shuffle(scores.begin(), scores.end(), rng);

    int middle = scores.size()/2;

    for (int i=0; i < scores.size(); i++) {
        if(i < middle){
            A.push_back(scores[i]);
        }
        else {
            B.push_back(scores[i]);
        }
    }
}

double fractionBelow(const vector<double> &scores, double threshold){
    if(scores.size() == 0){
            return 0.0;
        }

    double num=0.0;
    for(int i=0; i < scores.size(); i++){
        if (scores[i] < threshold){
            num++;
        }
    }

    return num/scores.size();
}