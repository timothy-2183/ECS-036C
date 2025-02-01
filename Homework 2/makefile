postfix_eval:postfix_eval.cc stack.h
	g++ -Wall -Werror -std=c++11 postfix_eval.cc -o postfix_eval

test_deque:test_deque.cc deque.h
	g++ -Wall -Werror -o test_deque test_deque.cc -pthread -lgtest
clean:
	rm -f postfix_eval test_deque*.dat