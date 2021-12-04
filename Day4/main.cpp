#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <algorithm>

struct  bingo_board
{
public:
	bingo_board() : row_size(0), board_sum(0) {};
	bingo_board(int row_size, int board_sum) :row_size(row_size), board_sum(board_sum) {};
	~bingo_board() {};
	
	void insert_row_into_board(std::string str) {
		
		int val, size = 0;
		std::vector<int> row;
		std::istringstream iss(str);

		while (iss >> val) {
			size++;
			nums_in_board.insert(val);
			row.push_back(val);
		}

		row_size = row_size > 0 ? row_size : size;

		board.push_back(row);
	};

	void count_sum() {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < row_size ; j++) {
				board_sum += board[i][j];
			}
		}
	};

	bool check_num_existance(int val) {
		return nums_in_board.contains(val);
	};
	
	std::tuple<bool, int> check_num_in_board(int num) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < row_size; j++) {
				if (board[i][j] == num) {
					board[i][j] = -1;
					board_sum -= num;
					
					auto ret = check_winner(i, j);
					return ret;
				}
			}
		}
		return std::make_tuple(false, 0);
	};
	
	std::tuple<bool, int> check_winner(int row, int column) {
		//check row
		int current_sum_row = 0;
		for (int i = 0; i < row_size; i++) { 
			current_sum_row += board[row][i];
		}
		
		if (current_sum_row == -5) {
			return std::make_tuple(true, board_sum);
		} else {
			//check column
			int current_sum_column = 0;
			for (int i = 0; i < board.size(); i++) {
				current_sum_column += board[i][column];
			}

			return current_sum_column == -5 ? std::make_tuple(true, board_sum) : std::make_tuple(false, 0);
		}
	};

	int get_board_sum() {
		return board_sum;
	}

private:
	int row_size;
	int board_sum;
	std::set<int> nums_in_board;
	std::vector<std::vector<int>> board;
};

void insert_drawed_num(std::string line, std::vector<int>& drawed_nums) 
{
	std::string val;
	std::istringstream ss(line);
	while (std::getline(ss, val, ',')) {
		drawed_nums.push_back(std::stoi(val));
	}
}

void insert_data(std::vector<int>& drawed_nums, std::vector<std::unique_ptr<bingo_board>>& all_board)
{
	std::fstream new_file;
	new_file.open("input", std::ios::in);

	if (new_file.is_open()) {
		
		int counter = 0;
		std::string line;
		while (std::getline(new_file, line)) {

			if (counter == 0) { 
				insert_drawed_num(line, drawed_nums);
			} else {
				if (line == "") {
					auto new_board = std::make_unique<bingo_board>(0,0);
					if (new_board != nullptr) {
						all_board.push_back(std::move(new_board));
					}
				} else {
					all_board.back()->insert_row_into_board(line);
				}
			}
			counter++;
		}
	}
}

void board_count_sum(std::vector<std::unique_ptr<bingo_board>>& all_board) 
{
	for (auto& board : all_board) {
		board->count_sum();
	}
}

int start_bingo(std::vector<int>& drawed_nums, std::vector<std::unique_ptr<bingo_board>>& all_board, std::string strategy) 
{
	bool exit = false;
	int return_val = 0;

	for (auto& num : drawed_nums) {
		int board_num = 0;
		std::vector<int> erase_vec;
		for (auto& board : all_board) {
			if (board->check_num_existance(num)) {
				auto ret = board->check_num_in_board(num);
				
				if (std::get<0>(ret)) {
					// Strategy first winner
					if (strategy == "First") {
						return_val = std::get<1>(ret) * num;
						exit = true;
						break;
					} else if (strategy == "Last") {
						erase_vec.push_back(board_num);
					}
				}
			}
			board_num++;
		}

		if (exit) break;

		// Strategy last winner
		if (strategy == "Last") {
			std::sort(erase_vec.begin(), erase_vec.end(), std::greater<int>());
			if (all_board.size() == 1) {
				return_val = all_board[0]->get_board_sum() * num;
				exit = true;
				break;
			}

			for (auto& elem : erase_vec) {
				all_board.erase(all_board.begin() + elem);
			}
		}
	}

	return return_val;
}

int main() {

	std::vector<int>drawed_nums;
	std::vector<std::unique_ptr<bingo_board>> all_board;

	insert_data(drawed_nums, all_board);
	board_count_sum(all_board);

	int ret_part1 = start_bingo(drawed_nums, all_board, "First");
	std::cout << "Final score of the winning board: " << ret_part1 << std::endl;

	int ret_part2 = start_bingo(drawed_nums, all_board, "Last");
	std::cout << "Final score of the last winning board: " << ret_part2 << std::endl;

	return 0;
}
