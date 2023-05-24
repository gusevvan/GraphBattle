#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <formula.h>
#include <field.h>

namespace gm {

    /*

    <цифра> ::= '0' | ... | '9' |
    <буква> ::= 'a' ... 'z' | 'A' ... 'Z' | '_'

    <число> ::= <цифра> {<цифра>} [ '.' <цифра> {<цифра>} ]

    <операция_+_-> ::= '+' | '-'
    <операция_*_/> ::= '*' | '/'
    <унарный_+_->  ::= '+' | '-'

    <идентификатор> ::= <буква> { <буква> | <цифра> }

    <переменная> ::= <идентификатор>
    <функция>    ::= <идентификатор> '(' <выражение> ')'

    <основание> ::= <переменная> | <функция> | <число> | ( '(' <выражение> ')' )

    <выражение> ::= <слагаемое> [ <операция_+_-> <слагаемое>]
    <слагаемое> ::= <множитель> [ <операция_*_/> <множитель>]
    <множитель> ::= [ <унарный_+_-> ] <множитель> | <основание> [ '^' <множитель> ]

    */

    std::string Formula::getError()
    {
        return _error;
    }
    void Formula::setStr(std::string& str) {
        _str = str;
    }

    double Formula::number(std::string& str, unsigned& index)
    {
        double result = 0.0;
        char digit;
        double k = 10.0;

        while (index < str.length())
        {
            digit = str[index++];

            if (digit >= '0' && digit <= '9')
                result = result * 10.0 + (digit - '0');
            else
            {
                --index;
                break;
            }
        }

        if (index < str.length())
            digit = str[index++];

        if (digit == '.')
        {
            while (index < str.length())
            {
                digit = str[index++];

                if (digit >= '0' && digit <= '9')
                {
                    result += (digit - '0') / k;
                    k *= 10.0;
                }
                else
                {
                    --index;
                    break;
                }
            }
        }
        else
            --index;

        return result;
    }

    double Formula::identifier(std::string& str, unsigned& index)
    {
        std::string name = "";
        double result;

        while (index < str.length() &&
            ((str[index] >= 'a' && str[index] <= 'z') ||
                (str[index] >= 'A' && str[index] <= 'Z') ||
                (str[index] >= '0' && str[index] <= '9') ||
                (str[index] == '_')))
            name += str[index++];

        try
        {
            if (index < str.length() && str[index] == '(')
            {
                ++index;
                result = function(name, str, index);

                if (index >= str.length() || str[index] != ')')
                {
                    throw "Waiting for \")\" in position ";
                }

                ++index;
            }
            else
            {
                double var;

                throw "Input the value of variable: : ";
                /*std::cin >> var;

                vars.insert(std::pair< const std::string, double >(name, var));

                result = vars[name];*/
            }
        }
        
        catch (const char* error) {
            _error = error;
            std::cerr << error << std::endl;
            return 0.0;
        }
        return result;
    }

    double Formula::function(std::string& name, std::string& str, unsigned& index)
    {
       try
       {
           double argument = expr(str, index);

           if (strcmp(name.c_str(), "abs") == 0)
               return abs(argument);

           if (strcmp(name.c_str(), "acos") == 0)
               return acos(argument);

           if (strcmp(name.c_str(), "asin") == 0)
               return asin(argument);

           if (strcmp(name.c_str(), "atan") == 0)
               return atan(argument);

           if (strcmp(name.c_str(), "cos") == 0)
               return cos(argument);

           if (strcmp(name.c_str(), "cosh") == 0)
               return cosh(argument);

           if (strcmp(name.c_str(), "exp") == 0)
               return exp(argument);

           if (strcmp(name.c_str(), "log") == 0)
               return log(argument);

           if (strcmp(name.c_str(), "log10") == 0)
               return log10(argument);

           if (strcmp(name.c_str(), "sin") == 0)
               return sin(argument);

           if (strcmp(name.c_str(), "sinh") == 0)
               return sinh(argument);

           if (strcmp(name.c_str(), "sqrt") == 0)
               return sqrt(argument);

           if (strcmp(name.c_str(), "tan") == 0)
               return tan(argument);

           if (strcmp(name.c_str(), "tanh") == 0)
               return tanh(argument);

           throw "Unknown function";

       }
        
       catch (const char* error) {
           _error = error;
           std::cerr << error << std::endl;
       }
    }

