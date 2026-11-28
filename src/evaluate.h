#pragma once
#include <vector>
#include <string>
#include "loader.h"
using namespace std;

void ROCValues(const vector<double> &normalScores, const vector<double> &attackScores, string csvPath);
double findThreshold(vector<double> scores, double targetRate);
void splitScores(vector<double> scores, vector<double> &A, vector<double> &B);
double fractionBelow(const vector<double> &scores, double threshold);
void typewiseDetection(const vector<Trace> &attackTraces, double threshold);
string getAttackType(string folder);