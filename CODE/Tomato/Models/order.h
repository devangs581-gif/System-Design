#ifndef ORDER_H
#define ORDER_H

#include "user.h"
#include "restaurant.h"
#include "menuItem.h"
#include "../Payment/paymentStrategy.h"
#include <bits/stdc++.h>
using namespace std;

class order{
    private:
    int id;
    user *u;
    restaurant *r;
    vector<menuItem>items;
    
};

#endif