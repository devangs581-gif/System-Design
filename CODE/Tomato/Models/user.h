#ifndef USER_H
#define USER_H

#include "cart.h"
#include<bits/stdc++.h>
using namespace std;

class user{
    private:
    int id;
    string name,address;
    cart *c;
    public:
    user(string name,string address,int id){
        this->name=name;
        this->address=address;
        this->id=id;
        c=new cart();
    }
    
    string getName(){
        return this->name;
    }

    void setName(string &name){
        this->name=name;
    }

    string getAddress(){
        return this->address;
    }

    void setAddress(string &address){
        this->address=address;
    }
    
    int getId(){
        return this->id;
    }

    void setId(int &id){
        this->id=id;
    }

};

#endif