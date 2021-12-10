#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

void read_data(std::vector<std::vector<std::string>>& input)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;	
		while (std::getline(new_file, line)) {
			std::vector<std::string> transformed_line;
			std::istringstream iss(line);
			for (auto& sign : line) {
				std::string str {sign};
				transformed_line.push_back(str);
			}
			input.push_back(transformed_line);
		}
	}
}

int convertPoints(std::string illegal, std::string part) {
	int ret = 0;
	if (illegal == ")") { ret = part == "Part1" ? 3 : 1; }
	else if (illegal == "]") { ret = part == "Part1" ? 57 : 2; }
	else if (illegal == "}") { ret = part == "Part1" ? 1197 : 3; }
	else if (illegal == ">") { ret = part == "Part1" ? 25137 : 4; }

	return ret;
}

void reverseBrackets(std::string& current, std::string& corrected_r_string)
{
	std::string r_string(current.rbegin(), current.rend());
	for (auto& elem : r_string) {
		std::string val{ elem };
		if (val == "(") { val = ")"; }
		else if (val == "[") { val = "]"; }
		else if (val == "{") { val = "}"; }
		else if (val == "<") { val = ">"; }
		corrected_r_string += val;
	}
}

long long calculate_incomplete(std::string& current) 
{
	long long sum = 0;
	std::string corrected_r_string;

	reverseBrackets(current, corrected_r_string);

	for (auto& elem : corrected_r_string) {
		std::string srt_elem { elem };
		sum = (sum * 5) + convertPoints(srt_elem, {});
	}
	return sum;
}

void  findFirstIllegalChar(std::vector<std::vector<std::string>>& input) {
	int counter = 0;
	std::multiset<long long> calculated_inclomplete;
	int total_syntax_error = 0;
	for (auto& line : input) {
		bool corrupted = false;
		std::string current;
		for (auto& sign : line) {
			if (sign == "{" || sign == "[" || sign == "(" || sign == "<") {
			
				current += sign;
			} else {
				auto last = current.back();
				std::string last_str{ last };

				if (last_str == "{" && sign == "}" || last_str == "[" && sign == "]" || last_str == "(" && sign == ")" || last_str == "<" && sign == ">") {
					current.pop_back();
				} else {
					corrupted = true;
					total_syntax_error += convertPoints(sign, "Part1");
					break;
				}
			}
		}
		if (!corrupted) {
			calculated_inclomplete.insert(calculate_incomplete(current));
		}

		counter++;
	}
	std::cout << "Total syntax error score :" << total_syntax_error << std::endl;
	std::cout << "Middle score :" << *std::next(calculated_inclomplete.begin(), calculated_inclomplete.size()/2) << std::endl;
}

int main()
{
	std::vector<std::vector<std::string>> input;

	read_data(input);
	findFirstIllegalChar(input);

	return 0;
}
