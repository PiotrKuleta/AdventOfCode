#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

void read_data(std::vector<std::vector<int>>& input)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;	
		while (std::getline(new_file, line)) {
			std::vector<int> transformed_line;
			std::istringstream iss(line);
			for (auto& sign : line) {
				transformed_line.push_back(sign - 48);
			}
			input.push_back(transformed_line);
		}
	}
}

void flash_around(std::vector<std::vector<int>>& dumbo_octopus_energy, int x, int y, std::set<std::string>& currently_flashed_octopus, int& flash_sum)
{
	std::string str = std::to_string(x) + std::to_string(y);
	
	if (x < 0 || x >= dumbo_octopus_energy.size() || y < 0 || y >= dumbo_octopus_energy[0].size())
		return;
	if (dumbo_octopus_energy[x][y] <= 8) {
		if (!currently_flashed_octopus.contains(str)) {
			dumbo_octopus_energy[x][y] += 1;
		}
		return;
	}

	//Flash !!
	if (!currently_flashed_octopus.contains(str)) {
		flash_sum += 1;
		dumbo_octopus_energy[x][y] = 0;
		currently_flashed_octopus.insert(str);
	}

	flash_around(dumbo_octopus_energy, x + 1, y, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x - 1, y, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x, y + 1, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x, y - 1, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x + 1, y + 1, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x + 1, y - 1, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x - 1, y + 1, currently_flashed_octopus, flash_sum);
	flash_around(dumbo_octopus_energy, x - 1, y - 1, currently_flashed_octopus, flash_sum);
}

void count_current_sum(std::vector<std::vector<int>>& input_copy, int& sf)
{
	for (int x = 0; x < input_copy.size(); x++) {
		for (int y = 0; y < input_copy[0].size(); y++) {
			sf += input_copy[x][y];
		}
	}
}

void check_flashes(std::vector<std::vector<int>>& input, std::set<std::string>& currently_flashed_octopus, int& flash_sum)
{
	for (int x = 0; x < input.size(); x++) {
		for (int y = 0; y < input[0].size(); y++) {
			flash_around(input, x, y, currently_flashed_octopus, flash_sum);
		}
	}
}

void Part1_after_x_steps(std::vector<std::vector<int>>& input, int steps)
{
	int flash_sum = 0;
	for (int step_num = 0; step_num < steps; step_num++) {
		std::set<std::string> currently_flashed_octopus;

		check_flashes(input, currently_flashed_octopus, flash_sum);
	}
	std::cout << "After " << steps << " steps, there is: " << flash_sum << " flashes." << std::endl;
}

void Part2_first_synchronized_flash(std::vector<std::vector<int>>& input)
{
	int synchronizing_step = 0, flash_sum = 0;
	while (true) {
		synchronizing_step++;
		std::set<std::string> currently_flashed_octopus;

		check_flashes(input, currently_flashed_octopus, flash_sum);

		if (currently_flashed_octopus.size() == (input.size() * input[0].size())) {
			break;
		}
	}

	std::cout << "Octopuses synchronize at " << synchronizing_step << " step." << std::endl;
}

int main()
{
	std::vector<std::vector<int>> input;
	
	read_data(input);
	auto input_copy = input;

	Part1_after_x_steps(input, 100);
	Part2_first_synchronized_flash(input_copy);

	return 0;
}
