#pragma once
#include <map>
#include <string>

namespace gm {
	class Formula {
	private:
		std::string _str;
		std::map< std::string, double > vars;
	public:

		void setStr(std::string& str, double grX);

		double number(unsigned& index);

		double identifier(unsigned& index);

		double function(std::string& name, unsigned& index);

		double base(unsigned& index);

		double expr(unsigned& index);

		double term(unsigned& index);

		double factor(unsigned& index);

		double calculate();
	};
}
