run:
	./test_multisetmake

all:prime_factors test_multiset

prime_factors: prime_factors.cc
	g++ -Wall -Werror -std=c++11 -o prime_factors prime_factors.cc

test_multiset: test_multiset.cc multiset.h
	g++ -Wall -Werror -std=c++11 -o test_multiset test_multiset.cc -pthread -lgtest

test_all: test_primes.cc multiset.h prime_factors.cc	
	g++ -Wall -Werror -std=c++11 -o test_primes test_primes.cc -pthread -lgtest

clean:
	rm -f prime_factors test_multiset test_primes