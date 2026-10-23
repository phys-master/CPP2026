#include <iostream>

int main() {
  int groups{0};
  int*** marks{nullptr};
  int* students{nullptr};
  int** counts{nullptr};
  void* selected{nullptr};
  int command;

  while (std::cin >> command && command != 0) {
    int group{-1};
    int student{-1};
    for (int index{0}; index < groups; ++index) {
      if (selected == marks[index]) {
        group = index;
      }
      for (int person{0}; person < students[index]; ++person) {
        if (selected == marks[index][person]) {
          group = index;
          student = person;
        }
      }
    }

    if (command == 1) {
      int*** new_marks = new int**[groups + 1];
      int* new_students = new int[groups + 1];
      int** new_counts = new int*[groups + 1];
      for (int index{0}; index < groups; ++index) {
        new_marks[index] = marks[index];
        new_students[index] = students[index];
        new_counts[index] = counts[index];
      }
      new_marks[groups] = new int*[1]{};
      new_students[groups] = 0;
      new_counts[groups] = nullptr;
      delete[] marks;
      delete[] students;
      delete[] counts;
      marks = new_marks;
      students = new_students;
      counts = new_counts;
      selected = marks[groups];
      ++groups;
      std::cout << "group " << groups << '\n';
    } else if (command == 2) {
      if (group == -1) {
        std::cout << "error\n";
        continue;
      }
      int** new_marks = new int*[students[group] + 1];
      int* new_counts = new int[students[group] + 1];
      for (int index{0}; index < students[group]; ++index) {
        new_marks[index] = marks[group][index];
        new_counts[index] = counts[group][index];
      }
      new_marks[students[group]] = new int[1]{};
      new_counts[students[group]] = 0;
      delete[] marks[group];
      delete[] counts[group];
      marks[group] = new_marks;
      counts[group] = new_counts;
      selected = marks[group][students[group]];
      ++students[group];
      std::cout << "student " << students[group] << '\n';
    } else if (command == 3) {
      if (!(std::cin >> group)) {
        break;
      }
      if (group < 1 || group > groups) {
        std::cout << "error\n";
        continue;
      }
      selected = marks[group - 1];
    } else if (command == 4) {
      if (!(std::cin >> group >> student)) {
        break;
      }
      if (group < 1 || group > groups || student < 1 || student > students[group - 1]) {
        std::cout << "error\n";
        continue;
      }
      selected = marks[group - 1][student - 1];
    } else if (command == 5) {
      int mark;
      if (!(std::cin >> mark)) {
        break;
      }
      if (student == -1 || mark < 2 || mark > 5) {
        std::cout << "error\n";
        continue;
      }
      const int count{counts[group][student]};
      int* new_marks = new int[count + 1];
      for (int index{0}; index < count; ++index) {
        new_marks[index] = marks[group][student][index];
      }
      new_marks[count] = mark;
      delete[] marks[group][student];
      marks[group][student] = new_marks;
      ++counts[group][student];
      selected = marks[group][student];
    } else if (command == 6) {
      for (int index{0}; index < groups; ++index) {
        std::cout << "group " << index + 1 << '\n';
        for (int person{0}; person < students[index]; ++person) {
          std::cout << "student " << person + 1 << ':';
          for (int grade{0}; grade < counts[index][person]; ++grade) {
            std::cout << ' ' << marks[index][person][grade];
          }
          std::cout << '\n';
        }
      }
    } else {
      std::cout << "error\n";
    }
  }

  for (int group{0}; group < groups; ++group) {
    for (int student{0}; student < students[group]; ++student) {
      delete[] marks[group][student];
    }
    delete[] marks[group];
    delete[] counts[group];
  }
  delete[] marks;
  delete[] students;
  delete[] counts;
  return 0;
}
