#include <iomanip>
#include <iostream>

int main() {
    int n{0};
    std::cin >> n;
    int a[n];
    float mid{0};
    for (int& x : a) {
        std::cin >> x;
        mid += (float)(x);
    }
    mid /= n;
    int min{0};
    int max{0};
    int count{0};
    for (int i = 0; i < n; ++i) {
        if (a[i] < a[min]) {
            min = i;
        }
        if (a[i] > a[max]) {
            max = i;
        }
        if (a[i] < 0) {
            ++count;
        }
    }
    std::cout << std::fixed << std::setprecision(1);
    std::cout << mid << '\n';
    std::cout << a[min] << ' ' << a[max] << '\n';
    std::cout << count << '\n';
    delete a;
    return 0;
}
