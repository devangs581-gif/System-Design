#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "menuItem.h"
#include<bits/stdc++.h>
using namespace std;

class restaurant{
    private:
    static int nextId;
    int id;
    string name,location;
    vector<menuItem>menu;
    
    public:
    restaurant(string &name,string &location){
         this->name=name;
         this->location=location;
         this->id=++nextId;
    }

    string getName(){
        return this->name;
    }
    void setName(string &name){
        this->name=name;
    }
    
    string getLocation(){
        return this->location;
    }
    void setLocation(string &location){
        this->location=location;
    }
    
    int getId(){
        return this->id;
    }
    void setId(int &id){
        this->id=id;
    }

    vector<menuItem> getMenu(){
        return this->menu;
    }

    void addItem(menuItem &item){
        menu.push_back(item);
    }
};

int restaurant::nextId=0;

#endif