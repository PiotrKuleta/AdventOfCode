#include <stdio.h>

#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

void read_data(std::vector<std::vector<int>>& input)
{
    std::fstream new_file;
    new_file.open("input", std::ios::in);
    if (new_file.is_open()) {
        std::string line;
        while (std::getline(new_file, line)) {
            std::vector<int> transformed_line;
            for (auto& elem : line) {
                transformed_line.push_back(elem - '0');
            }
            input.push_back(transformed_line);
        }
    }
}

struct Cell {
    int x;
    int y;
    int cost;
};

class compareClass 
{
public:
    bool operator() (const Cell& lhs, const Cell& rhs) const
    {
        return (lhs.cost > rhs.cost);
    }
};

bool isSafe(int x, int y, std::vector<std::vector<int>>& move_cost) 
{
    return x >= 0 && x < move_cost.size() && y >= 0 && y < move_cost[0].size();
}

int minCost(std::vector<std::vector<int>>& move_cost, int m, int n)
{
    int x_moves[] = { 1,-1, 0, 0 };
    int y_moves[] = { 0, 0, 1,-1 };

    std::vector<std::vector<int>> route_cost;
    std::vector<int> route_cost_row;

    std::vector<std::vector<bool>> visited;
    std::vector<bool> visited_row;

    for (int j = 0; j <= n; j++) {
        route_cost_row.push_back(INT_MAX);
        visited_row.push_back(false);
    }
    
    for (int i = 0; i <= m; i++) {
        route_cost.push_back(route_cost_row);
        visited.push_back(visited_row);
    }

    std::priority_queue<Cell, std::vector<Cell>, compareClass> p_queue;

    route_cost[0][0] = 0;
    p_queue.push({ 0, 0, 0 });

    while (!p_queue.empty()) {

        Cell cell = p_queue.top();
        p_queue.pop();
        int x = cell.x;
        int y = cell.y;
        if (visited[x][y]) continue;

        visited[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int next_x = x + x_moves[i];
            int next_y = y + y_moves[i];

            if (isSafe(next_x, next_y, move_cost) && !visited[next_x][next_y]) {
                route_cost[next_x][next_y] = std::min(route_cost[next_x][next_y],
                    route_cost[x][y] + move_cost[next_x][next_y]);
                p_queue.push({ next_x, next_y, route_cost[next_x][next_y] });
            }
        }
    }
    return route_cost[m][n];
}


void extend_row(std::vector<int> vec, std::vector<int>& input_elem ) {
    for (int i = 1; i < 5; i++) {
        std::transform(std::begin(vec), std::end(vec), std::begin(vec), [&](int x) {
            int modulo = (x + 1) % 9;
            x = modulo == 0 ? 9 : modulo;
            return x; });
        input_elem.insert(input_elem.end(), vec.begin(), vec.end());
    }
}

void increase_row(std::vector<std::vector<int>>& vec, std::vector<int> input_elem, int i) {
    std::transform(std::begin(input_elem), std::end(input_elem), std::begin(input_elem), [&](int x) {
        int modulo = (x + i) % 9;
        x = modulo == 0 ? 9 : modulo;
        return x; });
    vec.push_back(input_elem);
}

std::vector<std::vector<int>> extendInput(std::vector<std::vector<int>> input_copy)
{
    for (auto& input_elem : input_copy) {
        std::vector<int> vec = input_elem;
        extend_row(vec, input_elem);
    }

    std::vector<std::vector<int>> vec = input_copy;
    for (int i = 1; i < 5; i++) {
        for (auto& input_elem : vec) {
            increase_row(input_copy, input_elem, i);
        }
    }
    return input_copy;
}

void calculateDijkstra(std::vector<std::vector<int>> input, std::string part)
{
    printf("%s answer: %d \n", part.c_str(),  minCost(input, input.size() - 1, input[0].size() - 1));
}

int main()
{
    std::vector<std::vector<int>> input;
    read_data(input);
    calculateDijkstra(input, "Part1");
    calculateDijkstra(extendInput(input), "Part2");

    return 0;
}
