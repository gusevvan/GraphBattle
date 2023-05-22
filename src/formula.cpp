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

    void Formula::setStr(std::string& str, double grX) {
        std::ostringstream strs;
        strs << grX / 20;
        std::string value = strs.str();
        std::string term;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == 'x') {
                term += value;
            }
            else {
                term += str[i];
            }
        }
        _str = term;
    }

    double Formula::number(unsigned& index)
    {
        double result = 0.0;
        char digit;
        double k = 10.0;

        while (index < _str.length())
        {
            digit = _str[index++];

            if (digit >= '0' && digit <= '9')
                result = result * 10.0 + (digit - '0');
            else
            {
                --index;
                break;
            }
        }

        if (index < _str.length())
            digit = _str[index++];

        if (digit == '.')
        {
            while (index < _str.length())
            {
                digit = _str[index++];

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

    double Formula::identifier(unsigned& index)
    {
        std::string name = "";
        double result;

        while (index < _str.length() &&
            ((_str[index] >= 'a' && _str[index] <= 'z') ||
                (_str[index] >= 'A' && _str[index] <= 'Z') ||
                (_str[index] >= '0' && _str[index] <= '9') ||
                (_str[index] == '_')))
            name += _str[index++];

        if (index < _str.length() && _str[index] == '(')
        {
            ++index;
            result = function(name, index);

            if (index >= _str.length() || _str[index] != ')')
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

    double Formula::function(std::string& name, unsigned& index)
    {
        double argument = expr(index);

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

    double Formula::base(unsigned& index)
    {
        double result;

        if (index >= _str.length())
        {
            std::cout << "Неожиданный конец строки" << std::endl;
            exit(-1);
        }

        if (_str[index] == '(')
        {
            ++index;
            result = expr(index);

            if (index >= _str.length() || _str[index] != ')')
            {
                std::cout << "Ожидается \")\" в позиции " << index + 2 << std::endl;
                exit(-1);
            }

            ++index;
        }
        else
        {
            if (_str[index] >= '0' && _str[index] <= '9')
                result = number(index);
            else
            {
                if ((_str[index] >= 'A' && _str[index] <= 'Z') ||
                    (_str[index] >= 'a' && _str[index] <= 'z') ||
                    (_str[index] == '_'))
                    result = identifier(index);
                else
                {
                    std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
                    exit(-1);
                }
            }
        }

        return result;
    }

    double Formula::expr(unsigned& index)
    {
        double result;
        char operation;

        result = term(index);

        while (index < _str.length() &&
            (_str[index] == '+' || _str[index] == '-'))
        {
            operation = _str[index];
            ++index;

            switch (operation)
            {
            case '+':
                result += term(index);
                break;
            case '-':
                result -= term(index);
                break;
            }
        }

        return result;
    }

    double Formula::term(unsigned& index)
    {
        double result;
        char operation;
        double div;

        result = factor(index);

        while (index < _str.length() &&
            (_str[index] == '*' || _str[index] == '/'))
        {
            operation = _str[index];
            ++index;

            switch (operation)
            {
            case '*':
                result *= factor(index);
                break;
            case '/':
                div = factor(index);

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

    double Formula::factor(unsigned& index)
    {
        double result;

        if (index >= _str.length())
        {
            std::cout << "Неожиданный конец строки" << std::endl;
            exit(-1);
        }

        switch (_str[index])
        {
        case '+':
            ++index;
            result = factor(index);
            break;
        case '-':
            ++index;
            result = -factor(index);
            break;
        default:
            result = base(index);

            if (index <= _str.length() - 1 && _str[index] == '^')
            {
                ++index;
                result = pow(result, factor(index));
            }
        }

        return result;
    }

    double Formula::calculate()
    {
        unsigned index = 0;
        double result = expr(index);

        if (index < _str.length() - 1)
        {
            std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
            exit(-1);
        }

        return result;
    }
    
}
