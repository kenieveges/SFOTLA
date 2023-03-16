#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

int main() {
    const int rows = 5;
    const int cols = 5;

    // Create a 2D array with random 1s and 0s
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> uni(0, 1);
    int arr[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = uni(rng);
        }
    }

    // Ensure a continuous path of 1s from the first column to the last column
    for (int i = 0; i < rows; i++) {
        if (arr[i][0] == 1) {
            arr[i][0] = 0;
            arr[i][1] = 1;
        }
        if (arr[i][cols - 1] == 1) {
            arr[i][cols - 1] = 0;
            arr[i][cols - 2] = 1;
        }
    }
    for (int j = 0; j < cols; j++) {
        if (arr[0][j] == 1) {
            arr[0][j] = 0;
            arr[1][j] = 1;
        }
        if (arr[rows - 1][j] == 1) {
            arr[rows - 1][j] = 0;
            arr[rows - 2][j] = 1;
        }
    }

    // Ensure multiple continuous paths of 1s from the first column to the last column
    bool connected = false;
    while (!connected) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr[i][j] = uni(rng);
            }
        }
        for (int i = 0; i < rows; i++) {
            if (arr[i][0] == 1) {
                arr[i][0] = 0;
                arr[i][1] = 1;
            }
            if (arr[i][cols - 1] == 1) {
                arr[i][cols - 1] = 0;
                arr[i][cols - 2] = 1;
            }
        }
        for (int j = 0; j < cols; j++) {
            if (arr[0][j] == 1) {
                arr[0][j] = 0;
                arr[1][j] = 1;
            }
            if (arr[rows - 1][j] == 1) {
                arr[rows - 1][j] = 0;
                arr[rows - 2][j] = 1;
            }
        }

        bool visited[rows][cols] = { false };
        vector<vector<pair<int, int>>> paths;
        for (int i = 0; i < rows; i++) {
            if (arr[i][0] == 1 && !visited[i][0]) {
                vector<pair<int, int>> path;
                vector<pair<int, int>> stack = { {i, 0} };
                while (!stack.empty()) {
                    int x = stack.back().first