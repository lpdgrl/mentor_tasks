#include <iostream>
#include <functional>
#include <bitset>

// 9. Функция-калькулятор принимает одну из четырех функций: 
// sum(double, double), 
// sub(double, double), div(double, double), mul(double, double), 
// аргументы, и вызывает функцию с аргументами. 
// Как сделать через указатели на функцию? 
// А как сделать в C++-парадигме через std::function?

double _sum(double, double);
double _sub(double, double);
double _div(double, double);
double _mul(double, double);

using PtrFuncCalc = double (* const)(double, double);
using StdFuncCalc = std::function<double(double, double)>;

double func_calc_ptr(PtrFuncCalc, double, double);
double func_calc_function(StdFuncCalc fn, double, double);

struct A {
    int x = 0;
    int y = 0;
};

int main() {
    std::cout << "Example is using ptr to func" << '\n';
    std::cout << "Sum: " << func_calc_ptr(&_sum, 10.0, 15.0) << '\n';
    std::cout << "Sub: " << func_calc_ptr(&_sub, 5.0, 3.0) << '\n';
    std::cout << "Mul: " << func_calc_ptr(&_mul, 5.0, 3.0) << '\n';
    std::cout << "Div: " << func_calc_ptr(&_div, 6.0, 3.0) << '\n';

    std::cout << "Example is using std::function" << '\n';
    std::cout << "Sum: " << func_calc_function(&_sum, 10.0, 15.0) << '\n';
    std::cout << "Sub: " << func_calc_function(&_sub, 5.0, 3.0) << '\n';
    std::cout << "Mul: " << func_calc_function(&_mul, 5.0, 3.0) << '\n';
    std::cout << "Div: " << func_calc_function(&_div, 6.0, 3.0) << '\n';

    using namespace std::placeholders;

    std::cout << "Example is using std::bind" << '\n';
    int k = 10;
    auto sum_ = std::bind(_sum, _1, k);
    std::cout << "Sum: " << sum_(2) << '\n';

    return 0;
}

double func_calc_function(StdFuncCalc fn, double num1, double num2) {
    return fn(num1, num2);
}

double func_calc_ptr(PtrFuncCalc pf, double num1, double num2) {
    return pf(num1, num2);
}

double _sum(double num1, double num2) {
    return num1 + num2;
}

double _sub(double num1, double num2) {
    return num1 - num2;
}

double _mul(double num1, double num2) {
    return num1 * num2;
}

double _div(double num1, double num2) {
    return num1 + num2;
}

