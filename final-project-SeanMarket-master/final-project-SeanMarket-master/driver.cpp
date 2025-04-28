#include<iostream>
#include <vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>


#include "hash.hpp"
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"

using namespace std;
using namespace std::chrono;

void displayMenu()//keep it in starter code
{
    cout<<"------------------"<<endl;
    cout<<"1: Build the datastructure (call it only once)"<<endl;
    cout<<"2: Add a new item"<<endl;
    cout<<"3: Peek most powerful item from character"<<endl;
    cout<<"4: Pop most powerful item from character"<<endl;
    cout<<"5: Print all items for character"<<endl;
    cout<<"6: Get number of collisions"<<endl;
    cout<<"7: Print the table"<<endl;
	cout<<"8: Find easiest route through dungeon"<<endl;
    cout<<"9: Exit"<<endl;
    cout<<"------------------"<<endl;

}

bool validateInteger(string input)
{
    if (input.length() == 0)
    {
        return false;
    }

    if (input.length() == 1)
    {
        return isdigit(input.at(0));
    }

    if (input.at(0) != '-' && !isdigit(input.at(0)))
    {
        return false;
    }

    for (int i = 1; i < input.length(); i++)
    {
        if (!isdigit(input.at(i)))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct num of arg"<<endl;
    }
    string fname =argv[1];
    int tableSize = stoi(argv[2]);
    
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool built = false;
    //TODO validate int for input
    while(ch!=9)
    {
        displayMenu();
        cout<<"Give your choice >> ";
        getline(cin, chs);
        while(!validateInteger(chs)){
            cout << "Enter a valid int (1-10): ";
            getline(cin,chs);
        }
        ch =stoi(chs);
        switch (ch)
        {
            case 1:{ // bulk build (should only build on first call)
                if(built){
                    cout << "File already built\n";
                    break;
                }

                cout << "Building...\n";
                ht.buildBulk(fname);

                cout << "File built\n";

                built = true;

                break;
            }
            case 2:{ // Insert new items from console

                ItemInfo newItem;

                cout << "Character Name: ";
                string name;
                getline(cin, name);

                node* found = ht.searchCharacter(name);

                while(found == nullptr){
                    cout << "Enter a valid character\n";
                    cout << "Character Name: ";
                    getline(cin,name);
                    found = ht.searchCharacter(name);
                }

                newItem.characterName = name;

                cout << "\nItem Name: ";
                getline(cin, newItem.itemName);

                cout <<"\nDamage: ";
                string damage;
                cin >> damage;
                if(validateInteger(damage)){
                    newItem.damage = stoi(damage);
                }
                else{
                    while(!validateInteger(damage)){
                        cout << "Please enter an integer\n";
                        cin >> damage;

                    }
                    newItem.damage = stoi(damage);
                }

                cout<< "\nComment: ";
                cin.ignore();
                getline(cin, newItem.comment);
                cout << '\n';

                ht.insertItem(newItem);

                break;



            }
            case 3:{ // Peek 

                string characterName = "";

                cout << "Character: ";
                getline(cin, characterName);
                cout << '\n';

                node* character = ht.searchCharacter(characterName);
                
                if((character == nullptr)){
                    cout << "Character not found\n";
                    break;
                }

                cout << "retreieved result\n";

                cout<< "Character: " << character->characterName << '\n';
                cout << "Item: " << character->pq.peek()->itemName << '\n';
                cout << "Damage: " << character->pq.peek()->damage << '\n';
                cout << "Comment: " << character->pq.peek()->comment << '\n';

                break;

			}
            case 4:{ // Pop
				string characterName;

                cout << "Character name: ";
                getline(cin, characterName);

                node* character = ht.searchCharacter(characterName);
                if(character == nullptr){
                    cout << "Character not found\n";
                    break;
                }

                ht.deleteEntry(characterName);

                cout << "Successfully popped\n";
                break;
            }
            case 5:{ // Print all items for character

                string characterName;

                cout << "Character Name: ";
                getline(cin, characterName);
                cout << '\n';
                
                node* character = ht.searchCharacter(characterName);
                if(character == nullptr){
                    cout << "Character not found\n";
                    break;
                }

                character->pq.print();
                break;
			}
            case 6: { // Display collisions
                cout << "Number of Collisions: " << ht.getNumCollision() << '\n';
                break;
			}
            case 7: { // Print table
				ht.printTable();
                break;
			}
			case 8:{ // Find easiest path through dungeon
				cout << "Input dungeon(file name): " << endl;
				string dungeonFile;
				getline(cin, dungeonFile);
				EnemyGraph G;
				G.buildGraphFromFile(dungeonFile);
				cout << G.findEasiestPath(ht) << endl;
				break;
			}
			case 9:
				cout << "Goodbye..." << endl;
                return 0;
				break;
       
            default:
                cout<<"Give a valid entry"<<endl;
                break;
        }
    }
}
