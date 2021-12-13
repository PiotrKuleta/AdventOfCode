#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

void read_data(std::vector<std::vector<int>>& input, std::vector<std::pair<char, int>>& fold)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;	
		while (std::getline(new_file, line)) {
			std::vector<int> transformed_line;
			if (line.find(",") != std::string::npos) {
				std::istringstream iss(line);
				std::string token;
				while (std::getline(iss, token, ',')) {
					transformed_line.push_back(std::stoi(token));
				}
				input.push_back(transformed_line);
			} else if(line != "") {
				auto substr_line = line.substr(11, line.size());
				fold.push_back(std::make_pair(substr_line[0], std::stoi(substr_line.substr(2)))); 
			}
		}
	}
}

void createAndFillTable(std::vector<std::vector<int>>& input, std::vector<std::vector<std::string>>& table)
{
	int x = 0, y = 0;
	// find values to create table 
	for (int i = 0; i < input.size(); i++) {
		x = x < input[i][1] ? input[i][1] : x;
		y = y < input[i][0] ? input[i][0] : y;
	}

	// create blank table
	for (int i = 0; i <= x; i++) {
		std::vector<std::string> clean_line(y + 1, ".");
		table.push_back(clean_line);
	}

	// fill with #
	for (int i = 0; i < input.size(); i++) {
		int y = input[i][0], x = input[i][1];
		table[x][y] = "#";
	}
}

void getResult(std::vector<std::vector<std::string>>& table, std::string str, int& limit_x, int& limit_y)
{
	int sum = 0;
	for (int i = 0; i < limit_y; i++) {
		for (int j = 0; j < limit_x; j++) {
			if (str == "Part1") {
				if (table[i][j] == "#") sum += 1;
			} else if (str == "Part2") {
				std::cout << table[i][j] << " ";
			}
		}
		if (str == "Part2") std::cout << "\n";
	}
	if (str == "Part1") std::cout << str << " answer: " << sum << "\n";
}

void foldBy_Y(std::vector<std::vector<std::string>>& table, int& num_line, int& limit_x, int& limit_y)
{
	int iter = limit_y;
	for (int i = 0; i < num_line; i++) {
		for (int j = 0; j < limit_x; j++) {
			if (table[i][j] == "#" || table[iter - 1][j] == "#") {
				table[i][j] = "#";
			}
		}
		iter--;
	}
	limit_y = num_line;
}

void foldBy_X(std::vector<std::vector<std::string>>& table, int& num_line, int& limit_x, int& limit_y)
{
	int iter = limit_x;
	for (int i = 0; i < limit_y; i++) {
		int it = iter;
		for (int j = 0; j < num_line; j++) {
			if (table[i][j] == "#" || table[i][it - 1] == "#") {
				table[i][j] = "#";
			}
			it--;
		}
	}
	limit_x = num_line;
}

void foldAndReturnAnswer(std::vector<std::pair<char, int>>& fold, std::vector<std::vector<std::string>>& table)
{
	int counter = 0, limit_x = table[0].size(), limit_y = table.size();
	for (auto& [axis, num_line] : fold) {
		if (axis == 'y') {
			foldBy_Y(table, num_line, limit_x, limit_y);
		} else if (axis == 'x') {
			foldBy_X(table, num_line, limit_x, limit_y);
		}
		if (counter++ == 0) getResult(table, "Part1", limit_x, limit_y);
	}
	getResult(table, "Part2", limit_x, limit_y);
}

int main()
{
	std::vector<std::vector<int>> input;
	std::vector<std::pair<char, int>> fold;
	std::vector<std::vector<std::string>> table;
	
	read_data(input, fold);
	createAndFillTable(input, table);
	foldAndReturnAnswer(fold, table);

	return 0;
}

