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

        if (index < str.length() && str[index] == '(')
        {
            ++index;
            result = function(name, str, index);

            if (index >= str.length() || str[index] != ')')
            {
                std::cout << "Ожидается \")\" в позиции " << index + 2 << std::endl;
                exit(-1);
            }

            ++index;
        }
        else
        {
            double var;

            std::cout << "Введите значение переменной " << name << ": ";
            std::cin >> var;

            vars.insert(std::pair< const std::string, double >(name, var));

            result = vars[name];
        }

        return result;
    }

    double Formula::function(std::string& name, std::string& str, unsigned& index)
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

        std::cout << "Неизвестная функция" << std::endl;
        exit(-1);
    }

    double Formula::base(std::string& str, unsigned& index)
    {
        double result;

        if (index >= str.length())
        {
            std::cout << "Неожиданный конец строки" << std::endl;
            exit(-1);
        }

        if (str[index] == '(')
        {
            ++index;
            result = expr(str, index);

            if (index >= str.length() || str[index] != ')')
            {
                std::cout << "Ожидается \")\" в позиции " << index + 2 << std::endl;
                exit(-1);
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
                    std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
                    exit(-1);
                }
            }
        }

        return result;
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

            switch (operation)
            {
            case '*':
                result *= factor(str, index);
                break;
            case '/':
                div = factor(str, index);

                if (div == 0.0)
                {
                    std::cout << "Деление на нуль!" << std::endl;
                    exit(-1);
                }

                result /= div;
                break;
            }
        }

        return result;
    }

    double Formula::factor(std::string& str, unsigned& index)
    {
        double result;

        if (index >= str.length())
        {
            std::cout << "Неожиданный конец строки" << std::endl;
            exit(-1);
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

    double Formula::calculate(double grX)
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
            std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
            exit(-1);
        }

        return result;
    }
    
}
