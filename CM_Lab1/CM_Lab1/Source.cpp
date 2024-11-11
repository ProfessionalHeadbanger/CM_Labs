// 10. "........\123...\321...\..."..."
// —трокова€ константа, содержаща€ восьмеричные константы и кавычки

#include <iostream>
#include <fstream>
#include <string>

enum State 
{
	S0, // начальное состо€ние
	S1, // переход по открывающим кавычкам
	S2, // переход по цифрам 0, 1, 2, 3, 4, 5, 6, 7
	S3, // переход по закрывающим кавычкам к конечному состо€нию
	ERROR // ошибка
};

State transition(State currentState, char symbol)
{
	switch (currentState)
	{
	case S0:
		if (symbol == '"')
		{
			std::cout << "S0 -> S1\n";
			return S1;
		}
		std::cout << "Error in S0\n";
		return ERROR;
	case S1:
		if (symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7')
		{
			std::cout << "S1 -> S2\n";
			return S2;
		}
		std::cout << "Error in S1\n";
		return ERROR;
	case S2:
		if (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7')
		{
			std::cout << "S2 -> S2\n";
			return S2;
		}
		if (symbol == '"')
		{
			std::cout << "S2 -> S3\n";
			return S3;
		}
		std::cout << "Error in S2\n";
		return ERROR;
	case S3:
		if (symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7')
		{
			std::cout << "S3 -> S2\n";
			return S2;
		}
		std::cout << "Error in S3\n";
		return ERROR;
	default:
		std::cout << "Unexpected error\n";
		return ERROR;
	}
}

bool isValidString(const std::string& line)
{
	State currentState = S0; // Ќачальное состо€ние
	for (char symbol : line)
	{
		currentState = transition(currentState, symbol);
		if (currentState == ERROR)
		{
			return false;
		}
	}
	return currentState == S3; //  онечное состо€ние
}

int main()
{
	std::ifstream test_file("tests.txt");
	std::string line;
	
	while (std::getline(test_file, line))
	{
		if (isValidString(line))
		{
			std::cout << "Line " << line << " is valid\n\n";
		}
		else
		{
			std::cout << "Line " << line << " is invalid\n\n";
		}
	}
	test_file.close();
}