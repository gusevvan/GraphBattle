#pragma once
#include <map>
#include <string>

namespace fr {

	double number(std::string& str, unsigned& index);

	double identifier(std::string& str, unsigned& index);

	double function(std::string& name, std::string& str, unsigned& index);

	double base(std::string& str, unsigned& index);

	double expr(std::string& str, unsigned& index);
	double term(std::string& str, unsigned& index);
	double factor(std::string& str, unsigned& index);

	double calculate(std::string& str);
}
