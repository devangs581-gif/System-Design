#include<bits/stdc++.h>
using namespace std;

class Product{
  public:
    string name;
    int price;
    
    Product(string name,int price){
        this->name=name;
        this->price=price;
    }
};


class ShoppingCart{
    private:
       vector<Product*>products;

    public:
      void addProduct(Product *p){
          products.push_back(p);
      }

      const vector<Product*>getProduct(){
          return products;
      }

      int calculateTotalPrice(){
          int price=0;
          for(auto p:products){
              price+=p->price;
          }
          return price;
      }
};

class cartInvoice{
    private:
       ShoppingCart *cart;
    public:
      cartInvoice(ShoppingCart *cart){
         this->cart=cart;
      }

      void cartPrinter(){
          cout<<"This is Invoice Printer"<<endl;
          for(auto &it:cart->getProduct()){
              cout<<it->name<<"- Rs"<<it->price<<endl;
          }
          cout<<"Total Amount - "<<cart->calculateTotalPrice()<<"Rs"<<endl;
      }
};

class cartDbStorage{
    private:
      ShoppingCart *cart;
    public:
      cartDbStorage(ShoppingCart *cart){
         this->cart=cart;
      }
      void saveToDatabase(){
         cout<<"Saving to database"<<endl;
      }
};

int main(){
    ShoppingCart *cart=new ShoppingCart();

    cart->addProduct(new Product("Laptop",1000));
    cart->addProduct(new Product("mouse",30));


    cartInvoice *printer=new cartInvoice(cart);
    printer->cartPrinter();

    cartDbStorage *Db=new cartDbStorage(cart);
    Db->saveToDatabase();

    return 0;
}