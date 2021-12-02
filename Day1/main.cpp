#include <string>
#include <iostream>
#include <fstream>

int main() {

		std::fstream new_file;

	new_file.open("input", std::ios::in);

	if (new_file.is_open()) {

		std::vector<int> vec;

		int counter = 0;

		int prev_val = 0;
		int grater_than_prev_counter = 0;

		int prev_slider_sum = 0;
		int grater_than_prev_sliding_counter = 0;

		std::string line;
		while (std::getline(new_file, line)) {

			vec.push_back(std::stoi(line));
			
			{ //Check previous value
				if (counter != 0) {
					if (vec[counter - 1] < vec[counter]) {
						grater_than_prev_counter++;
					}
				}

				prev_val = vec[counter];
			}

			{ //Slider 
				int current_sum = 0;
				if (counter >= 2) {
					current_sum = vec[counter] + vec[counter - 1] + vec[counter - 2];
				}

				if (prev_slider_sum < current_sum && counter >= 3) {
					grater_than_prev_sliding_counter++;
				}

				prev_slider_sum = current_sum;
			}

			counter++;
		}

		std::cout << "In comparison to previous value: : " << grater_than_prev_counter << " times increased !!!" << std::endl <<
			     "In comparison to previous sliding window: : " << grater_than_prev_sliding_counter << " times increased !!!" << std::endl;
	}

	return 0;
}
