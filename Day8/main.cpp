#include <set>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <unordered_map>

void read_data(std::vector<std::vector<std::string>>& unique_signal_patterns, std::vector<std::vector<std::string>>& four_digit_output)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);
	if (new_file.is_open()) {
		std::string line;
		while (std::getline(new_file, line)) {
			std::istringstream iss(line);
			std::string token;
			int counter = 0;
			while (std::getline(iss, token, '|')) {
				
				std::istringstream iss_(token);
				std::string elem_token;
				std::vector<std::string> vec;
				while (std::getline(iss_, elem_token, ' ')) {
					if (elem_token != "") {
						vec.push_back(elem_token);
					}
				}

				counter++ == 0 ? unique_signal_patterns.push_back(vec) : four_digit_output.push_back(vec);
			}
		}
	}
}

void put_in_map(std::string& elem, std::unordered_map<int, std::set<std::string>>& new_map, int val)
{
	std::set<std::string> some_set;
	for (auto& char_1 : elem) {
		std::string val;  val.push_back(char_1);
		some_set.insert(val);
	}

	new_map[val] = some_set;
}

void Part1(std::vector<std::vector<std::string>>& four_digit_output)
{
	int sum = 0;
	for (auto& vec_elem : four_digit_output) {
		for (auto& elem : vec_elem) {
			if (elem.size() == 2 || elem.size() == 3 || elem.size() == 4 || elem.size() == 7) {
				sum++;
			}
		}
	}

	std::cout << "We have " << sum << " unique  four_digit_output" << std::endl;
}


void find_easy_to_decode_values(std::vector<std::string>& signal_pattern, std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers)
{
	for (auto& one_pattern : signal_pattern) {
		int size = one_pattern.size();
		if (size == 2 || size == 3 || size == 4 || size == 7) {
			switch (size) {
			case 2:
				put_in_map(one_pattern, easy_to_find_numbers, 1);
				break;
			case 3:
				put_in_map(one_pattern, easy_to_find_numbers, 7);
				break;
			case 4:
				put_in_map(one_pattern, easy_to_find_numbers, 4);
				break;
			case 7:
				put_in_map(one_pattern, easy_to_find_numbers, 8);
				break;
			}
		}
	}
}

void get_all_paterns_size_6(std::vector<std::string>& signal_pattern, std::string& all_with_size_6)
{
	for (auto& elem : signal_pattern) {
		if (elem.size() == 6) {
			all_with_size_6 += elem;
		}
	}
}

void get_unique_elemets(std::string& str, std::set<char>& unique_elements)
{
	for (auto& elem : str) {
		unique_elements.insert(elem);
	}
}

void get_diff_in_size_6_pattern(std::set<char>& unique_elements, std::string& all_with_size_6, std::set<std::string>& diff_in_size_6)
{
	for (auto& elem : unique_elements) {
		size_t n = std::count(all_with_size_6.begin(), all_with_size_6.end(), elem);
		if (n == 2) {
			std::string val;  val.push_back(elem);
			diff_in_size_6.insert(val);
		}
	}
}

void find_middle_right_up(std::set<std::string>& diff_in_size_6, std::string& left_bottom, std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& middle, std::string& right_up)
{
	for (auto& elem : diff_in_size_6) {
		if (elem != left_bottom) {
			auto dd = easy_to_find_numbers[1].count(elem);
			if (dd == 0) {
				middle = elem;
			} else if (dd == 1) {
				right_up = elem;
			}
		}
	}
}

void find_right_bottom(std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& right_up, std::string& right_bottom)
{
	for (auto& elem : easy_to_find_numbers[1]) {
		if (elem != right_up) {
			right_bottom = elem;
		}
	}
}

void find_left_top(std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& right_up, std::string& middle, std::string& right_bottom, std::string& left_top)
{
	for (auto& elem : easy_to_find_numbers[4]) {
		if (elem != right_up && elem != middle && elem != right_bottom) {
			left_top = elem;
		}
	}
}

void find_top(std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& right_up, std::string& right_bottom, std::string& top)
{
	for (auto& elem : easy_to_find_numbers[7]) {
		if (elem != right_up && elem != right_bottom) {
			top = elem;
		}
	}
}

