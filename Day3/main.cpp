#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

void part_one( int& line_size,  std::vector<std::string>& start_vec)
{
	int counter = 0;
	std::string gamma_rate, epsilon_rate;
	std::unordered_map<int, int> un_map;

	std::fstream new_file;
	new_file.open("input", std::ios::in);

	if (new_file.is_open()) {

		int val = 0;

		std::string line;
		while (std::getline(new_file, line)) {

			if (counter == 0) {
				line_size = line.size();
			}

			for (int i = 0; i < line_size; i++) {
				val = line[i] - 48;
				if (counter == 0) {
					un_map.insert(std::make_pair(i, val));
				} else {
					un_map[i] += val;
				}
			}

			start_vec.push_back(line);
			counter++;
		}
	}

	for (int i = 0; i < line_size; i++) {
		bool leading_one_condition = un_map[i] > (counter / 2);
		gamma_rate += leading_one_condition ? "1" : "0";
		epsilon_rate += !leading_one_condition ? "1" : "0";
	}

	std::cout << "Submarine power consumption: " << std::stoi(gamma_rate, 0, 2) * std::stoi(epsilon_rate, 0, 2) << std::endl;
}


int check_life_support(std::vector<std::string>& start_vec, int line_size, std::string rating)
{
	std::vector<std::string> prev_vec;
	std::vector<std::string> looped_vec = start_vec;

	for (int i = 0; i < line_size; i++) {
		double  counter = 0, sum = 0;
		for (auto& elem : looped_vec) {

			if (elem[i] - 48 == 1) {
				sum++;
			}
			counter++;
		}

		for (auto& elem : looped_vec) {
			if (looped_vec.size() == 1) {
				return std::stoi(looped_vec[0], 0, 2);
			}

			bool condition = rating == "oxygen" ? (sum / counter) * 100 >= 50 : (sum / counter) * 100 < 50;
			int leading_value = condition ? 1 : 0;
			if (elem[i] - 48 == leading_value) prev_vec.push_back(elem);
		}

		looped_vec = prev_vec;
		prev_vec.clear();
	}

	return std::stoi(looped_vec[0], 0, 2);
}

void part_two(std::vector<std::string>& start_vec, int line_size)
{
	int oxygen_generator = check_life_support(start_vec, line_size, "oxygen");
	int CO2_scrubber = check_life_support(start_vec, line_size, "scrubber");

	std::cout << "Life support rating of the submarine: " << oxygen_generator * CO2_scrubber << std::endl;
}


int main() {

	int line_size = 0;
	std::vector<std::string> start_vec;

	part_one(line_size, start_vec);
	part_two(start_vec, line_size);

	return 0;
}
