#include "ShopQueue.hpp"
#include <iostream>

using namespace std;

ShopQueue::ShopQueue() {
   queueFront = nullptr;
   queueEnd = nullptr;
}

ShopQueue::~ShopQueue(){
   while(!isEmpty()){
      dequeue();
   }
}

/**
 * Checks if the shopqueue is empty or not
 * @returns Whether its empty or not
 */ 
bool ShopQueue::isEmpty() {
   //TODO
   if(queueFront == nullptr){
      return true;
   }
   else{

      return false;
   }
}

/**
 * Looks at the shopqueue and returns the most 'urgent' order on the queue. No elements should be removed.
 * @return A customer order
 */
CustomerOrder* ShopQueue::peek() {
   // TODO
   if(isEmpty()){

      cout << "Queue empty, cannot peek!\n";
      return nullptr;
   }
   else{
      return queueFront;
   }
}

/**
 * Adds the customers to the queue.
 * @param name The name of the customer to add.
 * @param num_pancakes The number of pancakes to add
 * @param type_of_pancake The type of pancake to add. 
 * 
 */
void ShopQueue::enqueue(string name, int num_pancakes, int type_of_pancake) {
   // TODO
   CustomerOrder *newOrder = new CustomerOrder;

   newOrder->name = name;
   newOrder->number_of_pancakes = num_pancakes;
   newOrder->type_of_pancakes = type_of_pancake;

   if(isEmpty()){
      queueFront = newOrder;
      queueEnd = newOrder;
   }
   else{
      CustomerOrder *temp = queueEnd;
      newOrder->next = nullptr;
      temp->next = newOrder;
      queueEnd = newOrder;
   }
}

void ShopQueue::dequeue() {
   // TODO
   if(isEmpty()){
      cout << "Queue empty, cannot dequeue!\n";
   }
   else{
      CustomerOrder *completedOrder = new CustomerOrder;
      completedOrder = queueFront;
      if (queueFront->next == nullptr){
         queueFront = nullptr;
         delete completedOrder;
      }
      else{
         queueFront = queueFront->next;
         delete completedOrder;
      }
   }
}

/**
 * Should return the total number of customers in the queue. 
 * @returns The total number of elements
 */
int ShopQueue::queueSize(){
   // TODO

   int numCustomers = 0;
   CustomerOrder *current = queueFront;

   while(current != nullptr){
      numCustomers++;
      current = current->next;
   }

   return numCustomers;
}

/**
 * Just returns the end of the queue. Used for testing. Do not touch! :)
 */ 
CustomerOrder* ShopQueue::getQueueEnd(){
   return queueEnd;
}