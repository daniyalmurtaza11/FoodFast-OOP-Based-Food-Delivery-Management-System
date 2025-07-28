#include <iostream>
#include <fstream>
using namespace std;


//Daniyal Murtaza


class User {
protected:
    string username;
    string password;
public:
    virtual bool login() {
        cout<<"Enter username: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        cout<<"Login successful for user: "<<username<<endl;
        return true;}
};

class Customer:public User {
    string cartItems[50];
    int quantities[50];
    int cartCount;
    string address;
    string phone;
public:
    Customer(){
        cartCount=0;}
    void showMenuOptions() {
        cout<<"\nCustomer Menu:\n1. View Food details\n2. Place Order\n3. Cancel Order\n4. Checkout\n5. Exit"<<endl;}
    void viewFoodDetails(string menu[], int prices[], int itemCount) {
        cout<<"\nAvailable Menu:\n";
        for(int i=0;i<itemCount;i++) {
        cout<<i+1<<". "<<menu[i]<<" ---> Rs. "<<prices[i]<<endl;}
    }
    void addToCart(string menu[], int index, int quantity) {
        cartItems[cartCount]=menu[index];
        quantities[cartCount]=quantity;
        cartCount++;
        cout<<"Item added to cart.\n";}
    void placeOrder(){
        cout<<"\nOrder placed.\n";}
    void cancelOrder(){
        cartCount=0;
        cout<<"Order cancelled.\n";}
    void getDetails(){
        cout<<"\nEnter your address: ";
        cin.ignore();
        getline(cin, address);
        cout<<"Enter your phone number: ";
        getline(cin, phone);}
void checkout(string menu[], int prices[], int itemCount) {
int total=0;
saveOrderToFile();

        cout<<"\nBill Receipt:\n";
        for (int i=0;i<cartCount;i++){
            int price=0;
            for (int j=0;j<itemCount;j++){
                if (menu[j]==cartItems[i]){
                    price=prices[j];
                    break;}
}
int itemTotal=price*quantities[i];
cout<<cartItems[i]<<" x "<<quantities[i]<<" = Rs. "<< itemTotal<<endl;
total+=itemTotal;
}
        cout<<"Total Amount: Rs. "<<total<<endl;
        cout<<"Delivery Address: "<<address<<endl;
        cout << "Phone Number: "<<phone<<endl;
        cout << "Payment Method: Cash on Delivery\n";}
       void saveOrderToFile() {
    ofstream orderFile("orders.txt", ios::app); // append mode
    if (orderFile.is_open()) {
        orderFile << "Order by: " << username << endl;
        for (int i = 0; i < cartCount; i++) {
            orderFile << cartItems[i] << " x " << quantities[i] << endl;
        }
        orderFile << "Address: " << address << endl;
        orderFile << "Phone: " << phone << endl;
        orderFile << "--------------------------\n";
        orderFile.close();
        cout << "Order saved.\n";
    } else {
        cout << "Failed to save order.\n";
    }
}

};

class Restaurant:public User{
    string menu[50];
    int prices[50];
    int itemCount;
public:
    void showRestaurantOptions(){
        cout<<"\nRestaurant Menu:\n";
        cout<<"1. Add Food Details\n";
        cout<<"2. Delete Food\n";
        cout<<"3. Edit Food\n";
        cout<<"4. Check Food Order\n";
        cout<<"5. Update Food Delivery Status\n";
        cout<<"6. Calculate Bill\n";
        cout<<"7. Exit\n";}
Restaurant() {
    string defaultItems[] = {"Burger", "Pizza", "Fries", "Nuggets", "Pasta"};
    int defaultPrices[] = {250, 500, 150, 200, 350};
    itemCount = 5;
    for (int i = 0; i < itemCount; i++) {
        menu[i] = defaultItems[i];
        prices[i] = defaultPrices[i];
    }
    saveMenuToFile();
}

    string* getMenu(){
        return menu;}

    int* getPrices(){
        return prices;}
    int getItemCount(){
        return itemCount;}
    void addFoodItem(){
        saveMenuToFile();
        if (itemCount>=50) {
            cout<<"Cannot add more items.\n";
            return;
}
        cout<<"Enter food name: ";
        cin.ignore();
        getline(cin, menu[itemCount]);
        cout<<"Enter price: ";
        cin>>prices[itemCount];
        itemCount++;
        cout<<"Item added successfully.\n";
    }
    void editFoodItem() {
    int index;
    cout<<"Enter item number to edit: ";
    cin>>index;
    if (index<1||index>itemCount){
        cout<<"Invalid item number.\n";
        return;
    }
    index--;
    cout<<"Current name: " << menu[index] << ", price: "<<prices[index]<<endl;
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, menu[index]);
    cout<<"Enter new price: ";
    cin>>prices[index];
    saveMenuToFile();
    cout << "Item updated successfully.\n";
}

    void deleteFoodItem(){
        saveMenuToFile();
        int index;
        cout<<"Enter item number to delete: ";
        cin>>index;
        if(index<1||index>itemCount) {
            cout<<"Invalid item number.\n";
            return;}

        for(int i=index-1;i<itemCount-1;i++) {
            menu[i]=menu[i+1];
            prices[i]=prices[i+1];}
           itemCount--;
        cout<<"Item deleted successfully.\n";}
    void checkOrder(){
        cout<<"Displaying food orders.\n";}

    void updateOrderStatus(){
        cout<<"Order status updated to 'Prepared'.\n";}
    void calculateBill(){
        int total=0;
        for(int i=0;i<itemCount;i++) {
            total+=prices[i];}
        cout<<"Total Bill: Rs. "<<total<<"(bill).\n";
    }
  void saveMenuToFile() {
    ofstream outFile("menu.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < itemCount; i++) {
            outFile << menu[i] << "," << prices[i] << endl;
        }
        outFile.close();
        cout << "Menu saved to file.\n";
    } else {
        cout << "Failed to open file for writing.\n";
    }
}

