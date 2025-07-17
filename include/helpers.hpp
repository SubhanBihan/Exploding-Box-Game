#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <random>

void DisplayBoard(const std::vector<std::string>& board) {
    for (const auto& row : board) {
        for (const auto& col : row) {
            std::cout << col << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}

void RandomizeBoard(std::vector<std::string>& board) {
    std::mt19937 rng(std::random_device{}());

    static const std::string charset = "-#+";
    std::uniform_int_distribution<unsigned> dist(0, charset.size() - 1);

    for (auto &row : board) {
        for (auto &cell : row) {
            cell = charset[dist(rng)];
        }
    }

}