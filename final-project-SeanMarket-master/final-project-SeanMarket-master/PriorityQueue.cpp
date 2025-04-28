#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b)
{
	ItemInfo *temp = a;
	*b = *temp;
	*a = *b;

	return;
}

PriorityQ::PriorityQ()
{
	capacity = 50;
	ItemInfo *arr = new ItemInfo[capacity];
	heapArr = arr;
	currentSize = 0;

	for(int i = 0; i < capacity; i++){
		arr[i].characterName = "null";
		arr[i].comment = "null";
		arr[i].damage = 0;
		arr[i].itemName = "null";
	}

}

PriorityQ::~PriorityQ(){ //don't want a normal destructor. Was trying to call destructor after building
	delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
	//find a possible parent
	//check to see if the given index is a left node
	//check to see if the given index is a right node
	//return whichever returns true


	if((index == capacity - 1) && (index%2 == 0)){ //if there is an even number of nodes and the index is the last node
		return (index-2)/2;
	}
	else if ((index == capacity - 1) && (index%2 != 0)){ //if there is an odd number of nodes and the index is the last node.
		return (index-1)/2;
	}
	else{
		double parent = (index-1)/2; //if given index is left child
		int intParent = parent;

		if(heapArr[intParent].characterName != "null"){
			return parent;
		}

		if(parent < 0){
			return -1;
		}

		parent = (index-2)/2; //if given index is a right child

		if(heapArr[intParent].characterName != "null"){
			return parent;
		}

		if(parent < 0){
			return -1;
		}

		cout << "Parent not found\n";

		return 0;
		
	}

}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
	return 2*index + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
	return 2*index + 2;
}

ItemInfo* PriorityQ::peek()
{
	return heapArr;
}

void PriorityQ::heapify(int i)
{

	int leftChild = this->leftChild(i);
	int rightChild = this->rightChild(i);
	int parent = this->parent(i);


	if(heapArr[i].characterName == "null"){
		return;
	}

	if(heapArr[i].damage > heapArr[parent].damage){
		swap(heapArr[i], heapArr[parent]);
		heapify(parent);
	}

	if(heapArr[leftChild].damage >  heapArr[i].damage){
		swap(heapArr[leftChild], heapArr[i]);
	}

	if(heapArr[rightChild].damage > heapArr[i].damage){
		swap(heapArr[rightChild], heapArr[i]);
	}

	if(heapArr[0].characterName == heapArr[i].characterName){
		return;
	}

	heapify(parent);

}

void PriorityQ::insertElement(ItemInfo item)
{

	
	if(currentSize < capacity){
		heapArr[currentSize].characterName = item.characterName;
		heapArr[currentSize].damage = item.damage;
		heapArr[currentSize].comment = item.comment;
		heapArr[currentSize].itemName = item.itemName;

		currentSize++;
	}
	else{
		cout << "Cannot insert, PQ full\n";
		return;
	}

	heapify(currentSize-1);
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{

	for(int i = 0; i < currentSize; i++){
		cout << "\tIndex: " << i << '\n';
		cout <<"\tItem: " << heapArr[i].itemName << '\n';
		cout <<"\tDamage: " << heapArr[i].damage << '\n';
		cout <<"\tComment: " << heapArr[i].comment << '\n';
		cout << "\t=================\n";
	}
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) { //more like heapify helper

	int left = leftChild(i);
	int right = rightChild(i);

	if(heapArr[i].characterName == "null" && heapArr[left].characterName == "null"){ //only need to check left because right is greater than left.
		return;
	}

	if(heapArr[left].damage >  heapArr[i].damage){
		swap(heapArr[left], heapArr[i]);
	}

	if(heapArr[right].damage > heapArr[i].damage){
		swap(heapArr[right], heapArr[i]);
	}

	popHelper(right);
	popHelper(left);
}

// Method to remove max element (or root) from max heap
void PriorityQ::pop()
{
	deleteKey(heapArr[0].itemName);
	
}

void PriorityQ::deleteKey(string item){
	//swap with last non-null element, heapify.
	for(int i = 0; i < currentSize; i++){
		if(heapArr[i].characterName == item){
			
			heapArr[i].characterName = "null";
			heapArr[i].comment = "null";
			heapArr[i].damage = 0;
			heapArr[i].itemName = "null";

			currentSize--;

			if(currentSize == 0){
				return;
			}
			swap(heapArr[i], heapArr[currentSize]);

			popHelper(0);

			
			return;
		}
	}

}