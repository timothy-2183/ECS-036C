prime_factors:prime_factors.cc multiset.h
	g++ -Wall -Werror -std=c++11 prime_factors.cc -o prime_factors

test_multiset:test_multiset.cc multiset.h
	g++ -Wall -Werror -o test_multiset test_multiset.cc -pthread -lgtest
clean:
	rm -f prime_factors test_multiset*.dat