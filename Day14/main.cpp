#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <unordered_map>

void read_data(std::unordered_map<std::string, std::string>& input, std::string &polymer_template, std::set<std::string>& unique)
{
	int counter{0};

	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;
		while (std::getline(new_file, line)) {
			if (counter++ == 0) { polymer_template = line; continue; }
			std::vector<std::string> transformed_line;
			
			if (line.find("->") != std::string::npos) {
				std::istringstream iss(line.replace(2, 4, ","));
				std::string token;
				while (std::getline(iss, token, ',')) {
					transformed_line.push_back(token);
				}
				
				std::string str1{*(transformed_line[0].data())};
				std::string str2{*(transformed_line[0].data()+1)};

				unique.insert(str1);
				unique.insert(str2);
				unique.insert(transformed_line[1]);

				input.insert(std::make_pair(transformed_line[0], transformed_line[1]));
			}
		}
	}
}

void countPolymer(std::unordered_map<std::string, std::string>& input, std::unordered_map<std::string, long long>& char_occurrence, std::unordered_map<std::string, long long> clean_char_occurrence, int step)
{
	if (step == 0) return;
	
	auto clean_char_occurrence_copy = clean_char_occurrence;
	for (auto& [key, value] : char_occurrence) {
		if (value != 0) {
			clean_char_occurrence[key[0] + input[key]] += value;
			clean_char_occurrence[input[key] + key[1]] += value;
		}
	}
	char_occurrence = clean_char_occurrence;

	countPolymer( input, char_occurrence, clean_char_occurrence_copy, --step);
}

void createUniquePairs(std::set<std::string>& unique, std::unordered_map<std::string, long long>& char_occurrence, std::unordered_map<std::string, long long>& clean_char_occurrence)
{
	for (int i = 0; i < unique.size(); i++) {
		for (int j = 0; j < unique.size(); j++) {
			clean_char_occurrence[*next(unique.begin(), i) + *next(unique.begin(), j)] = 0;
		}
	}
	char_occurrence = clean_char_occurrence;
}

void insertStartPairs(std::string& polymer_template, std::unordered_map<std::string, long long>& char_occurrence)
{
	for (int i = 1; i < polymer_template.size(); i++) {
		std::string first{ polymer_template[i - 1] };
		std::string second{ polymer_template[i] };
		char_occurrence[first + second] += 1;
	}
}

void countLetterExistance(std::unordered_map<std::string, long long>& char_occurrence, std::unordered_map<std::string, long long>& sum, std::string& polymer_template)
{
	for (auto& [key, val] : char_occurrence) {
		std::string first{ key[0] };
		std::string second{ key[1] };
		sum[first] += val;
		sum[second] += val;
	}
	std::string first{ *(polymer_template.data()) };
	std::string second{ *(polymer_template.data() + polymer_template.size() - 1) };

	sum[first] += 1;
	sum[second] += 1;
}

void countMinMax(std::unordered_map<std::string, long long>& sum, long long& max, long long& min)
{
	for (auto [key, value] : sum) {
		max = max < value ? value : max;
		min = min > value ? value : min;
	}
}

void showOutputMessage(long long max, long long min, std::string& part)
{
	std::cout << part << "output: " << max / 2 - min / 2 << " "<< std::endl;
}

void calculateOutput(std::unordered_map<std::string, long long>& char_occurrence, std::string& polymer_template, std::string& part)
{
	long long max{ 0 }, min{ LLONG_MAX };
	std::unordered_map<std::string, long long>  sum;
	
	countLetterExistance(char_occurrence, sum, polymer_template);
	countMinMax(sum, max, min);
	showOutputMessage(max, min, part);
}

void calculatePart1(std::unordered_map<std::string, std::string>& input, std::unordered_map<std::string, long long> char_occurrence, std::unordered_map<std::string, long long>& clean_char_occurrence, std::string& polymer_template, int step, std::string part)
{
	countPolymer(input, char_occurrence, clean_char_occurrence, step);
	calculateOutput(char_occurrence, polymer_template, part);
}

void calculatePart2(std::unordered_map<std::string, std::string>& input, std::unordered_map<std::string, long long> char_occurrence, std::unordered_map<std::string, long long>& clean_char_occurrence, std::string& polymer_template, int step, std::string part)
{
	countPolymer(input, char_occurrence, clean_char_occurrence, step);
	calculateOutput(char_occurrence, polymer_template, part);
}

int main()
{
	std::set<std::string> unique;
	std::string polymer_template;
	std::unordered_map<std::string, std::string>  input;
	std::unordered_map<std::string, long long>  clean_char_occurrence, char_occurrence;
	
	read_data(input, polymer_template, unique);
	createUniquePairs(unique, char_occurrence, clean_char_occurrence);
	insertStartPairs(polymer_template, char_occurrence);
	calculatePart1(input, char_occurrence, clean_char_occurrence, polymer_template, 10, "Part1 ");
	calculatePart2(input, char_occurrence, clean_char_occurrence, polymer_template, 40, "Part2 ");

	return 0;
}
