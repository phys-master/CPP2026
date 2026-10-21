#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int kCommandSize{16};

bool ReadAmount(int& amount) {
  while (std::cin.peek() == ' ' || std::cin.peek() == '\t' ||
         std::cin.peek() == '\r') {
    std::cin.get();
  }
  return std::cin.peek() != '\n' && (std::cin >> amount);
}

void Deposit(int& total) {
  int amount;
  if (!ReadAmount(amount) || amount <= 0) {
    std::cout << "error\n";
    return;
  }
  total += amount;
}

void Withdraw(int& total) {
  int amount;
  if (!ReadAmount(amount) || amount <= 0 || amount > total) {
    std::cout << "error\n";
    return;
  }
  total -= amount;
}

void Balance(int& total) {
  std::cout << total << '\n';
}

void Reset(int& total) {
  total = 0;
}

void Inc(int& total) {
  ++total;
}

struct Command {
  const char* name;
  void (*action)(int&);
};

int main() {
  const Command commands[]{
    {"deposit", Deposit},
    {"withdraw", Withdraw},
    {"balance", Balance},
    {"reset", Reset},
    {"inc", Inc},
  };
  int total{0};
  char name[kCommandSize];

  while (std::cin >> std::setw(kCommandSize) >> name) {
    if (std::strcmp(name, "stop") == 0) {
      break;
    }

    bool found{false};
    for (const Command& command : commands) {
      if (std::strcmp(name, command.name) == 0) {
        command.action(total);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "error\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
