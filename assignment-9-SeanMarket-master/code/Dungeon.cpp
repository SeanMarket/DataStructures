#include "Dungeon.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

vector<vertex*> search(vector<int> cellNums, vector<vertex*> vertices){
    vector<vertex*> cells;

    for(int num : cellNums){
        for(vertex* itVertex : vertices){
            if(itVertex->vertexNum == num){
                cells.push_back(itVertex);
            }
        }
    }
    return cells;
}

int findVertexNumFromPositionHelper(int x, int y,int n){
    int vertexNum = 0;
    // int yPosition = y*n; //The dungeon is n x n in size.
    int xPosition = x*n;
    // vertexNum = yPosition + x;
    vertexNum = xPosition + y;
    return vertexNum;
}


bool isValidNum(int x, int y,int max){
    if(x < 0 || y < 0){
        return false;
    }
    
    if(x >= max || y >= max){
        return false;
    }
    
    return true;
}


void findNeighbors(int x, int y, int max, vector<int>& cellNums){
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j<= y+1; j++){
            if(isValidNum(i,j, max) && (i!= x || j !=y)){
                cellNums.push_back(findVertexNumFromPositionHelper(i,j, max));
            }
        }
    }
}

vector<int> adjPathHelper(vector<int> cellNums, vector<vertex*> vertices, Dungeon* dungeon){ //Creates a vector of the adjacent cells, and then determines which cells are traversable.
    vector<vertex*> cells = search(cellNums, vertices);
    
    vector<int> traversableCellNums;

    for(vertex* vertex : cells){
        if(!dungeon->isContaminated(vertex->x, vertex->y) && (dungeon->dungeon[vertex->x][vertex->y] != wall )){
            traversableCellNums.push_back(vertex->vertexNum);
    
        }
    }


    return traversableCellNums;
}

Dungeon::Dungeon(int size){
    //Given - This functions initializes the matrix in the heap
    n = size;

    dungeon = new cell_type* [n];
    for(int i=0; i<n; i++){
        dungeon[i] = new cell_type[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dungeon[i][j] = END;
        }
    }
}

/**
 * @brief This function should add a new vertex to the graph 
 * 
 * @param x x-cordinate of the cell
 * @param y y-cordinate of the cell
 * @param typeOfCell the type of the cell
 */
void Dungeon::addVertex(int x, int y, cell_type typeOfCell){
    vertex* newVertex = new vertex;
    newVertex->x = x;
    newVertex->y = y;
    newVertex->c = typeOfCell;
    
    newVertex->vertexNum = findVertexNumFromPosition(x, y);
    vertices.push_back(newVertex);
}


/**
 * @brief Finds the vertex number from the position of the open path in the maze
 * 
 * @param x the x-cordinate of the cell
 * @param y the y-codinate of the cell
 * @return int the vertex number of the cell
 */
int Dungeon::findVertexNumFromPosition(int x, int y){
    return findVertexNumFromPositionHelper(x, y, n); // the dungeon is n x n in size
}

/**
 * @brief Given the x,y cordinates of a cell, find the vertex no.s of the cells that are adjacent and possible to visit.
 * 
 * @param x 
 * @param y 
 * @return vector<int> 
 */
vector<int> Dungeon::findOpenAdjacentPaths(int x, int y){
    vector<int> neighbors;
    findNeighbors(x, y, n, neighbors);

    vector<int> traversableCellNums = adjPathHelper(neighbors, vertices, this);
    return traversableCellNums;

}

/**
 * @brief For each cell, find and store it's neighbors, essentially converting the matrix to an adjacency list representation. 
 * 
 */
void Dungeon::convertDungeonToAdjacencyListGraph(){

    //visit each cell
    for(vertex* current : vertices){
        //visit neighbors, ignoring invalid cells (walls & contaminated)
        vector<int>openPaths = findOpenAdjacentPaths(current->x, current->y);
        vector<vertex*> openVertices = search(openPaths, vertices);

        for(auto openNeighbor : openVertices){
            adjVertex adjItVertex{openNeighbor};
            current->adj.push_back(adjItVertex);
        }
    }
}


/**
 * @brief Determine whether a cell is contaminated 
 */
bool Dungeon::isContaminated(int x, int y){

    if(dungeon[x][y] == radioactive){
        return true;
    }

    vector<int> neighbors;

    findNeighbors(x, y, n, neighbors);
    
    vector<vertex*> pNeighbors = search(neighbors, vertices);
    for(auto neighbor : pNeighbors){
        if(dungeon[neighbor->x][neighbor->y] == radioactive){
            return true;
        }
    }

    return false;
}


/**
 * This function is supposed to return true if the Dungeon is traversal is possible and false if not.
 */
bool Dungeon::isDungeonTraversable(){
    //TODO
    vertex* vStart;
    for(int i = 0; i < vertices.size(); i++){
        // if(vertices[i]->c == start){
        //     vStart = vertices[i];
        // }
        if(dungeon[vertices[i]->x][vertices[i]->y] == start){
            vStart = vertices[i];
            break;
        }
    }

    vStart->visited = true;
    stack<vertex*> s;

    s.push(vStart);

    vertex* n;

    while(!s.empty()){
        n = s.top();
        s.pop();

        if(dungeon[n->x][n->y] == END){
            return true;
        }

        for(int i = 0; i < n->adj.size(); i++){
            if(!n->adj[i].v->visited){
                n->adj[i].v->visited = true;
                s.push(n->adj[i].v);
            }
        }
    }

    return false;
}


/**
 * @brief Destroy the Dungeon:: Dungeon object
 * 
 */
Dungeon::~Dungeon(){
    //TODO

    for(int i = 0; i < n; i++){
        delete[] dungeon[i];
    }
    delete dungeon;
}

