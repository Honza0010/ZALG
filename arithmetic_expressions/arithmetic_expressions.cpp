#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cmath>




std::unordered_map<char, int> operators = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}, {'%', 2},
        {'~', 3},
        {'^', 4}, {'!', 4},
};


std::string infix_to_postfix(const std::string& infix)
{
    bool unary = true;
    std::string postfix;
    std::stack<char> operator_stack;

    for (char c : infix)
    {
        if (c == ' ')
        {
            continue;
        }

        if (std::isdigit(c)) 
        {
            postfix += c;
            unary = false;  //The digit was first in infix therefore the next operator cannot be unary
            continue;
        }

        if (operators.count(c))
        {
            if (unary && c == '-')
            {
                operator_stack.push('~');
            }
            else
            {
                while (!operator_stack.empty() && operator_stack.top() != '(' && operators[c] <= operators[operator_stack.top()]) 
                {
                    postfix += " ";
                    postfix += operator_stack.top();
                    operator_stack.pop();
                }
                postfix += " ";
                if (c == '!') {
                    postfix += "!";
                }
                else {
                    operator_stack.push(c);
                }
            }
        }
        else if (c == '(') 
        {
            operator_stack.push(c);
        }
        else if (c == ')') 
        {
            while (!operator_stack.empty() && operator_stack.top() != '(') 
            {
                postfix += " ";
                postfix += operator_stack.top();
                operator_stack.pop();
            }
            if (!operator_stack.empty() && operator_stack.top() == '(') 
            {
                operator_stack.pop();
            }
        }
        unary = true;
    }

    while (!operator_stack.empty()) 
    {
        postfix += " ";
        postfix += operator_stack.top();
        operator_stack.pop();
    }

    return postfix;
}



int evaluate(const std::string& postfix)
{
    std::stringstream pfix(postfix);
    std::vector<std::string> tokens;

    std::string help;

    while (pfix >> help)
    {
        tokens.push_back(help);
    }


    std::stack<int> stack;

    for (const auto& token : tokens)
    {
        if (std::isdigit(token[0]))
        {
            stack.push(std::stoi(token));
            continue;
        }


        int num_r = stack.top();
        stack.pop();

        if (token == "~")
        {
            stack.push(-num_r);
            continue;
        }
        else if (token == "!")
        {
            int faktorial = 1;
            while (num_r > 1)
            {
                faktorial *= num_r;
                num_r--;
            }
            stack.push(faktorial);
            continue;
        }

        int num_l = stack.top();
        stack.pop();

        if (token == "+")
        {
            stack.push(num_l + num_r);
        }
        else if (token == "-")
        {
            stack.push(num_l - num_r);
        }
        else if (token == "*")
        {
            stack.push(num_l * num_r);
        }
        else if (token == "/")
        {
            stack.push(num_l / num_r);
        }
        else if (token == "^")
        {
            stack.push(std::pow(num_l, num_r));
        }
        else if (token == "%")
        {
            stack.push(num_l % num_r);
        }

    }

    return stack.top();

}




int main() {
    std::string infix = "(5! + (- 3))/3";
    std::string postfix = infix_to_postfix(infix);

    std::cout << "Infix Expression: " << infix << std::endl;
    std::cout << "Postfix Expression: " << postfix << std::endl;

    std::cout << "infix = " << evaluate(postfix) << "\n";

    return 0;
}