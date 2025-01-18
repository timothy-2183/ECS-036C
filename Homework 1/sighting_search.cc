#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>

class Time{
    private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    public:
    double elapsed_us;
    void Reset(){
        start = std::chrono::high_resolution_clock::now();
    }
    double CurrentTime(){
        end = std::chrono::high_resolution_clock::now();
        elapsed_us = std::chrono::duration<double, std::micro> (end - start).count();
        return elapsed_us;
    }
};

/*
Name        : linearSearch
Description : looks for the items that has the same signature in a linear manner
Receives    : vector of sightings, vector of the signature
Returns     : Amount of sightings that are the same as the signatures.
*/

int linearsearch(const std::vector<int> &sightings, const std::vector<int> &signature)
{
    int count = 0;
    for (auto i : sightings)
    {
        for (auto j : signature)
        {
            if (i == j)
            {
                count++;
            }   
        }
    }
    return count;
}

int linearsearch(int search , const std::vector<int> &myVec)
{
    for (auto i : myVec)
    {
        if (i == search)
        {
            return 1;
        }
        
    }
    return 0;
}
/*
Name        : binrec
Description : Looks at the middle of the sorted array, looks left to find the number if it's bigger, looks right otherwise.
Receives    : start of the search, end of the search, the search term, and the signature array.
Returns     : Amount of sightings that are the same as the signatures.
*/
int binrec(int front, int back, int search, const std::vector<int> &signatures)
{
    while (front <= back)
    {
        int mid = front + (back - front) / 2;

        if (signatures[mid] == search)
        {
            return 1;
        }
        else if (signatures[mid] < search)
        {
            front = mid + 1;
        }
        else
        {
            back = mid - 1;
        }
    }
    return 0;
}

/*
Name        : binSearch
Description : looks for the items that has the same signature by calling the recursive Binary Search.
Receives    : vector of sightings, vector of the signature
Returns     : Amount of sightings that are the same as the signatures.
*/
int binSearch(const std::vector<int> &sightings, const std::vector<int> &signatures)
{
    int count = 0;
    for (auto i : signatures)
    {
        count = count + binrec(0, sightings.size() - 1, i,sightings);
    }
    return count;
}

/*
Name        : readFileSightings
Description : Creates a vector of sightings which gets filled with the signature of the sighting File
Receives    : Filename (string, by reference)
Returns     : Vector containing int of the signatures for these sightings.
*/
std::vector<int> readFileSightings(const std::string &filename)
{
    std::vector<int> sightingSignature = {};
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return sightingSignature;
    }
    int speed, brightness;
    while (myFile >> speed >> brightness)
    {
        if (linearsearch(std::ceil(static_cast<double>(static_cast<double>(speed) * static_cast<double>(brightness) / 10)),sightingSignature)==0)
        {
            sightingSignature.push_back(std::ceil(static_cast<double>(static_cast<double>(speed) * static_cast<double>(brightness) / 10)));
        }
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
std::vector<int> readFileSignatures(const std::string &filename)
{
    std::vector<int> Signature;
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return Signature;
    }
    int num;
    while (myFile >> num)
    {
        Signature.push_back(num);
    }
    myFile.close();
    return Signature;
}

int main(int argc, char *argv[])
{
    if (!(argv[1] && argv[2] && argv[3]))
    {
        std::cerr << "Usage: "<< argv[0] <<" <sighting_file.dat> <signature_file.dat> <result_file.dat>";
        return -1;
    }
    Time clock;
    std::string sightingFile = argv[1];
    std::string signatureFile = argv[2];
    std::string resultFile = argv[3];

    auto sightings = readFileSightings(sightingFile);
    auto signature = readFileSignatures(signatureFile);
    if (sightings.empty() || signature.empty())
    {
        return -1;
    }
    char searchTerm;
    std::cout << "Choice of search method ([l]inear, [b]inary)?";
    std::cin >> searchTerm;
    while (searchTerm != 'l' && searchTerm != 'b')
    {
        std::cerr << "Incorrect choice" << std::endl;
        std::cin >> searchTerm;
    }
    
    // Starting clock to Measure the Search speed
    int match = 0;
    if (searchTerm =='l')
    {
        clock.Reset();
        match = linearsearch(sightings, signature);
    }
    else
    {
        clock.Reset();
        std::sort(sightings.begin(),sightings.end());
        match = binSearch(sightings, signature);
    }
    // Ending clock and counting the duration.
    std::cout << match << std::endl;
    std::cout << "CPU time: " << clock.CurrentTime() << " microseconds"<< std::endl;
    
    // Writing the output, taken from https://en.cppreference.com/w/cpp/io/basic_ofstream
    std::ofstream resStream(resultFile);
    if (!resStream.is_open())
    {
        std::cerr << "Error: cannot open file " << resultFile << std::endl;
        return -1;
    }
    else
    {
        resStream << match << " ";
        resStream.close();
    }
    return 0;
}