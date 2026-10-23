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

bool HasArgument() {
  while (std::cin.peek() == ' ' || std::cin.peek() == '\t' || std::cin.peek() == '\r') {
    std::cin.get();
  }
  return std::cin.peek() != '\n' && std::cin.good();
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
  const int length = std::strlen(word);
  if (!IsInside(x, y) || length > kCols - x) {
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
      bool read = HasArgument() && (std::cin >> x);
      read = read && HasArgument() && (std::cin >> y);
      read = read && HasArgument() && (std::cin >> symbol);
      if (!read || !Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(name, "text") == 0) {
      int x;
      int y;
      char word[kCols + 1];
      bool read = HasArgument() && (std::cin >> x);
      read = read && HasArgument() && (std::cin >> y);
      read = read && HasArgument() && (std::cin >> std::setw(kCols + 1) >> word);
      if (!read || !Text(board, x, y, word)) {
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
