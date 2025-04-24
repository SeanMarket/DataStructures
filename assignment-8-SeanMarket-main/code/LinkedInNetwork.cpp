#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    bool found = false;
    for(int i = 0; i < professionals.size(); i++){
        if(professionals[i]->name == name){
            found == true;
        }
    }
    if (found == false){

        Professional* newProf = new Professional;
        newProf->name = name;
        professionals.push_back(newProf);
    }
}

void LinkedInNetwork::addConnection(string v1, string v2){
    for(int i = 0; i < professionals.size(); i++){
        if(professionals[i]->name == v1){
            for(int j=0; j < professionals.size(); j++){
                if(professionals[j]->name == v2 && i!=j){
                    neighbor adjProf;
                    adjProf.v = professionals[j];
                    professionals[i]->neighbors.push_back(adjProf);

                    neighbor adjProf2;
                    adjProf2.v=professionals[i];
                    professionals[j]->neighbors.push_back(adjProf2);
                }
            }
        }
    }
}

void LinkedInNetwork::displayConnections(){
     for(int i=0; i < professionals.size(); i++){
        cout << professionals[i]->name << " --> ";
        for (int j=0; j < professionals[i]->neighbors.size(); j++){
            cout << professionals[i]->neighbors[j].v->name;
            if(j < professionals[i]->neighbors.size()){
                cout << ' ';
            }
        }
        cout << '\n';
     }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    Professional *vStart;
    for(int i=0; i < professionals.size(); i++){
        if(professionals[i]->name == sourceProfessional){
            vStart = professionals[i];
        }
    }
    cout << "Starting Professional (root): " << sourceProfessional << "-> ";

    vStart->visited = true;
    queue<Professional*> q;

    q.push(vStart);

    Professional* n;

    while(!q.empty()){
        n = q.front();
        q.pop();
        for(int x=0; x < n->neighbors.size(); x++){
            if(!n->neighbors[x].v->visited){
                n->neighbors[x].v->connectionOrder = n->connectionOrder+1;
                n->neighbors[x].v->visited = true;
                q.push(n->neighbors[x].v);
                cout << n->neighbors[x].v->name <<"("<< n->neighbors[x].v->connectionOrder <<")"<< " ";
            }
        }
    }
}

vector<string> bfs_helper(string source, vector<Professional*> &professionals, vector<string> professionalsWithinK, int k) {
    Professional *vStart;
    for(int i=0; i < professionals.size(); i++){
        if(professionals[i]->name == source){
            vStart = professionals[i];
        }
    }

    vStart->visited = true;
    queue<Professional*> q;

    q.push(vStart);

    Professional* n;

    while(!q.empty()){
        n = q.front();
        q.pop();
        for(int x=0; x < n->neighbors.size(); x++){
            if(!n->neighbors[x].v->visited){
                n->neighbors[x].v->connectionOrder = n->connectionOrder+1;

                if(n->neighbors[x].v->connectionOrder <= k  && n->neighbors[x].v->connectionOrder > 0){
                    professionalsWithinK.push_back(n->neighbors[x].v->name);
                }

                n->neighbors[x].v->visited = true;
                q.push(n->neighbors[x].v);
            }
        }
    }

    vector<string> ret;
    for(int i = 0; i < professionals.size(); i++){
        for(int j = 0; j < professionalsWithinK.size();j++){
            if (professionalsWithinK[j] == professionals[i]->name){
                ret.push_back(professionalsWithinK[j]);
            }
        }
    }
    // reverse(professionalsWithinK.begin(), professionalsWithinK.end());

    return ret;
}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<string> professionalsWithinK;
    

    return bfs_helper(professionalName, professionals, professionalsWithinK, k);
}