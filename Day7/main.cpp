#include <set>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <unordered_map>

int fuel_consumption(int n)
{
	if (n == 1) return 1;
	else if (n == 0) return 0;
	return n + fuel_consumption(n - 1);
}

void read_data(std::unordered_map<int, int>& crabs_positions, std::set<int>& unique_crab_positions)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;
		while (std::getline(new_file, line)) {
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ',')) {
				crabs_positions[std::stoi(token)] += 1;
				unique_crab_positions.insert(std::stoi(token));
			}
		}
	}
}

void count_fuel(std::set<int>& unique_crab_positions, std::unordered_map<int, int>& crabs_positions, std::string part)
{
	int fuel_sum = INT_MAX;
	for (int i = 0; i < *--unique_crab_positions.end(); i++) {

		int unique_position_fuel_sum = 0;
		for (auto& [position, crabs_at_position] : crabs_positions) {
			if (part == "Part1") {
				unique_position_fuel_sum += std::abs(position - i) * crabs_at_position;
			} else if (part == "Part2") {
				unique_position_fuel_sum += fuel_consumption(std::abs(position - i)) * crabs_at_position;
			}
		}
		fuel_sum = unique_position_fuel_sum < fuel_sum ? unique_position_fuel_sum : fuel_sum;
	}

	std::cout << part << ": we need " << fuel_sum << " fuel. " << std::endl;
}

int main() {

	std::set<int> unique_crab_positions;
	std::unordered_map<int, int> crabs_positions;

	read_data(crabs_positions, unique_crab_positions);

	count_fuel(unique_crab_positions, crabs_positions, "Part1");
	count_fuel(unique_crab_positions, crabs_positions, "Part2");

	return 0;
}


