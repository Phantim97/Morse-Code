#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <map>
#include <regex>

class InvalidInputException
{
public:
	void getErrorMessage() { std::cout << "Invalid input try again...\n"; }
};

const std::map<char, std::string> g_MorseCodec
{
{'a',". ---   "},{'b',"--- .   "}, {'c', "--- .  --- .   "}, {'d', "--- . .   "}, {'e', ".   "},
{'f',". . --- .   "}, {'g',"--- --- .   "},{'h',". . . .   "},{'i',". .   "},{'j',". --- --- ---   "},{'k',"--- . ---   "},{'l',". --- . .   "},{'m',"--- ---   "},
{'n',"--- .   "},{'o',"--- --- ---   "},{'p',". --- --- .   "},{'q',"--- --- . ---   "},{'r',". --- .   "},{'s',". . .   "}, {'t',"---   "},{'u',". . ---   "},
{'v',". . . ---   "},{'w',". --- ---   "},{'x',"--- . . ---   "},{'y',"--- . --- ---   "},{'z',"--- --- . .   "},{'1',". --- --- --- ---   "},
{'2',". . --- --- ---   "},{'3',". . . --- ---   "},{'4',". . . . ---   "},{'5',". . . . .   "},{'6',"--- . . . .   "},{'7',"--- --- . . .    "},
{'8',"--- --- --- . .   "},{'9',"--- --- --- --- ."},{'0',"--- --- --- --- ---   "},{' ',"       "}
};

bool isValidMorse(std::string s)
{
	bool bValidMorse = true;

	// Valid chars present (Works)
	std::regex charcheck("[[:s:]\.-]*");
	if (!std::regex_match(s, charcheck))
	{
		bValidMorse = false;
	}

	// One (.)
	std::regex dotcheck("(\.\.)*");
	if (std::regex_match(s, dotcheck))
	{
		bValidMorse = false;
	}

	// Three (---)
	std::regex linecheck("(---.)*");
	if (std::regex_match(s, linecheck))
	{
		bValidMorse = false;
	}

	// Check Spacing (1 or 3 or 7 only all else fails)

	std::regex spacing("([:s:]{8,})*|([:s:]{5})+|([:s:]{2})+");

	if (std::regex_search(s, spacing))
	{
		bValidMorse = false;
	}

	return bValidMorse;
}

// parse the sentence and tokenize words
std::string getword(std::string s)
{
	std::regex word("([:space:]{7})");
	std::string transword;
	// parse into words
	// tokenize letters
	std::regex letter("([:space:]{7})");
	// convert morse letters to characters
	// combine characters to a string

	return transword;
}

char morseToChar(std::string s)
{

	for (std::map<char, std::string>::const_iterator it = g_MorseCodec.begin(); it != g_MorseCodec.end(); it++)
	{
		if (it->second == s)
		{
			return it->first;
		}
		else
		{
			return ' ';
		}
	}
}

std::string charToMorse(char c)
{
	auto search = g_MorseCodec.find(c); //comparator too long of data type
	if (search != g_MorseCodec.end())
	{
		return search->second;
	}
	else
	{
		return "";
	}
}

int main()
{
	std::string msg;
	std::string translMsg = "";
	std::cout << "Enter an option here 1.) Word -> Morse | 2.) Morse -> Word: ";
	int choice = 0;
	do
	{
		try
		{
			std::cin >> choice;
			if (std::cin.fail())
			{
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException e)
		{
			e.getErrorMessage();
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
	} while (choice != 1 && choice != 2);
	std::cin.ignore(INT_MAX, '\n');

	if (choice == 1)
	{
		std::cout << "Enter your message here: ";

		std::getline(std::cin, msg);

		// format to lowercase
		std::locale loc;
		for (std::string::size_type i = 0; i < msg.length(); i++)
		{
			msg[i] = std::tolower(msg[i], loc);
		}

		std::cout << "Formatted message: " << msg << '\n';
		std::cout << "Your Message: " << msg << '\n';
		for (int i = 0; i < msg.size(); i++)
		{
			translMsg.append(charToMorse(msg[i]));
		}
		std::cout << "Morse Code: " << translMsg << '\n';
	}
	else
	{
		std::cout << "Enter your message here: ";
		std::getline(std::cin, msg);

		if (isValidMorse(msg))
		{
			std::cout << "Valid Morse Code Format\n";
		}
		else
		{
			std::cout << "Invalid Morse Code\n";
		}
	}
	system("pause");
	return 0;
}