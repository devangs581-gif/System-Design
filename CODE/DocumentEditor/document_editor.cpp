#include<bits/stdc++.h>
using namespace std;

class DocumentElement{
    public:
    virtual string render()=0;
};

class imageElement : public DocumentElement{
    private:
    string imagePath;

    public:

    imageElement(string imagePath){
        this->imagePath=imagePath;
    }

    string render() override{
       return "[Image: "+ imagePath + " ]" + "\n";
    }
};


class textElement : public DocumentElement{
    private:
    string text;
    public:
    textElement(string text){
        this->text=text;
    }
    string render() override{
        return "[Text : " + text + " ]" + "\n";
    }
};

class Document{
   private:
   vector<DocumentElement*>elements;
   public:
   void addElement(DocumentElement* el){
      elements.push_back(el);
   }

   string render(){
       string result;
       for(auto &e:elements){
           result+=e->render();
       }
       return result;
   }
};

class persistence{
   public:
   virtual void save(string data)=0;
};

class saveToDb:public persistence{
    public:
    void save(string data) override{
       cout<<"Data is saved to DB"<<endl;
    }
};

class saveToFile:public persistence{
    public:
    void save(string data) override{
        cout<<"Data is saved to File-Storage"<<endl;
    }
};

class documentEditor{
   private:
   Document *doc;
   persistence *storage;
   string renderedDocument;

   public:
   documentEditor(Document *doc,persistence *p){
      this->doc=doc;
      this->storage=p;
   }
   
   void addText(string text){
       doc->addElement(new textElement(text));
   }

   void addImage(string path){
       doc->addElement(new imageElement(path));
   }

   string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument=doc->render();
        }
        return renderedDocument;
   }

   void saveDocument(){
       storage->save(renderDocument());
   }
};

int main(){
     
    Document* doc=new Document();
    persistence* storage=new saveToDb();

    documentEditor* editor=new documentEditor(doc,storage);
    
    editor->addText("Hello");
    editor->addImage("picture.jpg");
    cout<<editor->renderDocument()<<endl;
    editor->saveDocument();

    return 0;
}