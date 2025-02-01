#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include "stack.h" 

bool IsOperator(const std::string &token);

double EvaluatePostfix(const std::string &expression, bool &is_valid);


void ProcessInput();

/*
Approach:
    - Takes the entire line, turns it into the string from the cin
    - basically takes in cin while there is cin, waits on response
    - each response seperated by an endl
    - ending input stream means the program ends immedeately\
    - also don't forget to print bye
*/ 
int main()
{
    std::string line;
    bool is_valid = true;
    while (std::getline(std::cin, line)){
        double result = EvaluatePostfix(line, is_valid);
        if (is_valid)
        {
            std::cout << result << std::endl;
        }
    }
    std::cout << "Bye!"; 
    return 0;
}

bool IsOperator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double EvaluatePostfix(const std::string &expression, bool &is_valid)
{
    std::istringstream iss(expression);
    std::string token;
    Stack<double> my_stack; 
    is_valid = true;

    while (iss >> token)
    {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1))
        {
            my_stack.Push(std::stod(token));
        }
        else if (IsOperator(token))
        {
            if (my_stack.Size() < 2)
            {
                std::cerr << "Error: invalid expression" << std::endl;
                is_valid = false;
                return 0;
            }
            double b = my_stack.Top();
            my_stack.Pop();
            double a = my_stack.Top();
            my_stack.Pop();

            if (token == "+")
            {
                my_stack.Push(a + b);
            }
            else if (token == "-")
            {
                my_stack.Push(a - b);
            }
            else if (token == "*")
            {
                my_stack.Push(a * b);
            }
            else if (token == "/")
            {
                if (b == 0)
                {
                    std::cerr << "Error: division by zero" << std::endl;
                    is_valid = false;
                    return 0;
                }
                my_stack.Push(a / b);
            }
        }
        else
        {
            std::cerr << "Error: unknown symbol '" << token << "'" << std::endl;
            is_valid = false;
            return 0;
        }
    }

    if (my_stack.Size() != 1)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        is_valid = false;
        return 0;
    }
    return my_stack.Top();
}


