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
Name        : readFileSightings
Description : Creates a vector of sightings which gets filled with the signature of the sighting File
Receives    : Filename (string, by reference)
Returns     : Vector containing int of the signatures for these sightings.
*/
std::vector<int> readFileSightings(const std::string& filename){
    std::vector<int> sightingSignature={};
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "File Failed to Open" << std::endl;
        return sightingSignature;
    }
    int brightness, speed;
    while (myFile >> brightness >> speed) {
        sightingSignature.push_back(brightness*speed/10);
    }
    if (!sightingSignature.empty()){
        std::sort(sightingSignature.begin(),sightingSignature.end(), [] (int a, int b){return a < b;});
    }
    myFile.close();
    return sightingSignature;
}

/*
Name        : readFileSignatures
Description : Creates a vector of sightings which gets filled with the signature of the known aircraft signatureFile
Receives    : Filename (string, by reference)
Returns     : Vector containing int of the signatures of the known aircrafts. .
*/
std::vector<int> readFileSignatures(const std::string& filename){
    std::vector<int> Signature={};
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "File Failed to Open" << std::endl;
        return Signature;
    }
    int num;
    while (myFile >> num) {
        Signature.push_back(num);
    }
    if (!Signature.empty()){
        std::sort(Signature.begin(),Signature.end(), [] (int a, int b){return a < b;});
    }
    myFile.close();
    return Signature;
}

/*
Name        : linearSearch
Description : looks for the items that has the same signature in a linear manner
Receives    : vector of sightings, vector of the signature
Returns     : Amount of sightings that are the same as the signatures.
*/

int linearsearch(const std::vector<int>& sightings, const std::vector<int>& signature){
    int count = 0;
    for (size_t i = 0; i < sightings.size(); i++)
    {
        for (size_t j = 0; j < signature.size(); j++)
        {
            if (sightings[i]==signature[j])
            {
                ++count;
            }
        }
        
    }
    return count;
}

/*
Name        : binSearch
Description : looks for the items that has the same signature by calling the recursive Binary Search.
Receives    : vector of sightings, vector of the signature
Returns     : Amount of sightings that are the same as the signatures.
*/
int binSearch(const std::vector<int>& sightings,const std::vector<int>& signatures){
    int count = 0;
    for (size_t i = 0; i < sightings.size(); i++)
    {
        count +=binrec(0, signatures.size()-1, sightings[i], signatures);
    }
    return count;
}
int binrec (int front, int back, int search, const std::vector<int>& signatures){
    if (front>=back)
    {
        return 0;
    }
    int curr = signatures[(front+back)/2];
    if (signatures[curr]==search) {return 1;}
    else if (signatures[curr]>search){ return binrec (front, curr-1, search, signatures);}
    else{ return binrec (curr+1, back, search, signatures);}
}
int main(){
    return 0;
}