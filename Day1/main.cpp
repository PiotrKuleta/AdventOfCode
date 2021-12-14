#include <vector>
#include <string>
#include <iostream>
#include <fstream>

void readData(std::vector<int>& vec)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);

	if (new_file.is_open()) {
		std::string line;
		while (std::getline(new_file, line)) {
			vec.push_back(std::stoi(line));
		}
	}
}

void checkIfGreaterThanPrevius(std::vector<int>& vec,int counter,int& greater_than_prev_counter,int&  prev_val)
{
	if (counter != 0 && vec[counter - 1] < vec[counter]) {greater_than_prev_counter++;}
	prev_val = vec[counter];
}

void checkIfSlidingWindowIncrease(int counter, std::vector<int>& vec, int& prev_slider_sum, int& greater_than_prev_sliding_counter)
{
	int current_sum = 0;
	if (counter >= 2) {
		current_sum = vec[counter] + vec[counter - 1] + vec[counter - 2];
	}
	
	if (prev_slider_sum < current_sum && counter >= 3) {
		greater_than_prev_sliding_counter++;
	}
	
	prev_slider_sum = current_sum;
}

void returnOutput(int greater_than_prev_counter, int greater_than_prev_sliding_counter)
{
	std::cout << "In comparison to previous value: : " << greater_than_prev_counter << " times increased !!!" << std::endl <<
		"In comparison to previous sliding window: : " << greater_than_prev_sliding_counter << " times increased !!!" << std::endl;
}

void calculateOutput(std::vector<int>& vec, int& greater_than_prev_value, int& greater_than_prev_sliding_value)
{
	int counter{ 0 }, prev_val{ 0 }, prev_slider_sum{ 0 };
	for (auto& elem : vec) {
		checkIfGreaterThanPrevius(vec, counter, greater_than_prev_value, prev_val);
		checkIfSlidingWindowIncrease(counter++, vec, prev_slider_sum, greater_than_prev_sliding_value);
	}
}

int main() {

	std::vector<int> vec;
	int greater_than_prev_value{ 0 }, greater_than_prev_sliding_value{ 0 };

	readData(vec);
	calculateOutput(vec, greater_than_prev_value, greater_than_prev_sliding_value);
	returnOutput(greater_than_prev_value, greater_than_prev_sliding_value);

	return 0;
}
