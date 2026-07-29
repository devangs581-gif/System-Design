#include<bits/stdc++.h>
using namespace std;

class Icharacter{
  public:
  virtual string getAbilities()=0;
};

class mario : public Icharacter{
   public:
   string getAbilities() override{
      return "Mario";
   }
};

class characterDecorator:public Icharacter{
   protected:
   Icharacter* ch;

   public:
   characterDecorator(Icharacter *ch){
    this->ch=ch;
   }
};

class heightUpDecorator:public characterDecorator{
   public:
   heightUpDecorator(Icharacter *ch):characterDecorator(ch){}

   string getAbilities() override{
     return ch->getAbilities() + "with Height Up ";
   }
};

class gunDecorator:public characterDecorator{
    public:
    gunDecorator(Icharacter *ch):characterDecorator(ch){}

    string getAbilities() override{
     return ch->getAbilities() + "with gun decorator ";
    }
};

int main(){
     Icharacter* m = new mario();
     cout<<"Basic Charcter "<<m->getAbilities()<<endl;

     m=new heightUpDecorator(m);
     cout<<"After height up "<<m->getAbilities()<<endl;

     m=new gunDecorator(m);
     cout<<"Afer gun power "<<m->getAbilities()<<endl;

     return 0;
}