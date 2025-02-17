#include <iostream>
#include <cstdlib>
#include <string>
#include "prime_factors.cc"
#include "multiset.h"

// Sieve function and Prime_Multiset function should be copied from the code provided earlier

int main() {
    // Test number
    int number = 1431430;
    
    // Create the prime multiset for the given number
    Multiset<int> factors = Prime_Multiset(number);

    // Print all prime factors of the number
    std::cout << "Prime factors (all):" << std::endl;
    if (factors.Empty()) {
        std::cout << "No prime factors" << std::endl;
    } else {
        for (int i = factors.Min(); i <= factors.Max(); i++) {
            if (factors.Contains(i)) {
                std::cout << i << " (x" << factors.Count(i) << "), ";
            }
        }
        std::cout << std::endl;
    }

    // Print the minimum prime factor
    std::cout << "Minimum prime factor (min):" << std::endl;
    if (!factors.Empty()) {
        std::cout << factors.Min() << " (x" << factors.Count(factors.Min()) << ")" << std::endl;
    } else {
        std::cout << "No prime factors" << std::endl;
    }

    // Print the maximum prime factor
    std::cout << "Maximum prime factor (max):" << std::endl;
    if (!factors.Empty()) {
        std::cout << factors.Max() << " (x" << factors.Count(factors.Max()) << ")" << std::endl;
    } else {
        std::cout << "No prime factors" << std::endl;
    }

    // Test the 'near' functionality: find the closest prime to 10
    std::cout << "Prime factor nearest to 10 (near):" << std::endl;
    int target = 10;
    if (!factors.Empty()) {
        int result = factors.Floor(target);
        if (result != -1) {
            std::cout << result << " (x" << factors.Count(result) << ")" << std::endl;
        } else {
            std::cout << "No match" << std::endl;
        }
    } else {
        std::cout << "No match" << std::endl;
    }

    return 0;
}