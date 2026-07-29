#ifndef NETBANKING_H
#define NETBANKING_H

#include<bits/stdc++.h>
#include "paymentStrategy.h"
using namespace std;

class netBanking : public paymentStrategy{
    public:
    void pay(int amount) override{
        cout<<"Paid "<<amount<<endl;
    }
};

#endif