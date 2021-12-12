#include <map>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <unordered_set>
#include <unordered_map>

bool check_big_letter(char letter){
	return letter >= 'A' && letter <= 'Z';
}

void read_data(std::multimap<std::string, std::string>& input)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;	
		while (std::getline(new_file, line)) {
			std::vector<std::string> transformed_line;
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, '-')) {
				transformed_line.push_back(token);
			}
			std::string key = transformed_line[0], value = transformed_line[1];
			if (key != "end" && value != "start") {
				input.insert(std::make_pair(key, value));
			}
			if (key != "start" && value != "end") {
				input.insert(std::make_pair(value, key));
			}
		}
	}
}

void move_along_graph(std::string nodes_key, std::multimap<std::string, std::string>& input, std::unordered_set<std::string>& correct_route, std::unordered_map<std::string, int> used_small, std::string route, std::string variant, bool small_used_twice)
{
	route += nodes_key + " ";
	if (nodes_key == "end") {
		correct_route.insert(route);
		return;
	}

	if (!check_big_letter(nodes_key[0])) {
		if (!used_small.contains(nodes_key)) {
			used_small.insert(std::make_pair(nodes_key, 1));
		} else if (!small_used_twice && variant == "Part2") {
			small_used_twice = true;
			used_small[nodes_key] += 1;
		}
	}

	auto nodes = input.equal_range(nodes_key);
	for (auto i = nodes.first; i != nodes.second; ++i) {
		
		if (variant == "Part1") {
			if (used_small.contains(i->second)) { continue; }
		} else {
			if (used_small.contains(i->second) && small_used_twice) { continue; }
		}

		move_along_graph(i->second, input, correct_route, used_small, route, variant, small_used_twice);
	}
}

int main()
{
	std::unordered_set<std::string> correct_route_p1;
	std::unordered_set<std::string> correct_route_p2;
	std::multimap<std::string,std::string> input;
	
	read_data(input);
	move_along_graph("start", input, correct_route_p1, std::unordered_map<std::string, int>(), {}, "Part1", false);
	std::cout << "Part1: " << correct_route_p1.size() << std::endl;

	move_along_graph("start", input, correct_route_p2, std::unordered_map<std::string, int>(), {}, "Part2", false);
	std::cout << "Part2: " << correct_route_p2.size() << std::endl;

	return 0;
}
