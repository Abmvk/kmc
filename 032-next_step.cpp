#include <iostream>

int square(int num) {
    return num * num;
}

int main() {
    int number = 5;
    int result = square(number);
    std::cout << "Het kwadraat van " << number << " is " << result << std::endl;
    return 0;
}
