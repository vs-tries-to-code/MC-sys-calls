#pragma once
#include<vector>
#include<fstream>
#include "loader.h"

const double SMOOTH = 0.001;
const int N = 341;  //

extern vector<vector<double>> tpm;

void countTransitions(vector<Trace>& traces);
void calcProbability();