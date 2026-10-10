#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int kCommandSize{16};
constexpr long long kMaxTotal{std::numeric_limits<long long>::max()};

void Deposit(long long& total) {
  long long amount;
  if (!(std::cin >> amount) || amount <= 0 || amount > kMaxTotal - total) {
    std::cout << "error\n";
    return;
  }
  total += amount;
}

void Withdraw(long long& total) {
  long long amount;
  if (!(std::cin >> amount) || amount <= 0 || amount > total) {
    std::cout << "error\n";
    return;
  }
  total -= amount;
}

void Balance(long long& total) { std::cout << total << '\n'; }

void Reset(long long& total) { total = 0; }

void Inc(long long& total) {
  if (total == kMaxTotal) {
    std::cout << "error\n";
    return;
  }
  ++total;
}

struct Command {
  const char* name;
  void (*action)(long long&);
};

int main() {
  const Command commands[]{
      {"deposit", Deposit}, {"withdraw", Withdraw}, {"balance", Balance},
      {"reset", Reset},     {"inc", Inc},
  };
  long long total{0};
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
