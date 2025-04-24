#include "/home/jovyan/CSCI2270/Week13/assignment-9-SeanMarket/code/Dungeon.hpp"
using namespace std;

void displayVertex(vertex* vertex);

int main(){
    Dungeon d(3);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            d.dungeon[i][j] = open;
            d.addVertex(i, j, open);
        }
    }

    d.convertDungeonToAdjacencyListGraph();

    if(d.isContaminated(1,1) == true){
        cout << "1,1 cont\n";
    }
    else{
        cout << "1,1 not cont\n";
    }

    d.dungeon[0][0] = radioactive;

    d.convertDungeonToAdjacencyListGraph();

    if(d.isContaminated(0,1) == true){
        cout << "0,1 cont\n";
    }
    else{
        cout << "0,1 not cont\n";
    }
    if(d.isContaminated(1,1) == true){
        cout << "1,1 cont\n";
    }
    else{
        cout << "1,1 not cont\n";
    }
    if(d.isContaminated(2,2) == true){
        cout << "2,2 cont\n";
    }
    else{
        cout << "2,2 not cont\n";
    }



    return 0;
}

void displayVertex(vertex* vertex){ //debugging function
    cout << "x: " << vertex->x << '\n';
    cout << "y: " << vertex->y << '\n';
    cout << "Type: " << vertex->c << '\n';
    cout << "VertexNum = " << vertex->vertexNum << '\n';
}