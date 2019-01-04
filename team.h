#pragma once
#include <unordered_set>
#include <vector>

using std::unordered_set;
using std::vector;

class Team {
private:
    long genTime;
    long id;
    unordered_set<long> memberBidders;
    unordered_set<long> activeBidders;
public:
    void addBidder(long id);
    void clearReg();
    int getAction(const vector<double> &state);
};