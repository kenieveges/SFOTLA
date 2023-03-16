#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <queue>
using namespace std;


// Define a struct for representing coordinates
struct Point {
    int row, col;
    Point(int row, int col) : row(row), col(col) {}
};

// Define a struct for representing a node in the search
struct Node {
    Point point;
    int distance;
    Node(Point point, int distance) : point(point), distance(distance) {}
};

// Define a function for finding the shortest path in the maze
vector<Point> findShortestPath(vector<vector<int>> maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Find the starting point
    Point start(0, 0);
    for (int i = 0; i < rows; i++) {
        if (maze[i][0] != 0) {
            start.row = i;
            break;
        }
    }

    // Find the ending point
    Point end(0, 0);
    for (int i = 0; i < rows; i++) {
        if (maze[i][cols - 1] != 0) {
            end.row = i;
            end.col = cols - 1;
            break;
        }
    }

    // Define a queue for the search
    queue<Node> q;

    // Add the starting point to the queue
    q.push(Node(start, 0));

    // Define a 2D array for keeping track of visited points
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Perform a breadth-first search
    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        Point point = node.point;
        int distance = node.distance;

        // Check if the current point is the ending point
        if (point.row == end.row && point.col == end.col) {
            vector<Point> path;
            while (point.row != start.row || point.col != start.col) {
                path.push_back(point);
                point = Point(point.row - 1, point.col);
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        // Check if the current point has been visited
        if (visited[point.row][point.col]) {
            continue;
        }
        visited[point.row][point.col] = true;

        // Add the neighboring points to the queue
        if (point.row > 0 && maze[point.row - 1][point.col] != 0) {
            q.push(Node(Point(point.row - 1, point.col), distance + 1));
        }
        if (point.row < rows - 1 && maze[point.row + 1][point.col] != 0) {
            q.push(Node(Point(point.row + 1, point.col), distance + 1));
        }
        if (point.col > 0 && maze[point.row][point.col - 1] != 0) {
            q.push(Node(Point(point.row, point.col - 1), distance + 1));
        }
        if (point.col < cols - 1 && maze[point.row][point.col + 1] != 0) {
            q.push(Node(Point(point.row, point.col + 1), distance + 1));
        }
    }

    // If the ending point was not found, return an empty path
    return vector<Point>();
}

// Define a function for generating a random maze of a given size
vector<vector<int>> generateMaze(int rows, int cols) {
    // Define a 2D array for the maze
    vector<vector<int>> maze(rows, vector<int>(cols, 0));

    // Define a random number generator
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(0, 1);

    // Fill the maze with random values ensure that the starting and ending points are open.
    // Also ensure that the maze has a solution, i.e. continuously open cells from the starting
    // point to the ending point.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                maze[i][j] = 1;
            } else {
                maze[i][j] = distribution(generator);
            }
        }
    }

    // Return the maze
    return maze;
}

// Define a function for exporting a maze to a file, use txt format.
void exportMaze(vector<vector<int>> maze, string filename) {
    ofstream file(filename);
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            file << maze[i][j];
        }
        file << endl;
    }
    file.close();
}

// Function for exporting shortest path to a file, use txt format.
void exportPath(vector<Point> path, string filename) {
    ofstream file(filename);
    for (int i = 0; i < path.size(); i++) {
        file << "(" << path[i].row << ", " << path[i].col << ")" << endl;
    }
    file.close();
}

// Main function for testing.
int main(){
    // Generate a random maze
    vector<vector<int>> maze = generateMaze(10, 10);

    // Export the maze to a file
    exportMaze(maze, "array.txt");

    // Find the shortest path in the maze
    vector<Point> path = findShortestPath(maze);

    // Export the path to a file
    exportPath(path, "path.txt");

    return 0;
}