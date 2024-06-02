#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

vector<vector<char>> createMaze(int width, int height) {
    vector<vector<char>> maze(height, vector<char>(width, '#'));
    stack<pair<int, int>> stack;
    stack.push({1, 1});
    maze[1][1] = ' ';

    srand(time(0));

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        vector<pair<int, int>> directions = {{x - 2, y}, {x + 2, y}, {x, y - 2}, {x, y + 2}};
        random_shuffle(directions.begin(), directions.end());
        bool found = false;

        for (auto direction : directions) {
            int nx = direction.first;
            int ny = direction.second;
            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[ny][nx] == '#') {
                maze[ny][nx] = ' ';
                maze[ny + (y - ny) / 2][nx + (x - nx) / 2] = ' ';
                stack.push({nx, ny});
                found = true;
                break;
            }
        }

        if (!found) {
            stack.pop();
        }
    }

    maze[1][1] = 'S';  // Start
    maze[height - 2][width - 2] = 'E';  // End
    return maze;
}

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

vector<pair<int, int>> dfs(const vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
    stack<pair<int, int>> stack;
    stack.push(start);
    map<pair<int, int>, pair<int, int>> parent;
    parent[start] = {-1, -1};

    while (!stack.empty()) {
        pair<int, int> current = stack.top();
        stack.pop();
        if (current == end) {
            break;
        }

        int x = current.first, y = current.second;
        vector<pair<int, int>> directions = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (auto& direction : directions) {
            int nx = direction.first, ny = direction.second;
            if (maze[ny][nx] != '#' && parent.find({nx, ny}) == parent.end()) {
                stack.push({nx, ny});
                parent[{nx, ny}] = current;
            }
        }
    }

    vector<pair<int, int>> path;
    for (pair<int, int> at = end; at != make_pair(-1, -1); at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> bfs(const vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
    queue<pair<int, int>> queue;
    queue.push(start);
    map<pair<int, int>, pair<int, int>> parent;
    parent[start] = {-1, -1};

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();
        if (current == end) {
            break;
        }

        int x = current.first, y = current.second;
        vector<pair<int, int>> directions = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (auto& direction : directions) {
            int nx = direction.first, ny = direction.second;
            if (maze[ny][nx] != '#' && parent.find({nx, ny}) == parent.end()) {
                queue.push({nx, ny});
                parent[{nx, ny}] = current;
            }
        }
    }

    vector<pair<int, int>> path;
    for (pair<int, int> at = end; at != make_pair(-1, -1); at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void displayMazeWithPath(vector<vector<char>> maze, const vector<pair<int, int>>& path) {
    for (const auto& position : path) {
        int x = position.first, y = position.second;
        if (maze[y][x] != 'S' && maze[y][x] != 'E') {
            maze[y][x] = '.';
        }
    }
    printMaze(maze);
}

void showMenu() {
    cout << "Labirent Oyunu\n";
    cout << "1. Kolay (15x15)\n";
    cout << "2. Orta (21x21)\n";
    cout << "3. Zor (31x31)\n";
    cout << "4. Cikis\n";
    cout << "Seciminizi yapin: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        int width, height;

        switch (choice) {
            case 1:
                width = 15;
                height = 15;
                break;
            case 2:
                width = 21;
                height = 21;
                break;
            case 3:
                width = 31;
                height = 31;
                break;
            case 4:
                cout << "Cikis yapiliyor..." << endl;
                return 0;
            default:
                cout << "Gecersiz secim. Tekrar deneyin." << endl;
                continue;
        }

        vector<vector<char>> maze = createMaze(width, height);
        printMaze(maze);

        pair<int, int> start = {1, 1};
        pair<int, int> end = {width - 2, height - 2};

        vector<pair<int, int>> dfsPath = dfs(maze, start, end);
        cout << "DFS ile bulunan yol:" << endl;
        displayMazeWithPath(maze, dfsPath);

        vector<pair<int, int>> bfsPath = bfs(maze, start, end);
        cout << "BFS ile bulunan yol:" << endl;
        displayMazeWithPath(maze, bfsPath);

    } while (choice != 4);

    return 0;
}
