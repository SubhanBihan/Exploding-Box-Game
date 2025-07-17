#include <algorithm>
#include <ranges>

#include "helpers.hpp"

int main () {
    unsigned total_rows, total_cols;

    std::cout << "Enter the number of rows (height) of the board: ";
    std::cin >> total_rows;

    std::cout << "Enter the number of columns of the board: ";
    std::cin >> total_cols;

    unsigned max_row = total_rows - 1, max_col = total_cols - 1;

    // Board specs:
    //      '-' represents empty space / air
    //      '#' represents a box
    //      '+' represents an obstacle
    //      '*' represents an explosion due to combination of a box and an obstacle - an intermediate state, should NEVER appear in Board Display
    std::vector<std::string> board(total_rows, std::string(total_cols, '-'));

    // Generate a random board
    RandomizeBoard(board);

    std::vector<std::pair<unsigned, unsigned>> boxes;                 // To track the positions of all current boxes
    std::vector<std::pair<unsigned, unsigned>> obstacles;             // To track the positions of all current obstacles

    for (unsigned row = 0U; row <= max_row; row++) {                  // Track the initial positions of boxes and obstacles
        for (unsigned col = 0U; col <= max_col; col++) {
            switch (board[row][col])
            {
                case '-':
                    break;
                case '#':
                    boxes.emplace_back(row, col);
                    break;
                case '+':
                    obstacles.emplace_back(row, col);
                    break;
                default:
                    break;
            }
        }
    }

    std::ranges::sort(boxes, [](const auto& box1, const auto& box2){ return box1.first > box2.first; });    // So that we move from bottom to top when iterating through 'boxes'

    bool state_change = false;                              // Tracks change of board state per turn

    do {
        DisplayBoard(board);

        state_change = false;

        for (auto &[row, col] : boxes) {                    // Box moves 1 space down if possible
            if (row < max_row && board[row + 1][col] != '#') {
                board[row][col] = '-';
                board[row + 1][col] = (board[row + 1][col] == '+') ? '*' : '#';

                row++;

                state_change = true;                        // If any box moves, state of board has changed
            }
        }

        for (auto it = obstacles.begin(); it != obstacles.end(); ) {
            const auto [row, col] = *it;

            if (board[row][col] == '*') {                   // 3-by-3 explosion, remove surrounding boxes
                board[row][col] = '#';                      // Temporary

                for (unsigned brow = std::max(0U, row - 1); brow <= std::min(max_row, row + 1); brow++) {
                    for (unsigned bcol = std::max(0U, col - 1); bcol <= std::min(max_col, col + 1); bcol++) {
                        if (board[brow][bcol] == '#') {
                            board[brow][bcol] = '-';
                            boxes.erase(std::remove(boxes.begin(), boxes.end(), std::make_pair(brow, bcol)), boxes.end());
                        }
                    }
                }

                it = obstacles.erase(it);                   // There's no longer an obstacle here
            }
            else it++;
        }

    } while (state_change);                                 // Continue until no change in (two consequtive) states

    return 0;
}