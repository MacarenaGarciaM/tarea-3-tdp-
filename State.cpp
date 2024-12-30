#include "State.h"

State::State(int n) : level(n, -1), ptr(n, 0) {}

void State::resetLevels() {
    fill(level.begin(), level.end(), -1);
}

void State::resetPointers() {
    fill(ptr.begin(), ptr.end(), 0);
}

int State::getLevel(int node) const {
    return level[node];
}

void State::setLevel(int node, int lvl) {
    level[node] = lvl;
}

int State::getPointer(int node) const {
    return ptr[node];
}

void State::incrementPointer(int node) {
    ptr[node]++;
}
