#include <iomanip>
#include <iostream>

constexpr int kPrecision{1};

int main() {
  int groups;
  int format;
  if (!(std::cin >> groups >> format) || groups <= 0 ||
      (format != 1 && format != 2)) {
    return 0;
  }

  int*** marks = new int** [groups] {};
  int* students = new int[groups]{};
  int** counts = new int*[groups]{};
  bool valid{true};

  for (int group{0}; group < groups && valid; ++group) {
    if (!(std::cin >> students[group]) || students[group] <= 0) {
      valid = false;
      break;
    }
    marks[group] = new int*[students[group]]{};
    counts[group] = new int[students[group]]{};

    for (int student{0}; student < students[group] && valid; ++student) {
      int count;
      if (!(std::cin >> count) || count <= 0) {
        valid = false;
        break;
      }
      counts[group][student] = count;
      marks[group][student] = new int[count];

      void* buffer;
      if (format == 1) {
        buffer = new int[count];
      } else {
        buffer = new char[count];
      }

      for (int index{0}; index < count && valid; ++index) {
        if (format == 1) {
          int* numbers = static_cast<int*>(buffer);
          if (!(std::cin >> numbers[index]) || numbers[index] < 2 ||
              numbers[index] > 5) {
            valid = false;
          }
        } else {
          char* letters = static_cast<char*>(buffer);
          if (!(std::cin >> letters[index]) ||
              (letters[index] != 'A' && letters[index] != 'B' &&
               letters[index] != 'C' && letters[index] != 'F')) {
            valid = false;
          }
        }
      }

      for (int index{0}; index < count && valid; ++index) {
        if (format == 1) {
          marks[group][student][index] = static_cast<int*>(buffer)[index];
        } else {
          const char letter{static_cast<char*>(buffer)[index]};
          int mark{2};
          if (letter == 'A') {
            mark = 5;
          } else if (letter == 'B') {
            mark = 4;
          } else if (letter == 'C') {
            mark = 3;
          }
          marks[group][student][index] = mark;
        }
      }

      if (format == 1) {
        delete[] static_cast<int*>(buffer);
      } else {
        delete[] static_cast<char*>(buffer);
      }
    }
  }

  if (valid) {
    std::cout << std::fixed << std::setprecision(kPrecision);
    for (int group{0}; group < groups; ++group) {
      long long sum{0};
      long long count{0};
      for (int student{0}; student < students[group]; ++student) {
        for (int index{0}; index < counts[group][student]; ++index) {
          sum += marks[group][student][index];
          ++count;
        }
      }
      std::cout << static_cast<double>(sum) / count << '\n';
    }
  }

  for (int group{0}; group < groups; ++group) {
    if (marks[group] != nullptr) {
      for (int student{0}; student < students[group]; ++student) {
        delete[] marks[group][student];
      }
    }
    delete[] marks[group];
    delete[] counts[group];
  }
  delete[] marks;
  delete[] students;
  delete[] counts;
  return 0;
}
