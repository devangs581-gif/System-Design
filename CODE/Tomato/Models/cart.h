#ifndef CART_H
#define CART_H

#include "restaurant.h"
#include "menuItem.h"
#include <bits/stdc++.h>
using namespace std;

class cart{
    private:
    restaurant* r;
    vector<menuItem>items;

    public:
    cart(){
      r=nullptr;
    }
    
    void addItem(menuItem &item){
        if(!r){
            cout<<"Please Select the Restaurant first"<<endl;
            return ;
        }
        items.push_back(item);
    }
    
    void setRestaurant(restaurant* res){
        r=res;
    }
    
    restaurant* getRestaurant(){
       return this->r;
    }
    
    void clear(){
        items.clear();
        r=nullptr;
    }
    
    vector<menuItem> getItems(){
        return this->items;
    }

    int totalCost(){
        int ans=0;
        for(auto &it:items){
           ans=ans + it.getPrice();
        }
        return ans;
    }

    bool isEmpty(){
        return (!r || items.empty());
    }
};

#endif