#include<bits/stdc++.h>
using namespace std;

class burger{
    public:
    virtual void prepare()=0;
};

class basicBurger:public burger{
      public:
      void prepare() override{
          cout<<"Preparing Basic-Burger"<<endl;
      }
};

class standardBurger:public burger{
      public:
      void prepare() override{
          cout<<"Preparing Standard-Burger"<<endl;
      }
};

class wheatBurger:public burger{
    public:
    void prepare() override{
          cout<<"Preparing Wheat-Burger"<<endl;
      }
};

class vegBurger:public burger{
    public:
    void prepare() override{
          cout<<"Preparing Veg-Burger"<<endl;
      }
};

class burgerFactory{
    public:
    virtual burger* createBurger(string &type)=0;
};


class singhBurger:public burgerFactory{
    public:
    burger* createBurger(string &type) override{
        if(type == "basic") return new basicBurger();
        else if(type == "standard") return new standardBurger();
        else {
            cout<<"Invalid Burger-Type"<<endl;
            return nullptr;
        }
    }
};

class kingBurger:public burgerFactory{
    public:
    burger* createBurger(string &type)override{
        if(type == "wheat") return new wheatBurger();
        else if(type == "veg") return new vegBurger();
        else{
            cout<<"Invalid Burger-Type"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string type="basic";

    burgerFactory *factory=new kingBurger();
    burger *b=factory->createBurger(type);

    if(b) b->prepare();

    return 0;
}