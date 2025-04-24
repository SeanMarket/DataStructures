#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 6){
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Airline> <Query_Start_Age> <Query_End_Age>\n";
        return -1;
    }


    int numParams = 4;
    string queryParams[numParams];
    for(int i = 0; i < numParams; i++){
        queryParams[i] = argv[i+2]; //skip run command and input file
    }

    int arrayCapacity = 10;
    int recordIndex = 0;
    int doublingCounter = 0;
    AirlinePassenger *array = new AirlinePassenger[arrayCapacity];
    ifstream inFile;       // stream for reading in file
    inFile.open(argv[1]); //file location

    if(!(inFile.is_open())){
        cout << "File failed to open\n";
        return -1;
    }
    
    parseFile(inFile, queryParams, array, arrayCapacity, recordIndex, doublingCounter);
    //TODO 

    // for (int i = 0; i < recordIndex; i++){
    //     cout << array[i].name << '\n';
    // }
    cout << "Array doubled: " <<  doublingCounter << '\n';
    cout << "Total number of passengers returned after the query: " << recordIndex << '\n';
    printQueriedPassengers(array, recordIndex);

    delete[] array;
    return 0;
}
