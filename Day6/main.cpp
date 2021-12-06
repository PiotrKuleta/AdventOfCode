#include <map>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <algorithm>

void read_data(std::map<int, long long>& fish_map)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;
		while (std::getline(new_file, line)) {
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ',')) {
				fish_map[std::stoi(token)] += 1;
			}
		}
	}
}

void birth_action(std::map<int, long long>& fish_map_copy, int time_of_birth_num, long long& births_num)
{
	if (fish_map_copy.contains(time_of_birth_num)) {
		fish_map_copy[time_of_birth_num] += births_num;
	} else {
		fish_map_copy.insert(std::make_pair(time_of_birth_num, births_num));
	}
}

long long sum_all_fish(std::map<int, long long>& fish_map)
{
	long long fish_sum = 0;
	for (auto& elem : fish_map) {
		fish_sum += elem.second;
	}
	return fish_sum;
}

void check_fish_number_after_x_days(int day, std::map<int, long long> fish_map)
{
	for (int i = 0; i < day; i++) {

		int counter = 0;
		long long fish_to_add_on_6_and_8 = -1;
		std::map<int, long long> fish_map_copy;

		for (auto& fish : fish_map) {

			if (fish.first == 0) {
				fish_to_add_on_6_and_8 = fish_map[0];
			} else {
				fish_map_copy.insert(std::make_pair(fish.first - 1, fish.second));
			}

			counter++;
		}

		if (fish_to_add_on_6_and_8 != -1) {
			birth_action(fish_map_copy, 6, fish_to_add_on_6_and_8);
			birth_action(fish_map_copy, 8, fish_to_add_on_6_and_8);
		}

		fish_map.clear();
		fish_map = fish_map_copy;
	}

	std::cout << "After " << day << " days, there will be: " << sum_all_fish(fish_map) << " fish." << std::endl;
}

int main() {

	std::map<int, long long> fish_map;

	read_data(fish_map);
	check_fish_number_after_x_days(80, fish_map);
	check_fish_number_after_x_days(256, fish_map);

	return 0;
}
