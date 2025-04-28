// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include<sstream>


using namespace std;


node* HashTable::createNode(string charName, node* nextNode)
{
	node* newNode = new node;
	
	if(nextNode == nullptr){

		newNode->next = nullptr;
	}
	else{
		newNode->next = nextNode;
	}
	newNode->characterName = charName;

	
	return newNode;
}


HashTable::HashTable(int bsize)
{
	cout << "Create hashtable\n";
	tableSize = bsize;
	numCollision = 0;

	node* *arr = new node*[tableSize];

	table = arr;

	for(int i = 0; i < tableSize; i++){
		table[i] = nullptr;
	}
}

HashTable::~HashTable(){
//TODO
	for(int i = 0; i < tableSize; i++){
		node* curr = table[i];
		if(curr == nullptr){
			continue;
		}

		node* next = curr->next;
		while(curr != nullptr){//Loop through all characters and delete the PQ and then the node itself.
			// curr->pq.removePriorityQ();
			next = curr->next;
			delete curr;
			curr = next;
		}
		delete curr; //have to call one more time for the very last node.
	}

	delete[] table;

}


void HashTable::printTable()
{
	for(int i = 0; i < tableSize; i++){
		cout << "table[" << i <<"]: ";
		if(table[i] != nullptr){
			node* curr = table[i];
			while(curr != nullptr){
				cout << curr->characterName;

				if(curr->next != nullptr){
					cout << ", ";
				}

				curr = curr->next;
			}
		}
		cout << '\n';
	}
}


//function to calculate hash function
unsigned int HashTable::hashFunction(string charName)
{

	int numChars = 0;
	for(char c : charName){
		numChars += c;
	}

	unsigned int hashNum = numChars%tableSize;


	return hashNum;
}



node* HashTable::searchCharacter(string charName)
{
	
	int charHash = hashFunction(charName);

	if((table[charHash] == nullptr)){
		return nullptr;
	}
	else if((table[charHash]->characterName != charName) && (table[charHash]->next == nullptr)){//check if chain empty
		return nullptr;
	}
	else if(table[charHash]->characterName == charName){
		return table[charHash];
	}
	else if((table[charHash]->characterName != charName) && (table[charHash]->next != nullptr)){ //check chain
		node* curr = table[charHash]->next;

		while((curr->characterName != charName)){
			if(curr->next == nullptr){
				return nullptr;
			}

			curr = curr->next;
		}
		return curr;
	}

	return nullptr;
}



//function to insert
void HashTable::insertItem(ItemInfo newItem)
{
	node* found = searchCharacter(newItem.characterName);

	if(found != nullptr){
		found->pq.insertElement(newItem);
		return;
	}

	node* newNode = createNode(newItem.characterName, nullptr);

	int hashNum = hashFunction(newItem.characterName);
	newNode->pq.insertElement(newItem);

	if(table[hashNum] == nullptr){
		table[hashNum] = newNode;
		return;
	}

	numCollision++;

	node* curr = table[hashNum];

	while(curr->next != nullptr){
		curr = curr->next;
	}
	

	curr->next = newNode;

	return;

}

void HashTable:: buildBulk(string fname)
{

	ifstream infile;
	infile.open(fname);

	if(!infile.is_open()){
		cout << "Error opening file\n";
		return;
	}

	int attribute = 0;
	string line;
	while(getline(infile, line)){
		string sepLine;
		istringstream streamLine(line);

		string attributes[4];

		int counter = 0;
		while(getline(streamLine, sepLine, ';')){
			attributes[counter] = sepLine;
			counter++;
		}
		ItemInfo info;
		
		info.characterName = attributes[0];
		info.itemName = attributes[1];
		info.damage = stoi(attributes[2]);
		info.comment = attributes[3];

		insertItem(info);
		
	}


}

void HashTable::deleteEntry(string charName) {

	node* character = searchCharacter(charName);

	if(character == nullptr){
		cout << "no record found\n";
		return;
	}

	character->pq.deleteKey(charName);


	if(character->pq.isEmpty()){
		node* prev = nullptr;
		node* next = character->next;
		node* curr = nullptr;

		for(int i = 0; i < tableSize; i++ ){
			if(table[i]->characterName == character->characterName && character->next != nullptr){
				table[i] = next;
				return;
			}
			else if(table[i]->characterName == character->characterName && character->next == nullptr){
				table[i] = nullptr;
				delete character;
				return;
			}
			else if(table[i]->next != nullptr && table[i]->characterName != character->characterName){
				curr = table[i];
				while(curr != nullptr){ //find previous node

					if(curr->next == character){
						prev = curr;
						break;
					}

					curr = curr->next;
				}
			}
		}

		prev->next = next;

		numCollision--;
		
		delete character;
	}
}