#include<bits/stdc++.h>
using namespace std;

class Isubscriber{
     public:
     virtual void update()=0;
};

class Ichannel{
    public:
    virtual void subscriber(Isubscriber* subs)=0;
    virtual void unsubscribe(Isubscriber *subs)=0;
    virtual void notify()=0;
};

class channel:public Ichannel{
    private:
    string name,latestVideo;
    vector<Isubscriber *>subscribers;

    public:
    channel(string name){
        this->name=name;
    }

    void subscriber(Isubscriber *subs) override {
        subscribers.push_back(subs);
    }

    void unsubscribe(Isubscriber *subs) override {
        auto it=find(subscribers.begin(),subscribers.end(),subs);
        if(it != subscribers.end()){
            subscribers.erase(it);
        }
    }

    void notify() override {
        for(auto &it:subscribers){
            it->update();
        }
    }
    
    void uploadVideo(string title){
        this->latestVideo=title;
        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
        notify();
    }

    string getVideoData(){
        return "Check out this [" + latestVideo + "]\n";
    }
};

class subscriber:public Isubscriber{
    private:
    string name;
    channel* ch;
    public:
    subscriber(string name,channel *ch){
        this->name=name;
        this->ch=ch;
    }
    void update() override{
       cout << "Hey " << name << "," << ch->getVideoData();
    }
};

int main(){
    
    channel *ch=new channel("Crazy-XYZ");
    
    subscriber *subs1=new subscriber("Devang",ch);
    subscriber *subs2=new subscriber("mehta",ch);
    
    ch->subscriber(subs1);
    ch->subscriber(subs2);

    ch->uploadVideo("CDS Prepration");
    
    ch->unsubscribe(subs1);
    
    ch->uploadVideo("In IMA");

    return 0;
}