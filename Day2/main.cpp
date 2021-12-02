#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

int main() {

	std::fstream new_file;
	new_file.open("input", std::ios::in);

	int horizontal_position = 0, final_depth = 0, final_depth_with_aim = 0, aim =0  ;

	if (new_file.is_open()) {

		std::string command;
		int value;

		std::string line;
		while (std::getline(new_file, line)) {

			std::istringstream ss(line);
			ss >> command >> value;
			
			if(command == "forward") {
				horizontal_position += value;
				final_depth_with_aim += aim * value;
			} else {
				final_depth += command == "up" ? -value : value ;
				aim += command == "up" ? -value : value;
			}

		}

		std::cout << "Final result: " << horizontal_position * final_depth << " !" <<std::endl;
		std::cout << "Final result with aim: " << horizontal_position * final_depth_with_aim << " !" << std::endl;

	}

	return 0;
}
