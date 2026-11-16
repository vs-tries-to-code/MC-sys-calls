#pragma once 
#include "loader.h"

double scoreTrace(const Trace& trace);
double averageScore(const vector<Trace>& traces);
void printScoreStats(string name, const vector<Trace> &traces);
vector<double> scoreAll(vector<Trace> &traces);
double findThreshold(vector<double> scores, double targetRate);
void splitScores(vector<double> scores, vector<double> &A, vector<double> &B);
double fractionBelow(vector<double> &scores, double threshold);
