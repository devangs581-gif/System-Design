#include<bits/stdc++.h>
using namespace std;

//================ Notification =================//

class Inotification{
public:
    virtual string getContent() = 0;
    virtual ~Inotification() {}
};

class simpleNotification : public Inotification{
private:
    string text;

public:
    simpleNotification(string msg){
        text = msg;
    }

    string getContent() override{
        return text;
    }
};

//================ Decorator =================//

class InotificationDecorator : public Inotification{
protected:
    Inotification *noti;

public:
    InotificationDecorator(Inotification *n){
        noti = n;
    }
};

class timeStampDecorator : public InotificationDecorator{
public:
    timeStampDecorator(Inotification *n)
        : InotificationDecorator(n){}

    string getContent() override{
        return "26/07/2026 " + noti->getContent();
    }
};

class signatureDecorator : public InotificationDecorator{
public:
    signatureDecorator(Inotification *n)
        : InotificationDecorator(n){}

    string getContent() override{
        return noti->getContent() + " - Maverick";
    }
};

//================ Strategy =================//

class InotificationStrategy{
public:
    virtual string sendNotification(string msg) = 0;
    virtual ~InotificationStrategy() {}
};

class smsStrategy : public InotificationStrategy{
public:
    string sendNotification(string msg) override{
        return "SMS Strategy : " + msg;
    }
};

class emailStrategy : public InotificationStrategy{
public:
    string sendNotification(string msg) override{
        return "Email Strategy : " + msg;
    }
};

//================ Observer =================//

class Iobserver{
public:
    virtual void update() = 0;
    virtual ~Iobserver(){}
};

class Iobservable{
public:
    vector<Iobserver*> observers;

    virtual void add(Iobserver *obs)=0;
    virtual void remove(Iobserver *obs)=0;
    virtual void notify()=0;

    virtual ~Iobservable(){}
};

class notificationObservable : public Iobservable{

private:
    Inotification *currentNotification;

public:

    notificationObservable(){
        currentNotification = nullptr;
    }

    void add(Iobserver *obs) override{
        observers.push_back(obs);
    }

    void remove(Iobserver *obs) override{
        auto it = find(observers.begin(), observers.end(), obs);
        if(it != observers.end())
            observers.erase(it);
    }

    void notify() override{
        for(auto obs : observers)
            obs->update();
    }

    void setNotification(Inotification *noti){
        currentNotification = noti;
        notify();
    }

    string getNotification(){
        if(currentNotification == nullptr)
            return "";
        return currentNotification->getContent();
    }
};

//================ Singleton =================//

class notificationService{

private:

    static notificationService *instance;

    notificationObservable *notiObs;

    vector<Inotification*> notifications;

    notificationService(){
        notiObs = new notificationObservable();
    }

public:

    static notificationService* getInstance(){

        if(instance == nullptr)
            instance = new notificationService();

        return instance;
    }

    void sendNotification(Inotification *noti){

        notifications.push_back(noti);

        notiObs->setNotification(noti);
    }

    notificationObservable* getObservable(){
        return notiObs;
    }
};

notificationService* notificationService::instance = nullptr;


//================ Logger =================//

class logger : public Iobserver{
private:
    notificationObservable *notiObs;

public:
    
    logger(){
      this->notiObs=notificationService::getInstance()->getObservable();
      this->notiObs->add(this);
    }

   //  logger(notificationObservable *obs){
   //      notiObs = obs;
   //  }

    void update() override{
        cout << "Logger : "
             << notiObs->getNotification()
             << endl;
    }
};

//================ Notification Engine =================//

class notificationEngine : public Iobserver{

private:

    notificationObservable *notiObs;
    vector<InotificationStrategy*> strategies;

public:
   notificationEngine(){
      this->notiObs=notificationService::getInstance()->getObservable();
      this->notiObs->add(this);
   }

   //  notificationEngine(notificationObservable *obs){
   //      notiObs = obs;
   //  }

    void addStrategy(InotificationStrategy *strategy){
        strategies.push_back(strategy);
    }

    void update() override{

        string msg = notiObs->getNotification();

        for(auto strategy : strategies){
            cout << strategy->sendNotification(msg)
                 << endl;
        }
    }
};
//================ Main =================//

int main(){

    Inotification *notification =  new simpleNotification("Hello Devang");

    notification = new timeStampDecorator(notification);

    notification = new signatureDecorator(notification);

    notificationService *service = notificationService::getInstance();

    logger *log = new logger();

    notificationEngine *engine = new notificationEngine();

    engine->addStrategy(new smsStrategy());
    engine->addStrategy(new emailStrategy());

    service->sendNotification(notification);

    return 0;
}