// cpp_physics_experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main() {
    std::cout << "Hello World!\n" << std::endl;

    int fib1 = 1;
    int fib2 = 1;
    int fib3;

    for (int i = 0; i < 10; i++) {
        std::cout << "Fibonacci value:" << fib1 << std::endl;
        fib3 = fib1;
        fib1 = fib1 + fib2;
        fib2 = fib3;
    }

    return 0;
}