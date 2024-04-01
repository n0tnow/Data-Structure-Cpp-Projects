#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class MazeSolver {
private:
    int rows;
    int cols;
    int **maze;
    pair<int, int> start;
    pair<int, int> end;
    bool **visited;

public:
    MazeSolver(int rows, int cols) : rows(rows), cols(cols) {
        maze = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            maze[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                maze[i][j] = rand() % 2; // 0 or 1
            }
        }

        // Make start and end points passable
        maze[0][0] = 0;
        maze[rows - 1][cols - 1] = 0;

        // Ensure there is at least one path in the maze
        while (!isPathExist()) {
            resetMaze();
        }

        // Set start and end points
        start = make_pair(0, 0);
        end = make_pair(rows - 1, cols - 1);

        visited = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                visited[i][j] = false;
            }
        }
    }

    void resetMaze() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maze[i][j] = rand() % 2; // 0 or 1
            }
        }
        maze[0][0] = 0;
        maze[rows - 1][cols - 1] = 0;
    }

    bool isPathExist() {
        queue<pair<int, int>> q;
        q.push(make_pair(0, 0));

        bool **visitedBFS = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            visitedBFS[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                visitedBFS[i][j] = false;
            }
        }

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();

            if (current == end) {
                return true;
            }

            visitedBFS[current.first][current.second] = true;

            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};

            for (int i = 0; i < 4; ++i) {
                int nx = current.first + dx[i];
                int ny = current.second + dy[i];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visitedBFS[nx][ny]) {
                    q.push(make_pair(nx, ny));
                    visitedBFS[nx][ny] = true;
                }
            }
        }

        return false;
    }

    void printMaze() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == start.first && j == start.second) {
                    cout << "S ";
                } else if (i == end.first && j == end.second) {
                    cout << "E ";
                } else {
                    cout << (maze[i][j] == 1 ? "# " : ". ");
                }
            }
            cout << endl;
        }
    }

    bool solveDFS(pair<int, int> current = make_pair(0, 0)) {
        if (current == end) {
            visited[current.first][current.second] = true;
            return true;
        }

        visited[current.first][current.second] = true;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = current.first + dx[i];
            int ny = current.second + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visited[nx][ny]) {
                if (solveDFS(make_pair(nx, ny))) {
                    maze[nx][ny] = '-';
                    return true;
                }
            }
        }

        return false;
    }

    bool solveBFS() {
        queue<pair<int, int>> q;
        q.push(start);

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();

            if (current == end) {
                visited[current.first][current.second] = true;
                return true;
            }

            visited[current.first][current.second] = true;

            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};

            for (int i = 0; i < 4; ++i) {
                int nx = current.first + dx[i];
                int ny = current.second + dy[i];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visited[nx][ny]) {
                    q.push(make_pair(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }

        return false;
    }

    ~MazeSolver() {
        for (int i = 0; i < rows; ++i) {
            delete[] maze[i];
            delete[] visited[i];
        }
        delete[] maze;
        delete[] visited;
    }
};

int main() {
    srand(time(NULL));
    bool exitProgram = false;

    while (!exitProgram) {
        MazeSolver mazeSolver(8, 8); // 8x8 size maze

        cout << "Maze:" << endl;
        mazeSolver.printMaze();

        cout << "\nDFS Solution:" << endl;
        if (mazeSolver.solveDFS()) {
            mazeSolver.printMaze();
            cout << "Maze solved." << endl;
        } else {
            cout << "Solution not found." << endl;
        }

        cout << "\nBFS Solution:" << endl;
        if (mazeSolver.solveBFS()) {
            mazeSolver.printMaze();
            cout << "Maze solved." << endl;
        } else {
            cout << "Solution not found." << endl;
        }

        cout << "Press 'R' to reset maze and solutions, or 'E' to exit: ";
        char choice;
        cin >> choice;

        if (choice == 'E' || choice == 'e') {
            exitProgram = true;
        }
    }

    return 0;
}
