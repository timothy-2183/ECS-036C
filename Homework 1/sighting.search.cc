#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <string>
#include <sstream>

// Defining a data structure used to store pairs of values, hence using tuples containing <speed, brightness, signature>
class sighting{
    public:
    int speed;
    int brightness;
    int signature;
    sighting(int a, int b){
        speed = a;
        brightness = b;
        signature = a*b/10;
    }
    
};

/*
Name        : readFile
Description : Creates a vector of sightings which gets filled with the information of the File
Receives    : Filename (string, by reference)
Returns     : Shared Pointer to the vector containing <sighting> objects.
*/
std::vector<sighting>* readFile(const std::string& filename){
    (void) filename;
    return nullptr;
}

/*
Name        : linearSearch
Description : looks for the items that has the same signature in a linear manner
Receives    : Shared pointer to the sighting vector, Shared pointer to the signature
Returns     : Amount of signature found in the 
*/



int main(){
    return 0;
}