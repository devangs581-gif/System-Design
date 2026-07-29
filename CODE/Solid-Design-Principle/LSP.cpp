#include<bits/stdc++.h>
using namespace std;

class depositOnlyAccount{
   public:
   virtual void deposit(double amount)=0; 
};

class withdrawAccount:public depositOnlyAccount{
     public:
     virtual void withdraw(double amount)=0;
};


class currentAccount:public withdrawAccount{
    private:
    double balance;
    public:
    currentAccount(){
        this->balance=0;
    }

    void deposit(double amount){
        this->balance+=amount;
        cout<<"Amount successfully deposited in your current account and your final balance of acccount is -> "<<this->balance<<"-Rs"<<endl;
    }

    void withdraw(double amount){
        if(this->balance < amount) cout<<"Balance is insufficient in your current account"<<endl;
        else{
            this->balance-=amount;
            cout<<"Amount successfully withdraw from your current account and your final balance is -> "<<this->balance<<"-Rs"<<endl;
        }
    }
};

class savingAccount:public withdrawAccount{
    private:
    double balance;
    public:
    savingAccount(){
        this->balance=0;
    }

    void deposit(double amount){
        this->balance+=amount;
        cout<<"Amount successfully deposited in your saving account and your final balance of acccount is -> "<<this->balance<<"-Rs"<<endl;
    }

    void withdraw(double amount){
        if(this->balance < amount) cout<<"Balance is insufficient in your saving account"<<endl;
        else{
            this->balance-=amount;
            cout<<"Amount successfully withdraw from your saving account and your final balance is -> "<<this->balance<<"-Rs"<<endl;
        }
    }
};

class fixedAccount:public depositOnlyAccount{
   private:
    double balance;
    public:
    fixedAccount(){
        this->balance=0;
    }

    void deposit(double amount){
        this->balance+=amount;
        cout<<"Amount successfully deposited in your fixed account and your final balance of acccount is -> "<<this->balance<<"-Rs"<<endl;
    }
};

class client{
    private:
    vector<withdrawAccount*>withdrawAccounts;
    vector<depositOnlyAccount*>depositOnlyAccounts;

    public:
    client(vector<withdrawAccount*>withdrawAccounts,vector<depositOnlyAccount*>depositOnlyAccounts){
        this->withdrawAccounts=withdrawAccounts;
        this->depositOnlyAccounts=depositOnlyAccounts;
    }

    void processTransaction(){
        for(withdrawAccount *acc:withdrawAccounts){
            acc->deposit(1000);
            acc->withdraw(500);
        }
        for(depositOnlyAccount *acc:depositOnlyAccounts){
            acc->deposit(1000);
        }
    }
};

int main(){

    vector<withdrawAccount*>withdrawAccounts;
    withdrawAccounts.push_back(new savingAccount());
    withdrawAccounts.push_back(new currentAccount());
    
    vector<depositOnlyAccount*>depositOnlyAccounts;
    depositOnlyAccounts.push_back(new fixedAccount());

    client *c=new client(withdrawAccounts,depositOnlyAccounts);

    c->processTransaction();
    
    return 0;
}
