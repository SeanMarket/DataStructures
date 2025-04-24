/*************************************************************/
/*                PancakeHouse Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of PancakeHouse    */
/*************************************************************/

#include "PancakeHouse.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
int const PancakeHouse::pancake_types[] = {1, 2, 5, 3, 7};


/**
 * Constructor for the Pancake House
 */
PancakeHouse::PancakeHouse() {
    profit = 0;
    pancakesCooked = 0;
    cashRegister = new Register;
    shopQueue = new ShopQueue;
}

/**
 * Destructor for the pancake house. Removes the register and shopQueue.
 */
PancakeHouse::~PancakeHouse(){
    delete shopQueue;
    delete cashRegister;
}

/**
 * Gets the stack.
 * @returns The cash register
 */
Register* PancakeHouse::getStack(){
    return cashRegister;
}

/**
 * Gets the queue.
 * @returns The shop queue
 */
ShopQueue* PancakeHouse::getQueue() {
    return shopQueue;
}

/**
 * Gets the profit class variable
 * @returns The profit
 */
int PancakeHouse::getProfit(){
    return profit;
}

/**
 * This function should add orders to the queue. 
 * @param name The name of the person to be added
 * @param number_of_pancakes The total number of pancakes to be ordered
 * @param type_of_pancakes The type of pancake to be cooked (i.e., the 'price' of the pancake). There are 5 types, anything outside of the range 1-5 should be rejected.
 */
void PancakeHouse::addOrder(string name, int number_of_pancakes, int type_of_pancakes) {
    // TODO
    if(type_of_pancakes < 1 || type_of_pancakes > 5){
        return;
    }
    else{
        shopQueue->enqueue(name, number_of_pancakes, type_of_pancakes);
    }
}

/**
 * This should cook an order of pancakes. By removing an element from the queue (if one exists) it should then calculate the price
 * of an order (num pancakes*type price). The price should then be pushed onto the stack if a space exists.
 * 
 */
void PancakeHouse::cookPancakes() {
    // TODO
    CustomerOrder *order = new CustomerOrder;
    order = shopQueue->peek();

    if(shopQueue->isEmpty()){
        return;
    }

    pancakesCooked += order->number_of_pancakes;


    int money = order->number_of_pancakes * pancake_types[order->type_of_pancakes - 1];

    // cout << order->number_of_pancakes << '\n';
    // cout << pancake_types[order->type_of_pancakes - 1] << '\n';

    // cout << order->number_of_pancakes * pancake_types[order->type_of_pancakes - 1] << '\n';

    cashRegister->push(money); //type of pancakes array is 0 indexed, pancake types are 1 indexed

    strikeOrder();

}

/*
 * This function will cancel the existing order in the queue
 */
void PancakeHouse::strikeOrder(){
    // TODO
    shopQueue->dequeue();
}

/*
 * Takes out the recent order from stack, displays the money refunded and takes away from the profit class variable
 */
void PancakeHouse::refundOrder(){
    // TODO
    if(cashRegister->isEmpty()){
        cout << "Stack empty, cannot pop an item!\n";
        cout << "No money in the cash register!\n";
        return;
    }else{
        cout << "Money refunded = " << cashRegister->pop() << '\n';
    }
}

/**
 * Closes the shop for the day. Should remove the queue elements and remove all of the elements off of the register.
 */
void PancakeHouse::closeShop(){
    // TODO
    while(!(shopQueue->isEmpty())){
        shopQueue->dequeue();
    }
    while(!(cashRegister->isEmpty())){
        cashRegister->pop();
    }
}

/**
 * Should get the total profit that is contained in the register. Removes each element from the register and adds it to the 
 * profit variable.
 */
void PancakeHouse::updateTotalProfit(){
    // TODO
    while(!cashRegister->isEmpty()){
        profit += cashRegister->pop();
    }
}

/**
 * Runs through the order queue and prints each order. The queue elements should remain untouched!
 */
void PancakeHouse::printOrders(){ // how to walk through queue without dequeueing
    // TODO
    CustomerOrder *order = new CustomerOrder;
    order = shopQueue->peek();

    while(order != nullptr){
        cout << "Customer name: " << order->name << '\n';
        cout << "Number of pancakes ordered: " << order->number_of_pancakes << '\n';
        cout << "Type of pancakes: " << order->type_of_pancakes << '\n';
        order = order->next;
    }
}