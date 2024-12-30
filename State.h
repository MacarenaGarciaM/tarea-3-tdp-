#ifndef STATE_H
#define STATE_H

#include <vector>
using namespace std;

class State {
private:
    vector<int> level;
    vector<int> ptr;

public:
    State(int n);
    void resetLevels();
    void resetPointers();
    int getLevel(int node) const;
    void setLevel(int node, int lvl);
    int getPointer(int node) const;
    void incrementPointer(int node);
};

#endif // STATE_H
