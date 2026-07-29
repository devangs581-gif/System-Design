#include<bits/stdc++.h>
using namespace std;

class Icommand{
    public:
    virtual void execute()=0;
    virtual void undo()=0;
};

class light{
    public:
    void on(){
        cout<<"Light is on"<<endl;
    }
    void off(){
        cout<<"Light is off"<<endl;
    }
};

class fan{
    public:
    void on(){
        cout<<"Fan is on"<<endl;
    }
    void off(){
        cout<<"Fan is off"<<endl;
    }
};

class lightCommand : public Icommand{
     private:
     light *l;
     public:
     lightCommand(light *l){
        this->l=l;
     }
     void execute() override{
        l->on();
     }
     void undo() override{
        l->off();
     }
};

class fanCommand : public Icommand{
    private:
    fan *f;
    public:
    fanCommand(fan *f){
        this->f=f;
     }
    void execute() override{
        f->on();
     }
     void undo() override{
        f->off();
     }
};

class remoteControl{
     private:
     static const int size=4;
     vector<Icommand *>commands;
     vector<bool>isButtonPressed;
     public:
     remoteControl(){
         commands.assign(size,nullptr);
         isButtonPressed.assign(size,false);//false-off,true-on
     }
     void setCommand(Icommand* com,int indx){
         if(commands[indx] != nullptr) delete commands[indx];
         commands[indx]=com;
         isButtonPressed[indx]=false;
     }
     void pressButton(int indx){
        if(isButtonPressed[indx]) 
            commands[indx]->undo();
        else 
           commands[indx]->execute();
        isButtonPressed[indx] = !isButtonPressed[indx];
     }
};

int main(){
    light *l=new light();
    fan *f=new fan();
    
    remoteControl* remote=new remoteControl();
    remote->setCommand(new lightCommand(l),0);
    remote->setCommand(new fanCommand(f),1);
    
    remote->pressButton(0);
    remote->pressButton(0);

    remote->pressButton(1);
    remote->pressButton(1);

    return 0;
}