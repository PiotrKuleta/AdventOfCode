#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

void read_data(std::vector<std::vector<int>>& lava_tubes)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;	
		while (std::getline(new_file, line)) {
			std::vector<int> tube;
			std::istringstream iss(line);
			for (auto& bubble : line) {
				tube.push_back(bubble - 48);
			}
			lava_tubes.push_back(tube);
		}
	}
}

void check_around(std::vector<std::vector<int>>& lava_tubes, int x, int y, int current_val, std::vector<std::pair<int, int>>& lowest_point_vec, int algorithm_depth, bool& lowest_val)
{
	if (x < 0 || x >= lava_tubes.size() || y < 0 || y >= lava_tubes[0].size())
		return;
	if (algorithm_depth >= 2)
		return;

	if (algorithm_depth > 0) {
		if (current_val < lava_tubes[x][y] && lowest_val == true) {
			lowest_val = true;
		} else {
			lowest_val = false;
		}
	}

	check_around(lava_tubes, x + 1, y, current_val, lowest_point_vec, algorithm_depth +1, lowest_val);
	check_around(lava_tubes, x - 1, y, current_val, lowest_point_vec, algorithm_depth +1, lowest_val);
	check_around(lava_tubes, x, y + 1, current_val, lowest_point_vec, algorithm_depth +1, lowest_val);
	check_around(lava_tubes, x, y - 1, current_val, lowest_point_vec, algorithm_depth +1, lowest_val);

	if (algorithm_depth ==0 && lowest_val) {
		lowest_point_vec.push_back(std::make_pair(x, y)); 
	}
}

void Part1_findFourDigitOutput(std::vector<std::vector<int>>& lava_tubes, std::vector<std::pair<int, int>>& lowest_point_vec) {
	for (int x = 0; x < lava_tubes.size(); x++) {
		for (int y = 0; y < lava_tubes[0].size(); y++) {
			int depth = 0;
			bool lowest_val = true;
			check_around(lava_tubes, x, y, lava_tubes[x][y], lowest_point_vec, 0, lowest_val);
		}
	}

}

void fill_around(std::vector<std::vector<int>>& lava_tubes, int x, int y,  int frame_value,int& occurrences) {
	if (x < 0 || x >= lava_tubes.size() || y < 0 || y >= lava_tubes[0].size())
		return;
	if (lava_tubes[x][y] == frame_value)
		return;

	occurrences++;
	lava_tubes[x][y] = frame_value; 

	fill_around(lava_tubes, x + 1, y, frame_value, occurrences);
	fill_around(lava_tubes, x - 1, y, frame_value, occurrences);
	fill_around(lava_tubes, x, y + 1, frame_value, occurrences);
	fill_around(lava_tubes, x, y - 1, frame_value, occurrences);
}

std::multiset<int> Part2_findLargestBasins(std::vector<std::pair<int, int>>& lowest_point_vec, std::vector<std::vector<int>>& lava_tubes, int frame_value)
{
	std::multiset<int> basins;
	for (auto& point : lowest_point_vec) {
		int occurrences = 0;
		fill_around(lava_tubes, point.first, point.second, frame_value, occurrences);
		basins.insert(occurrences);
	}
	return basins;
}

void count_output(std::vector<std::vector<int>>& lava_tubes, std::vector<std::pair<int, int>> lowest_point_vec) {
	int sum = 0;
	for (auto& point : lowest_point_vec) {
		sum += 1+ lava_tubes[point.first][point.second];
	}
	std::cout << "Sum of unique four_digit_output: " << sum << std::endl;
}

void count_top_3(std::multiset<int> basins) {
	int sum = 1;
	for (int i = basins.size() - 3; i < basins.size(); i++) {
		sum *= *next(basins.begin(), i);
	}
	std::cout << "Three largest basins size :" << sum << std::endl;
}

int main()
{
	std::vector<std::vector<int>> lava_tubes;
	std::vector<std::pair<int, int>> lowest_point_vec;

	read_data(lava_tubes);

	Part1_findFourDigitOutput(lava_tubes, lowest_point_vec);
	count_output(lava_tubes, lowest_point_vec);
	count_top_3(Part2_findLargestBasins(lowest_point_vec, lava_tubes, 9));

	return 0;
}
