#include <string>
#include <iostream>
#include <fstream>

int main() {

	std::fstream new_file;

	new_file.open("input", std::ios::in);

	if (new_file.is_open()) {

		int counter = 0;
		int prev_val = 0;
		int grater_than_prev_counter = 0;

		std::string line;
		while (std::getline(new_file, line)) {
			
			int current_val = std::stoi(line);

			if (prev_val < current_val && counter!=0) {
				grater_than_prev_counter++;
			}

			prev_val = current_val;
			counter++;
		}

		std::cout << "Increased: " << grater_than_prev_counter << " times !!!";
	}

	return 0;
}
