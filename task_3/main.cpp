#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int kRows{5};
constexpr int kCols{10};
constexpr int kCommandSize{16};

bool IsInside(int x, int y) {
    return x >= 0 && x < kCols && y >= 0 && y < kRows;
}

void Clear(char board[][kCols]) {
    for (int row{0}; row < kRows; ++row) {
        for (int col{0}; col < kCols; ++col) {
            board[row][col] = ' ';
        }
    }
}

bool Put(char board[][kCols], int x, int y, char symbol) {
    if (!IsInside(x, y)) {
        return false;
    }
    board[y][x] = symbol;
    return true;
}

bool Text(char board[][kCols], int x, int y, const char* word) {
    const int length{static_cast<int>(std::strlen(word))};
    if (!IsInside(x, y) || length == 0 || length > kCols - x) {
        return false;
    }
    for (int letter{0}; letter < length; ++letter) {
        Put(board, x + letter, y, word[letter]);
    }
    return true;
}

void Print(const char board[][kCols]) {
    for (int row{0}; row < kRows; ++row) {
        for (int col{0}; col < kCols; ++col) {
            std::cout << board[row][col];
        }
        std::cout << '\n';
    }
}

int main() {
    char board[kRows][kCols];
    Clear(board);
    char name[kCommandSize];

    while (std::cin >> std::setw(kCommandSize) >> name) {
        if (std::strcmp(name, "quit") == 0) {
            break;
        }

        if (std::strcmp(name, "clear") == 0) {
            Clear(board);
        } else if (std::strcmp(name, "put") == 0) {
            int x;
            int y;
            char symbol;
            if (!(std::cin >> x >> y >> symbol) || !Put(board, x, y, symbol)) {
                std::cout << "error\n";
            }
        } else if (std::strcmp(name, "text") == 0) {
            int x;
            int y;
            char word[kCols + 2];
            if (!(std::cin >> x >> y >> std::setw(kCols + 2) >> word) || !Text(board, x, y, word)) {
                std::cout << "error\n";
            }
        } else if (std::strcmp(name, "print") == 0) {
            Print(board);
        } else {
            std::cout << "error\n";
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
