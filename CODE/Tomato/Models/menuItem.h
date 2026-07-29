#ifndef MENUITEM_H
#define MENUITEM_H

#include<bits/stdc++.h>
using namespace std;

class menuItem{
    private:
    string code,name;
    int price;
    
    public:
    menuItem(string &code,string &name,int &price){
        this->code=code;
        this->name=name;
        this->price=price;
    }

    string getName(){
         return this->name;
    }

    void setName(string &name){
        this->name=name;
    }

    string getCode(){
       return this->code;
    }
    
    void setCode(string &code){
        this->code=code;
    }

    int getPrice(){
        return this->price;
    }
};
#endif