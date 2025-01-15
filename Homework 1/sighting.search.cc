#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>

/*
Name        : readFile
Description : Creates a vector of sightings which gets filled with the information of the File
Receives    : Filename (string, by reference)
Returns     : Shared Pointer to the vector containing int of the btightness of the objects .
*/
std::vector<int> readFile(const std::string& filename){
    std::vector<int> sightingSignature={};
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "File Failed to Open" << std::endl;
        return sightingSignature;
    }
    std::string line;
    while (std::getline(myFile,line))
    {
        std::istringstream iss (line);
        int speed, brightness;
        if (iss >> speed >> brightness) sightingSignature.push_back(speed*brightness/10);
    }
    if (!sightingSignature.empty()){
        std::sort(sightingSignature.begin(),sightingSignature.back(), [] (int a, int b){return a < b;});
    }
    return sightingSignature;
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