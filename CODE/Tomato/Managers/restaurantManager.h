#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include "../Models/restaurant.h"
#include<bits/stdc++.h>
using namespace std;

class restaurantManager{
    private:
    vector<restaurant *> restaurants;
    static restaurantManager *instance;
    
    public:
    static restaurantManager* getInstance(){
        if(!instance){
            instance=new restaurantManager();
        }
        return instance;
    }
    
    void addRestaurant(restaurant *r){
        restaurants.push_back(r);
    }
    
    vector<restaurant *>searchByLocation(string &loc){
        vector<restaurant *>result;
        
        for(auto &it:restaurants){
            string location=it->getLocation();
            if(location == loc) result.push_back(it);
        }
        return result;
    }

};

restaurantManager* restaurantManager::instance=nullptr;
#endif