void find_bottom(std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& right_up, std::string& middle, std::string& right_bottom, std::string& left_bottom, std::string& left_top, std::string& top, std::string& bottom)
{
	for (auto& elem : easy_to_find_numbers[8]) {
		if (elem != right_up && elem != middle && elem != right_bottom && elem != left_bottom && elem != left_top && elem != top) {
			bottom = elem;
		}
	}
}

void find_left_bottom(std::set<std::string>& diff_in_size_6, std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& left_down)
{
	for (auto& elem : diff_in_size_6) {
		auto count = easy_to_find_numbers[4].count(elem);
		if (count == 0) {
			left_down = elem;
		}
	}
}

void find_proper_mapping(std::set<std::string>& diff_in_size_6, std::unordered_map<int, std::set<std::string>>& easy_to_find_numbers, std::string& left_bottom, std::string& middle, std::string& right_up, std::string& right_bottom, std::string& left_top, std::string& top, std::string& bottom)
{
	find_left_bottom(diff_in_size_6, easy_to_find_numbers, left_bottom);
	find_middle_right_up(diff_in_size_6, left_bottom, easy_to_find_numbers, middle, right_up);
	find_right_bottom(easy_to_find_numbers, right_up, right_bottom);
	find_left_top(easy_to_find_numbers, right_up, middle, right_bottom, left_top);
	find_top(easy_to_find_numbers, right_up, right_bottom, top);
	find_bottom(easy_to_find_numbers, right_up, middle, right_bottom, left_bottom, left_top, top, bottom);
}

void decoded_four_digit_output(std::vector<std::vector<std::string>>& four_digit_output, int& counter, std::string& number, std::string& right_up, std::string& left_bottom, std::string& right_bottom, std::string& left_top, std::string& middle, int& sum)
{
	for (auto& elem : four_digit_output[counter++]) {

		switch (elem.size()) {
		case 2:
			number += "1";
			break;
		case 4:
			number += "4";
			break;
		case 3:
			number += "7";
			break;
		case 7:
			number += "8";
			break;
		case 5:
			{
				if (elem.find(right_up) != std::string::npos && elem.find(left_bottom) != std::string::npos) number += "2";
				else if (elem.find(right_up) != std::string::npos && elem.find(right_bottom) != std::string::npos) number += "3";
				else if (elem.find(left_top) != std::string::npos && elem.find(right_bottom) != std::string::npos) number += "5";
			}
			break;
		case 6:
			{
				if (elem.find(right_up) == std::string::npos) number += "6";
				else if (elem.find(left_bottom) == std::string::npos) number += "9";
				else if (elem.find(middle) == std::string::npos) number += "0";
			}
			break;
		}
	}

	sum += std::stoi(number);
}

void Part2(std::vector<std::vector<std::string>>& unique_signal_patterns, std::vector<std::vector<std::string>>& four_digit_output)
{
	int sum = 0, counter = 0;

	for (auto& signal_pattern : unique_signal_patterns) {
		std::string number, all_with_size_6;
		std::set<char> unique_elements;
		std::set<std::string> diff_in_size_6;
		std::unordered_map<int, std::set<std::string>> easy_to_find_numbers;
		std::string left_bottom, middle, right_up, right_bottom, bottom, top, left_top;
		
		find_easy_to_decode_values(signal_pattern, easy_to_find_numbers);
		get_all_paterns_size_6(signal_pattern, all_with_size_6);
		get_unique_elemets(all_with_size_6, unique_elements);
		get_diff_in_size_6_pattern(unique_elements, all_with_size_6, diff_in_size_6);
		find_proper_mapping(diff_in_size_6, easy_to_find_numbers, left_bottom, middle, right_up, right_bottom, left_top, top, bottom);
		decoded_four_digit_output(four_digit_output, counter, number, right_up, left_bottom, right_bottom, left_top, middle, sum);
	}

	std::cout << "Sum of decoded four-digit output values: " << sum << std::endl;
}

int main() {

	std::vector<std::vector<std::string>> unique_signal_patterns;
	std::vector<std::vector<std::string>> four_digit_output;

	read_data(unique_signal_patterns, four_digit_output);

	Part1(four_digit_output);
	Part2(unique_signal_patterns, four_digit_output);

	return 0;
}



