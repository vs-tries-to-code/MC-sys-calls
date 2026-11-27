#include "evaluate.h"
#include "scoring.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

void ROCValues(vector<double> &normalScores, vector<double> &attackScores, string csvPath){
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