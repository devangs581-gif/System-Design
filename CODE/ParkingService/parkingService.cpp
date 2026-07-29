#include<bits/stdc++.h>
using namespace std;

class parkingSpace{
  public:
  int id;
  int price;
  bool isEmpty;

  parkingSpace(int id,int price){
    this->id=id;
    this->price=price;
    this->isEmpty=true;
  }
  bool getEmpty(){
    return isEmpty;
  }

  void setEmpty(){
    isEmpty=true;
  }
  
  void setFull(){
    isEmpty=false;
  }
};

class parking{
   private:
   vector<parkingSpace*>spaces;
   public:
   void addParkingSpace(parkingSpace *space){
       spaces.push_back(space);
   }
   int giveParking(){
      for(auto &it:spaces){
         if(it->getEmpty()) {
            it->setFull();
            return it->id;
         }
      }
      return -1;
   }

   void freeParking(int id){
       for(auto &it:spaces){
         if(it->id == id){
            it->setEmpty();
         }
       }
   }
};

class parkingTicket{
    public:
    string userName;
    string car;
    string carNumber;
    int price;
    int parkingId;
    
    
    void setTicket(string userName,string car,string carNumber,int price,int parkingId){
        this->userName=userName;
        this->car=car;
        this->carNumber=carNumber;
        this->parkingId=parkingId;
        this->price=price;
    }

    parkingTicket* getTicket(){
        return this;
    }
};


class parkingManager{
     private:
     static parkingManager* instance;
     parking *par;
     parkingTicket *ticket;
     set<parkingTicket*>records;
     parkingManager(parking* p){
          this->par=p;
     }
     public:
     static parkingManager* getInstance(parking *p){
         if(instance == nullptr) 
            instance=new parkingManager(p);
         return instance;
     }

     parkingTicket* giveParking(user* user){
          int id=par->giveParking();
          ticket->setTicket(user->name,user->car,user->carNumber,1000,id);
          auto it=ticket->getTicket();
          records[user]=ticket;
          return it;
     }

     void freeParking(user *user){
         auto it=records[user];
         par->freeParking(it);
         records.erase(user);
     }
};

parkingManager* parkingManager::instance=nullptr;

class user{ 
    public:
    string name;
    string car;
    string carNumber;
    parkingTicket *ticket;
    parkingManager *manager;

    user(string name,string car,string carNumber){
        this->name=name;
        this->car=car;
        this->carNumber=carNumber;
    }
    
    parkingTicket* getParking(){
         ticket=manager->giveParking(this);
    }
    
    void freeParking(parkingTicket *ticket){
        int id=ticket->parkingId;
        cout<<"Your car is park at this parkingId "<<id<<endl;
        
    }
};

int main(){
    
    parkingSpace *space1=new parkingSpace(1,100,true);
    parkingSpace *space2=new parkingSpace(2,1000,true);

    parking *par=new parking();
    par->addParkingSpace(space1);
    par->addParkingSpace(space2);
    
    parkingManager *manager=parkingManager :: getInstance(par);
    
    user* devang=new user("devang","Thar");
    parkingSpace* devangSpace=devang->getParking();

    devang->freeParking(devangSpace);

    return 0;
}