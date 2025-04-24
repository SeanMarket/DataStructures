#include "array_double.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

void parseFile(ifstream &input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter)
{
    string temp;
    int arraySize = 10;

    while (getline(input, temp))
    {
        // process the case by tab separated values, by using istringstream or similar constructs.
        string tempArray[4];
        istringstream streamTemp(temp);
        AirlinePassenger tempPassenger;
        for (int j = 0; j < 4; j++)
        {
            getline(streamTemp, tempArray[j], ',');
        }

        tempPassenger.name = tempArray[0];
        tempPassenger.airline = tempArray[1];
        tempPassenger.location = tempArray[2];
        tempPassenger.age = stoi(tempArray[3]);

        if (isPassengerQueried(tempPassenger, queryParams[0], queryParams[1], stoi(queryParams[2]), stoi(queryParams[3])))
        {
            // if(recordIdx == arrCapacity){ // replace with addPassenger
            //     resizeArr(passengers, &arrCapacity);
            // }
            // passengers[recordIdx].name = tempPassenger.name;
            // passengers[recordIdx].airline = tempPassenger.airline;
            // passengers[recordIdx].location = tempPassenger.location;
            // passengers[recordIdx].age = tempPassenger.age;
            // recordIdx++;
            addPassenger(passengers, tempPassenger, arrCapacity, recordIdx, doublingCounter);
        }
    }
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge)
{
    //TODO
    if ((passenger.airline == queryAirline) && (passenger.location == queryLocation) && (passenger.age >= startAge) && (passenger.age <= endAge))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize)
{
    int newSize = *arraySize * 2;
    AirlinePassenger *tempPassengers = new AirlinePassenger[newSize];
    for (int i = 0; i < *arraySize; i++)
    {
        tempPassengers[i] = passengers[i];
    }
    delete[] passengers;
    passengers = tempPassengers;
    *arraySize = newSize;
    //TODO
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter)
{
    if (recordIdx == arrCapacity)
    {
        resizeArr(passengers, &arrCapacity);
        doublingCounter++;
    }
    passengers[recordIdx] = airlinePassenger;

    recordIdx++;
    //TODO
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length)
{
    //TODO
    AirlinePassenger temp;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        { //don't need to operate on final element
            if (passengers[j].age < passengers[j + 1].age)
            {

                temp = passengers[j];
                passengers[j] = passengers[j + 1];
                passengers[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        { //don't need to operate on final element
            if (passengers[j].age == passengers[j + 1].age)
            {
                if (passengers[j].name > passengers[j + 1].name)
                {

                    temp = passengers[j];
                    passengers[j] = passengers[j + 1];
                    passengers[j + 1] = temp;
                }
            }
        }
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords)
{
    sortPassengers(passengers, numOfRecords);

    cout << "Queried Passengers\n---------------------------------------" << endl;
    for(int i = 0; i < numOfRecords; i++){
        cout << passengers[i].name << " " << passengers[i].age << endl;
    }

    //TODO
}
