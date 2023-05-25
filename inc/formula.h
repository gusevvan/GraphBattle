#pragma once
#include <map>
#include <string>

namespace gm {
	class Formula {
	private:
		std::string _str;
		std::map< std::string, double > vars;
		std::string _error = "";
	public:

		void setStr(std::string& str);

		double number(std::string& str, unsigned& index);

		double identifier(std::string& str, unsigned& index);

		double function(std::string& name, std::string& str, unsigned& index);

		double base(std::string& str, unsigned& index);

		double expr(std::string& str, unsigned& index);

		double term(std::string& str, unsigned& index);

		double factor(std::string& str, unsigned& index);

		double calculate(double grX);

		std::string getError();
		
		void refreshError();
	};
}
