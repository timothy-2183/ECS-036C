test_multiset: test_multiset.cc multiset.h
	g++ -Wall -Werror -std=c++11 -o test_multiset test_multiset.cc

prime_factors: prime_factors.o multiset.h
	g++ -Wall -Werror -std=c++11 prime_factors.o -o prime_factors 

prime_factors.o: prime_factors.cc multiset.h
	g++ -Wall -Werror -std=c++11 -c prime_factors.cc

clean:
	rm -f test_multiset prime_factors *.o