void loadMenuFromFile() {
    ifstream inFile("menu.txt");
    itemCount = 0;
    if (inFile.is_open()) {
        string name;
        int price;
        while (getline(inFile, name, ',')) {
            inFile >> price;
            inFile.ignore(); // To skip the newline
            menu[itemCount] = name;
            prices[itemCount] = price;
            itemCount++;
        }
        inFile.close();
        cout << "Menu loaded from file.\n";
    } else {
        cout << "No menu file found, using default menu.\n";
    }
}


};

class Rider:public User{
public:
    void showRiderOptions(){
        cout<<"\nRider Menu:\n";
        cout<<"1. View Order\n";
        cout<<"2. Accept or Reject Delivery\n";
        cout<<"3. Update Delivery Status\n";
        cout<<"4. Exit\n";
    }
    void viewOrder(){
        cout<<"Order viewed.\n";}
    void acceptOrReject(){
        char ch;
        cout<<"Do you accept the delivery? (y/n): ";
        cin>>ch;
        if(ch=='y'||ch=='Y'){cout << "Delivery accepted.\n";}
        else {cout<<"Delivery rejected.\n";}
}
    void updateDeliveryStatus(){
        cout<<"Order delivery status updated.\n";}
    void updatePayment(){
        cout<<"Payment received and updated.\n";}
};

class Admin:public User {
public:
    void manageRestaurant(){
        cout<<"Restaurant account managed.\n";}
    void manageRider(){
        cout<<"Rider account managed.\n";}

};

  int main(){
    Restaurant restaurant;
    Customer customer;
    Rider rider;
    Admin admin;

    int roleChoice;
do{cout<<"\nLogin as:\n1. Restaurant\n2. Customer\n3. Rider\n4. Admin\n5. Exit\nEnter choice: ";
   cin>>roleChoice;
restaurant.loadMenuFromFile();
switch (roleChoice){
case 1:
cout<<"\nRestaurant Login:\n";
restaurant.login();
{
int resOption;
  do{
    restaurant.showRestaurantOptions();
    cout<<"Enter your choice: ";
    cin>>resOption;
     switch(resOption){
    case 1:
     restaurant.addFoodItem();
     break;
    case 2:
     restaurant.deleteFoodItem();
     break;
    case 3:
    restaurant.editFoodItem();
    break;
case 4:
    restaurant.checkOrder();
    break;
case 5:
    restaurant.updateOrderStatus();
    break;
case 6:
    restaurant.calculateBill();
    break;
case 7:
    cout << "Logging out...";
    break;
default:
    cout<<"Invalid option.";}
       } while(resOption!=7);
                }
            break;
case 2:
cout<<"\nCustomer Login:\n";
customer.login();
{
string* menu=restaurant.getMenu();
int* prices=restaurant.getPrices();
int itemCount=restaurant.getItemCount();
    int option;
    do{
    customer.showMenuOptions();
    cout<<"Enter your choice: ";
    cin>>option;
    switch(option){
        case 1:
          customer.viewFoodDetails(menu, prices, itemCount);
          break;
        case 2:
          int foodId, qty;
          customer.viewFoodDetails(menu, prices, itemCount);
          cout<<"Enter food ID to order: ";
          cin>>foodId;
          cout<<"Enter quantity: ";
          cin>>qty;
            customer.addToCart(menu, foodId - 1, qty);
            customer.placeOrder();
            restaurant.updateOrderStatus();
            rider.viewOrder();
            rider.updateDeliveryStatus();
            rider.updatePayment();
            break;
        case 3:
          customer.cancelOrder();
          break;
        case 4:
          customer.getDetails();
          customer.checkout(menu, prices, itemCount);
          break;
        case 5:
          cout<<"Logging out...\n";
          break;
        default:
          cout<<"Invalid option.\n";}
}
while(option != 5);}
    break;
case 3:
    cout<<"\nRider Login:\n";
    rider.login();
    {
      int riderOption;
      do {
        rider.showRiderOptions();
        cout<<"Enter your choice: ";
        cin>>riderOption;
        switch(riderOption){
     case 1:
        rider.viewOrder();
        break;
     case 2:
        rider.acceptOrReject();
        break;
     case 3:
        rider.updateDeliveryStatus();
        break;
     case 4:
        cout<<"Logging out...\n";
        break;
     default:
        cout<<"Invalid option.\n";}
 }while(riderOption!=4);
  }
    break;
 case 4:
    cout<<"\nAdmin Login:\n";
    admin.login();
    cout <<"Admin logged out...\n";
    break;
 case 5:
    cout<<"Exiting program.\n";
    break;
 default:
    cout<<"Invalid choice.\n";}

 }while(roleChoice != 5);

  return 0;
}
