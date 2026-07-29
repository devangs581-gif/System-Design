#include<bits/stdc++.h>
using namespace std;

class IfileSystemInterface{
    public:
    string name;
    virtual void openAll()=0;
    virtual string getName()=0;
};

class file : public IfileSystemInterface{
   public:
   file(string name){
      this->name=name;
   }
   
   string getName() override{
       return this->name;
   }

   void openAll() override{
        cout<<this->getName()<<endl;
   }
};


class folder : public IfileSystemInterface{
    private:
    vector<IfileSystemInterface*>children;

    public:
    folder(string name){
            this->name=name;
        }

    void add(IfileSystemInterface *temp){
        children.push_back(temp);
    }

    string getName() override{
        return this->name;
    }

    void openAll() override{
        cout<<this->getName()<<endl;
            for(auto &it:children){
                it->openAll();
            }
    }
};


int main(){

    folder* root=new folder("root");
    root->add(new file("file1.txt"));
    root->add(new file("file2.txt"));


    folder* docs=new folder("docs");
    docs->add(new file("docs1.txt"));
    docs->add(new file("docs2.txt"));

    root->add(docs);
    
    root->openAll();

    return 0;
}