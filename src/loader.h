#include <vector>
#include <string>

using namespace std;

struct Trace{
    vector<int> calls;
    string folder;
};

vector<int> getFile(string path);
vector<Trace> loadDirRecursive(string dir);
void printSummary(string name, const vector<Trace>& traces);
