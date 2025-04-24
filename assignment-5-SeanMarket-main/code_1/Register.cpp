#include <iostream>
#include <cstdlib>
#include <iostream>
#include "Register.hpp"


using namespace std;

Register::Register(){
   top = 0;
}

/*
 * If the register is full or not
 * @returns 
 */
bool Register::isFull(){
   // TODO
   if(top == SIZE){
      return true;
   }else{
      return false;
   }
}

/*
 * Adds money to stack.
 * @param money: the type of pancake's price times the quantity
 */
void Register::push(int money){
   // TODO
   if(isFull()){
      cout << "Stack overflow: \n";
   }
   else{
      a[top] = money; //next open index in the array is top
      top++;
   }
}


/*
 * Checks if stack is full. 
 * @returns a bool
 */
bool Register::isEmpty(){
   // TODO
   if(top == 0){
      return true;
   }
   else{
      return false;
   }
}

/*
 * Looping through the stack array to display amounts
 */
void Register::disp(){
   // TODO
   int temp = top;
   cout << "top = " << a[temp-1] << '\n'; //top is the next available space
   for(int i = temp-2; i > -1; i--){ //already printed out the top (top-1) value, so start at the index before the top value (top-2)
      cout << a[i] << '\n';
   }
}

int Register::pop(){
   // TODO
   if(isEmpty()){
      cout << "Stack empty, cannot pop an item!\n";
      return -1;
   }
   else{
      int returnVal = a[top-1];
      top--;

      return returnVal;
   }
}