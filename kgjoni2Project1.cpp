/*main.cpp*/

//
// Banking program in modern C++.
//
// KRISTI GJONI
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "customer.h"

using namespace std;


void makeTransaction(int x, double y, vector <Customer>& C){
  bool isFound = false;
  for(Customer& c: C){
    if(x == c.getID()){
      c.updateBalance(y);
      isFound = true;
    }
  }
  for(Customer& c: C){
    if(isFound == false){
      cout << " **Invalid Tx: " << x << "," << y << endl;
      break;
    }
  }
}

void sortByNameAndPrint(vector <Customer>& C){
  
  cout << ">> Customers before:" << endl;
  
  sort(C.begin(), 
       C.end(),
       [] (Customer c1, Customer c2)
       {
         if(c1.getName() < c2.getName()){
           return true;
         }
         else{
           return false;
         }
       }
      );
      for(Customer& c: C){
        cout << " " << c.getName() << " (" << c.getID() << "): $" << c.getBalance() << endl;
      }
  }

void sortByBalanceAndPrint(vector <Customer>& C){
  
  cout << ">> Customers after:" << endl;
  
  sort(C.begin(), 
       C.end(),
       [] (Customer c1, Customer c2)
       {
         if(c1.getBalance() > c2.getBalance()){
           return true;
         }
         else if(c1.getBalance() < c2.getBalance()){
           return false;
         }
         else{
           if(c1.getName() < c2.getName()){
             return true;
           }
           else{
             return false;
           }
         }
       }
      );
      for(Customer& c: C){
        cout << " " << c.getName() << " (" << c.getID() << "): $" << c.getBalance() << endl;
      }
  }

int main()
{
  int n;
  double m;
  
  string  customerFilename, transactionsFilename;

  cin >> customerFilename;
  cout << customerFilename << endl;
  
  cin >> transactionsFilename;
  cout << transactionsFilename << endl;

  ifstream  custFile(customerFilename);
  ifstream  txFile(transactionsFilename);

  cout << std::fixed;
  cout << std::setprecision(2);

  if (!custFile.good())
  {
    cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
    return -1;
  }
  if (!txFile.good())
  {
    cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
    return -1;
  }
    
  vector <Customer> customer;
  vector <Customer> cost;
  //vector <Customer2> V;
  string line, customer_name, customer_id, customer_balance, x, y;
  
  while(getline(custFile, line))
  {
    stringstream ss(line);
    
    //parse line
    getline(ss, customer_name, ',');
    getline(ss, customer_id, ',');
    getline(ss, customer_balance);
    
    Customer C(customer_name, stoi(customer_id), stod(customer_balance));
    
    //insert at end
    customer.push_back(C);
  }
  
  sortByNameAndPrint(customer);
  
  cout << ">> Processing..." << endl;
  
  while(getline(txFile, line))
  {
    stringstream ss(line);
    
    //parse line
    getline(ss, x , ',');
    getline(ss, y);
    
    n = stoi(x);
    m = stod(y);
    
    makeTransaction(n, m, customer);
  }
  
  sortByBalanceAndPrint(customer);
  
   return 0;
}
