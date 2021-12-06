#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <algorithm>

struct vent_line {
public:
	vent_line() : x1(0),x2(0),y1(0),y2() {};
	~vent_line() {};

	void insert_vent(int num, int val) {
		if (num == 1) { x1 = val; }
		else if (num == 2) { y1 = val; }
		else if (num == 3) { x2 = val; }
		else if (num == 4) { y2 = val; }
	};

public:
	int x1, x2, y1, y2;

};

int main() {

	std::fstream new_file;
	new_file.open("input", std::ios::in);
	
	std::vector<vent_line*> all_vents;

	if (new_file.is_open()) {

		std::string line;

		while (std::getline(new_file, line)) {

			std::string sfind = " -> ";
			std::string sReplace = ",";
			line.replace(line.find(sfind), sfind.size(), sReplace);
			//std::cout << line << std::endl;

			std::istringstream iss(line);
			std::string token;

			vent_line* vent= new vent_line();
			
			int counter = 1;
			while (std::getline(iss, token, ',')) {
				vent->insert_vent(counter++, std::stoi(token));
			}

			all_vents.push_back(vent);
		}

	}

	int max_x = 0;
	int max_y = 0;
	for (auto& vent : all_vents) {
		max_x = vent->x1 > max_x ? vent->x1 : max_x;
		max_x = vent->x2 > max_x ? vent->x2 : max_x;

		max_y = vent->y1 > max_y ? vent->y1 : max_y;
		max_y = vent->y2 > max_y ? vent->y2 : max_y;
	}

	std::vector<std::vector<int>>diagram;
	for (int i = 0; i <= max_x; i++) { 
		std::vector<int> vec( max_y + 1, 0 ); 
		diagram.push_back(vec);
	}

	for (auto& vent : all_vents) {
		if (vent->x1 == vent->x2) {
			
			int lower, greater;
			if (vent->y1 < vent->y2) {
				lower = vent->y1;
				greater = vent->y2;
			} else {
				greater  = vent->y1;
				lower = vent->y2;
			}

			for (int i = lower; i <= greater; i++) {
				diagram[i][vent->x1] += 1;
			}


		} else if (vent->y1 == vent->y2) {

			int lower, greater;
			if (vent->x1 < vent->x2) {
				lower = vent->x1;
				greater = vent->x2;
			}
			else {
				greater = vent->x1;
				lower = vent->x2;
			}

			for (int i = lower; i <= greater; i++) {
				diagram[vent->y1][i] += 1;
			}

		}

	}

	int count_2_more = 0;
	for (auto& diagram_line : diagram) {
		
		for (int i = 0; i < diagram_line.size(); i++) {
			diagram_line[i] >= 2 ? count_2_more++ : 0 ;
		}
	}

	std::cout << "Part1 answer: " << count_2_more <<std::endl;

	int counter = 0;

	for (auto& vent : all_vents) {
		if (vent->x1 == vent->y1 && vent->x2 == vent->y2) {
			
			int lower, greater;
			if (vent->x1 < vent->x2) {
				lower = vent->x1;
				greater = vent->x2;
			}
			else {
				greater = vent->x1;
				lower = vent->x2;
			}
			
			for (int i = lower; i <= greater; i++) {
				diagram[i][i] += 1;
			}
		
		} else if (vent->x1 == vent->y2 && vent->x2 == vent->y1) {
			
			int lower, greater;
			if (vent->x1 < vent->y1) {
				lower = vent->x1;
				greater = vent->y1;
			}
			else {
				greater = vent->x1;
				lower = vent->y1;
			}

			int y_ = greater;
			for (int i = lower; i <= greater; i++) {
				diagram[i][y_--] += 1;
			}
		
		} else if (std::abs(vent->x1 - vent->x2) == std::abs(vent->y1 - vent->y2)) { // tu jest blad ne bezwzgledna !!
			
			bool check_case = true;;
			int lower, greater, check_;
			if (vent->x1 - vent->x2 > 0) {
				
				if (vent->y1 > vent->y2 > 0) {
					lower = vent->y2; 
					greater = vent->y1;
					check_ = vent->x2;
				} else {
					lower = vent->y1;
					greater = vent->y2;
					check_ = vent->x1;
					check_case = false;
				}		
			} else {
	
				if (vent->y1 < vent->y2 > 0) {
					lower = vent->y1;
					greater = vent->y2;

					check_ = vent->x1;
				} else {
					lower = vent->y2; 
					greater = vent->y1;
					check_ = vent->x2;
					check_case = false;
				}
			}


			for (int i = lower; i <= greater; i++) {

				int y = check_case == true ? check_++  : check_-- ;

				diagram[i][y] += 1;
			}
		}

		for (auto& diagram_line : diagram) {

			for (int i = 0; i < diagram_line.size(); i++) {
			}
		}

		counter++;
	}

	int count_2_more_2 = 0;
	for (auto& diagram_line : diagram) {
		for (int i = 0; i < diagram_line.size(); i++) {
			diagram_line[i] >= 2 ? count_2_more_2++ : 0;
		}
	}

	std::cout << "Part2 answer: " << count_2_more_2 << std::endl;

	return 0;
}
