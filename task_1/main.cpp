#include <iomanip>
#include <iostream>

constexpr int kPrecision{1};

struct MinMax {
  int min;
  int max;
};

double FindAverage(const int* temps, int days) {
  long long sum{0};
  for (int day{0}; day < days; ++day) {
    sum += temps[day];
  }
  return static_cast<double>(sum) / days;
}

MinMax FindMinMax(const int* temps, int days) {
  MinMax result{temps[0], temps[0]};
  for (int day{1}; day < days; ++day) {
    if (temps[day] < result.min) {
      result.min = temps[day];
    }
    if (temps[day] > result.max) {
      result.max = temps[day];
    }
  }
  return result;
}

int CountColdDays(const int* temps, int days) {
  int count{0};
  for (int day{0}; day < days; ++day) {
    if (temps[day] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int days;
  if (!(std::cin >> days) || days <= 0) {
    return 0;
  }

  int* temps = new int[days];
  for (int day{0}; day < days; ++day) {
    if (!(std::cin >> temps[day])) {
      delete[] temps;
      return 0;
    }
  }

  const double average{FindAverage(temps, days)};
  const MinMax limits{FindMinMax(temps, days)};
  const int cold_days{CountColdDays(temps, days)};

  std::cout << std::fixed << std::setprecision(kPrecision);
  std::cout << average << '\n';
  std::cout << limits.min << ' ' << limits.max << '\n';
  std::cout << cold_days << '\n';

  delete[] temps;
  return 0;
}
