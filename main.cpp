//Convert Dr. T's struct to class and add Dr. T's To Do list.
//Teacher: Dr. Tyson McMillan
//Student: Ronald Angora
//Date: 05/01/2021

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include "Input_Validation_Extended.h"
using namespace std; 

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;
  public:
    //Default Constructor
    MenuItem() = default;
    //Setters
    void setName(string n){ name = n; }
    void setItemCost(double IC){ itemCost = IC; }
    void setDesc(string d){ desc = d; }
    void setAddLetter(char AL){ addLetter = AL; }
    void setRemoveLetter(char RL){ removeLetter = RL; }
    void setCount(int c){ count = c; }
    //Getters
    string getName() const { return name; }
    double getItemCost() const { return itemCost; }
    string getDesc() const { return desc; }
    char getAddLetter() const { return addLetter; }
    char getRemoveLetter() const { return removeLetter; }
    int getCount() const { return count; }
    //Incrase count +1
    void increaseCount()
    {
      count++;
    }
    //Decrease count -1
    void decreaseCount()
    {
      count--;
    }
};

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Taco", "Salmon", "Steak", "Kabob", "Burger"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); //initialze all counts to 0
    entireMenu[i].setDesc("delicious"); //set all default desc to "delicous"
  }

}

void showMenu(vector<MenuItem> &m)
{
  string colorB;
  colorB = "\x1b[" + to_string(34) + ";1m";
  string reset = "\x1b[0m";
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << colorB << "Angora's Struct to Class Menu" << reset << endl; 
  cout << "\x1b[36;1mADD\x1b[0m  \t\x1b[39;1mNAME\x1b[0m \t \x1b[32;1mCOST\x1b[0m \t\x1b[31;1mREMOVE\x1b[0m\t\x1b[39;1mCOUNT\x1b[0m\t\x1b[93;1mDESC\x1b[0m"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) << m[i].getName()
    << setw(5) << "\x1b[32;1m\t$\x1b[0m" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter()
    << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() 
    <<endl; 
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subTotal = 0.0;
  double total = 0.0;
  double tip = 0.0; 
  int userInput = 0;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].increaseCount(); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subTotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subTotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].decreaseCount(); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subTotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subTotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order."; 
  
  //Tip Process
  cout << "\nSubtotal = $" << subTotal;
  cout << "\n20%      = $" << subTotal * .2;
  cout << "\nEnter tip amount: ";
  tip = validateDouble(tip);
  
  //Total Due Process
  cout << "\nSubtotal  = $" << subTotal;
  cout << "\nTax       = $" << subTotal * .0625;
  cout << "\nTip       = $" << tip;
  total = subTotal + subTotal * .0625 + tip;
  cout << "\nTotal Due = $" << total;
  
  //Cash or card
  cout << "\n1) Cash ";
  cout << "\n2) Card ";
  userInput = validateInt(userInput);
  if(userInput == 1)
  {
    double cash = 0.0;
    cout << "\nHand over cash $";
    cash = validateDouble(cash);
    cout << "\nChange = $" << cash - total;
  }
  else if(userInput == 2)
  {
    cout << "Thank you! Your payment has been processed!";
  }
}

void printReceipt(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);
  cout << "\n\n************RECEIPT************" << endl;
  cout << "\x1b[39;1mNAME\x1b[0m \t\t\x1b[32;1mCOST\x1b[0m \t\x1b[39;1mCOUNT\x1b[0m"<<endl;
  for(int i=0; i < m.size(); i++)
  {
    if(m[i].getCount() > 0)
    {
      cout << m[i].getName() << setw(4) << "\x1b[32;1m\t$\x1b[0m" << m[i].getItemCost() << setw(5)
      << m[i].getCount() << setw(9) << endl; 
    }
  }  
}

int main() 
{
  char option = '\0';
  do
  {
    vector<MenuItem> wholeMenu; 
    populateMenu(wholeMenu); //put some default values in the menu
    showMenu(wholeMenu); //print the current data of the menu on screen 
    acceptOrder(wholeMenu); 
    printReceipt(wholeMenu);
    cout << "\nAny key for a new customer." << endl;
    cout << "'X' or 'x' to Quit." << endl;
    cin >> option;
  }while(option != 'X' && option != 'x');
  
  return 0; 
}