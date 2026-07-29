#include<bits/stdc++.h>
using namespace std;

class Talkable{
    public:
    virtual void talk()=0;
};

class normalTalk:public Talkable{
    public:
    void talk() override{
        cout<<"Talking Normally"<<endl;
    }
};

class noTalk:public Talkable{
    public:
    void talk() override{
        cout<<"Not Talking"<<endl;
    }
};

class Walkable{
    public:
    virtual void walk()=0;
};

class normalWalk:public Walkable{
    public:
    void walk() override{
        cout<<"Walking normally"<<endl;
    }
};

class noWalk:public Walkable{
    public:
    void walk() override{
        cout<<"Not walking"<<endl;
    }
};

class Robot{
    private:
    Talkable* t;
    Walkable* w;
    
    public:
    Robot(Talkable *t,Walkable *w){
       this->t=t;
       this->w=w;
    }

    void walk(){
        w->walk();
    }

    void talk(){
        t->talk();
    }

    virtual void projection()=0;
};

class companionRobot:public Robot{
    public:
    companionRobot(Walkable *w,Talkable *t):Robot(t,w){

    }
    void projection() override{
        cout<<"Projection of companinon-Robot"<<endl;
    }
};

int main(){
    Robot *robot1=new companionRobot(new normalWalk(),new noTalk()); 
    
    robot1->walk();
    robot1->talk();
    robot1->projection();

    return 0;
}