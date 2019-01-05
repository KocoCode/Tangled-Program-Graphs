#pragma once
#include "bidder.h"
#include "team.h"
#include "poolproxy.h"

class TPG {
private:
    int numAtomicActions;
    int numFeatureDimension;
    int numBehaviouralStates;
    int maxProgSize;
    int Rsize;
    double Rgap;
    double pAddProfilePoint;
    double pAtomic;
    double pBidAdd;
    double pBidDelete;
    double pBidMutate;
    double pBidSwap;
    double pma;
    double pmd;
    double pmm;
    double pmn;
    int omega;
public:
    TPG(int _numAtomicActions, int numFeatureDimension,
    int _numBehaviouralStates=50, int _maxProgSize=96, int _Rsize=90,
    double _Rgap=0.5, double _pAddProfilePoint=0.0005, double _pAtomic=0.5,
    double _pBidAdd=0.5, double _pBidDelete=0.5, double _pBidMutate=1,
    double _pBidSwap=1, double _pma=0.7, double _pmd=0.7, double _pmm=0.2,
    double _pmn=0.1, int omega=5);

    void genTeams(int genTime);
    void genTeams(int genTime, int parentId);
    void genUniqueBidder(int bidderId);
    void selTeams(int genTime);
    void cleanup(int genTime);
    void initBehaviouralStates(function<vector<double>()> initFunc);
    void addBehaviouralState(const vector<double> behaviouralState);
};