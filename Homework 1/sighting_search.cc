#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>
#include <unordered_set>

/*
Name        : linearSearch
Description : looks for the items that has the same signature in a linear manner
Receives    : vector of sightings, vector of the signature
Returns     : Amount of sightings that are the same as the signatures.
*/

int linearsearch(const std::vector<int> &sightings, const std::vector<int> &signature)
{
    for (size_t i = 0; i < sightings.size(); i++)
    {
        for (size_t j = 0; j < signature.size(); j++)
        {
            if (sightings[i] == signature[j])
            {
                return 1;
            }
        }
    }
    return 0;
}
/*
Name        : linearSearch (int)
Description : looks for the items that has the same signature in a linear manner
Receives    : int being searched, vector to be searched from
Returns     : 1 or 0 depending on whether the value is found or not.
*/

int linearsearch(int search, const std::vector<int> &searching)
{
    for (size_t j = 0; j < searching.size(); j++)
    {
        if (search == searching[j])
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
    for (size_t i = 0; i < sightings.size(); i++)
    {
        count = count + binrec(0, signatures.size() - 1, sightings[i], signatures);
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
        if (linearsearch(speed * brightness / 10, sightingSignature) == 0)
        {
            sightingSignature.push_back(speed * brightness / 10);
        }
    }
    if (!sightingSignature.empty())
    {
        std::sort(sightingSignature.begin(), sightingSignature.end(), [](int a, int b)
                  { return a < b; });
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
    std::vector<int> Signature = {};
    std::ifstream myFile(filename);
    if (!myFile.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return Signature;
    }
    int num;
    while (myFile >> num)
    {
        if (linearsearch(num, Signature)==0)
        {
            Signature.push_back(num);
        }

        Signature.push_back(num);
    }
    if (!Signature.empty())
    {
        std::sort(Signature.begin(), Signature.end());
    }
    myFile.close();
    return Signature;
}

int main(int argc, char *argv[])
{
    if (!(argv[1] && argv[2] && argv[3]))
    {
        std::cerr << "Usage: /autograder/source/tests/sighting_search <sighting_file.dat> <signature_file.dat> <result_file.dat>";
        return 1;
    }

    std::string sightingFile = argv[1];
    std::string signatureFile = argv[2];
    std::string resultFile = argv[3];

    auto sightings = readFileSightings(sightingFile);
    auto signature = readFileSignatures(signatureFile);

    char searchTerm;
    std::cout << "Choice of search method ([l]inear, [b]inary)?";
    std::cin >> searchTerm;
    while (!(searchTerm == 'l' || searchTerm == 'b'))
    {
        std::cerr << "Incorrect choice";
        std::cin >> searchTerm;
    }
    // Starting clock to Measure the Search speed
    auto start = std::chrono::high_resolution_clock::now();
    int match = 0;
    if (searchTerm == 'l')
    {
        match = binSearch(sightings, signature);
    }
    else
    {
        match = linearsearch(sightings, signature);
    }
    // Ending clock and counting the duration.
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Writing the output, taken from https://en.cppreference.com/w/cpp/io/basic_ofstream
    std::ofstream resStream(resultFile);
    if (!resStream.is_open())
    {
        std::cerr << "Error: cannot open file " << resultFile << std::endl;
    }
    else
    {
        resStream << match << " ";
        resStream.close();
    }
    std::cout << "CPU time: " << duration << " microseconds" << std::endl;
    return 0;
}