#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "multiset.h"

// Function to return a multiset filled with prime factors of a number

//Uses an algorithm for finding a primes up to number N, Sieve of Eratosthenes
std::vector<int> sieve(int N) {
    if (N < 2) return {};  

    std::vector<bool> is_prime(N + 1, true); 
    std::vector<int> primes;

    is_prime[0] = is_prime[1] = false; 

    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Collect all prime numbers
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}


Multiset<int> Prime_Multiset(const int n){
    auto my_set = Multiset<int>();
    auto primes_vector = sieve(n);
    int temp = 0;
    for (auto i :primes_vector)
    {
        temp = i;
        while (n%temp==0)
        {
            my_set.Insert(i);   
            temp = temp*i;
        }
    }
    if (my_set.Contains(n)) my_set.Remove(n) ;
    return my_set;
}

bool parse_int(const std::string& str, int& number) {
    char* end;
    long val = std::strtol(str.c_str(), &end, 10);
    if (*end != '\0' || val <= 0) return false;
    number = static_cast<int>(val);
    return true;
}

// Main Function
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] <<" <number> <command> [<args>]" << std::endl;
        return 1;
    }

    int number = 0;
    if (!parse_int(argv[1], number)) {
        std::cerr << "Invalid number" << std::endl;
        return 1;
    }

    Multiset<int> factors = Prime_Multiset(number);
    std::string command = argv[2];

    if (command == "all") {
        if (factors.Empty()) {
            std::cout << "No prime factors" << std::endl;
        } else {
            for (int i = factors.Min(); i <= factors.Max(); i++) {
                if (factors.Contains(i)) {
                    std::cout << i << " (x" << factors.Count(i) << "),";
                }
            }
            std::cout << std::endl;
        }
    } 
    else if (command == "min") {
        if (!factors.Empty()) {
            std::cout << factors.Min() << " (x" << factors.Count(factors.Min()) << ")" << std::endl;
        } else {
            std::cout << "No prime factors" << std::endl;
        }
    } 
    else if (command == "max") {
        if (!factors.Empty()) {
            std::cout << factors.Max() << " (x" << factors.Count(factors.Max()) << ")" << std::endl;
        } else {
            std::cout << "No prime factors" << std::endl;
        }
    } 
    else if (command == "near") {
        if (argc < 4) {
            std::cerr << "Command 'near' expects another argument: [+/-]prime" << std::endl;
            return 1;
        }

        std::string near_arg = argv[3];
        bool greater = near_arg[0] == '+';
        bool lesser = near_arg[0] == '-';
        int target;

        if ((greater || lesser) && parse_int(near_arg.substr(1), target)) {
            if (!factors.Empty()) {
                int result = greater ? factors.Ceil(target) : factors.Floor(target);
                std::cout << result << " (x" << factors.Count(result) << ")" << std::endl;
            } else {
                std::cout << "No match" << std::endl;
            }
        } 
        else if (parse_int(near_arg, target)) {
            if (!factors.Empty() && factors.Contains(target)) {
                std::cout << target << " (x" << factors.Count(target) << ")" << std::endl;
            } else {
                std::cout << "No match" << std::endl;
            }
        } 
        else {
            std::cerr << "Invalid prime" << std::endl;
            return 1;
        }
    } 
    else {
        std::cerr << "Command '" << command << "' is invalid\n";
        std::cerr << "Possible commands are: all|min|max|near" << std::endl;
        return 1;
    }
}