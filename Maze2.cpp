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

public:
    MazeSolver(int rows, int cols) : rows(rows), cols(cols) {
        maze = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            maze[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                maze[i][j] = rand() % 2; // 0 or 1
            }
        }
        // Başlangıç noktasını sol üst köşe, bitiş noktasını sağ alt köşe olarak ayarla
        start = make_pair(0, 0);
        end = make_pair(rows - 1, cols - 1);

        // Labirentin içinde geçilebilir yol oluştur
        maze[start.first][start.second] = 0;
        maze[end.first][end.second] = 0;
    }

    void printMaze() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (maze[i][j] == 1 ? "#" : ".");
            }
            cout << endl;
        }
    }

    bool solveDFS(pair<int, int> current = make_pair(0, 0)) {
        int **visited = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            visited[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                visited[i][j] = 0;
            }
        }

        if (dfsUtil(current.first, current.second, visited)) {
            return true;
        }
        return false;
    }

    bool dfsUtil(int x, int y, int **visited) {
        if (x == end.first && y == end.second) {
            return true;
        }

        visited[x][y] = 1;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visited[nx][ny]) {
                if (dfsUtil(nx, ny, visited)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool solveBFS() {
        bool **visited = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; ++j) {
                visited[i][j] = false;
            }
        }

        queue<pair<int, int>> q;
        q.push(start);

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();

            if (current == end) {
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
        }
        delete[] maze;
    }
};

int main() {
    srand(time(NULL));
    MazeSolver mazeSolver(5, 5); // 5x5 size maze
    cout << "Maze:" << endl;
    mazeSolver.printMaze();

    cout << "\nDFS solution:" << endl;
    if (mazeSolver.solveDFS()) {
        cout << "Maze solved." << endl;
    } else {
        cout << "Solution not found." << endl;
    }

    cout << "\nBFS solution:" << endl;
    if (mazeSolver.solveBFS()) {
        cout << "Maze solved." << endl;
    } else {
        cout << "Solution not found." << endl;
    }

    return 0;
}