    double Formula::base(std::string& str, unsigned& index)
    {
        try
        {
            double result;

            if (index >= str.length())
            {
                throw"Unexpected end of line";
            }

            if (str[index] == '(')
            {
                ++index;
                result = expr(str, index);

                if (index >= str.length() || str[index] != ')')
                {
                    throw"Waiting for \")\" in position ";
                
                }

                ++index;
            }
            else
            {
                if (str[index] >= '0' && str[index] <= '9')
                    result = number(str, index);
                else
                {
                    if ((str[index] >= 'A' && str[index] <= 'Z') ||
                        (str[index] >= 'a' && str[index] <= 'z') ||
                        (str[index] == '_'))
                        result = identifier(str, index);
                    else
                    {
                        throw"Incorrect character in positon ";
                    }
                }
            }
            return result;
        }
        catch (const char* error) {
            _error = error;
            std::cerr << error << std::endl;
        }
        try
        {
            double result;

            if (index >= str.length())
            {
                throw"Unexpected end of line";
            }

            if (str[index] == '(')
            {
                ++index;
                result = expr(str, index);

                if (index >= str.length() || str[index] != ')')
                {
                    throw"Waiting for \")\" in position ";
                }

                ++index;
            }
            else
            {
                if (str[index] >= '0' && str[index] <= '9')
                    result = number(str, index);
                else
                {
                    if ((str[index] >= 'A' && str[index] <= 'Z') ||
                        (str[index] >= 'a' && str[index] <= 'z') ||
                        (str[index] == '_'))
                        result = identifier(str, index);
                    else
                    {
                        throw"Incorrect character in positon ";
                    }
                }
            }
            return result;
        }
        catch (const char* error) {
            _error = error;
            std::cerr << error << std::endl;
        }
    }

    double Formula::expr(std::string& str, unsigned& index)
    {
        double result;
        char operation;

        result = term(str, index);

        while (index < str.length() &&
            (str[index] == '+' || str[index] == '-'))
        {
            operation = str[index];
            ++index;

            switch (operation)
            {
            case '+':
                result += term(str, index);
                break;
            case '-':
                result -= term(str, index);
                break;
            }
        }

        return result;
    }

    double Formula::term(std::string& str, unsigned& index)
    {
        double result;
        char operation;
        double div;

        result = factor(str, index);

        while (index < str.length() &&
            (str[index] == '*' || str[index] == '/'))
        {
            operation = str[index];
            ++index;
            try
            {
                switch (operation)
                {
                case '*':
                    result *= factor(str, index);
                    break;
                case '/':
                    div = factor(str, index);

                    if (div == 0.0)
                    {
                        throw"Division by zero!";
                    }

                    result /= div;
                    break;
                }
            }
            catch (const char* error) {
                _error = error;
                std::cerr << error << std::endl;

            }
        }
        return result;
    }

    double Formula::factor(std::string& str, unsigned& index)
    {
        double result;
        try
        {
            if (index >= str.length())
            {
                throw"Unexpected end of line";
            }

            switch (str[index])
            {
            case '+':
                ++index;
                result = factor(str, index);
                break;
            case '-':
                ++index;
                result = -factor(str, index);
                break;
            default:
                result = base(str, index);

                if (index <= str.length() - 1 && str[index] == '^')
                {
                    ++index;
                    result = pow(result, factor(str, index));
                }
            }

            return result;
        }
        catch (const char* error) {
            _error = error;
            std::cerr << error << std::endl;

        }
    }

    double Formula::calculate(double grX)
    {
        try
        {
            std::ostringstream strs;
            strs << grX / 80;
            std::string value = strs.str();
            std::string term;
            for (int i = 0; i < _str.size(); ++i) {
                if (_str[i] == 'x') {
                    term += value;
                }
                else {
                    term += _str[i];
                }
            }
            unsigned index = 0;
            double result = expr(term, index);

            if (index < term.length() - 1)
            {
                throw"Incorrect character in positon ";
            }

            return result;
        }
        catch (const char* error) {
            _error = error;
            std::cerr << error << std::endl;

        }
    }
    
}
