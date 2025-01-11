//别人打印菱形星图代码
#include <iostream>

int main51() {
    int n, c, k, space = 1;

    std::cout << "Enter number of rows (half of the diamond) : ";
    std::cin >> n;

    space = n - 1;

    for (k = 1; k <= n; k++) {
        for (c = 1; c <= space; c++)
            std::cout << " ";

        space--;

        for (c = 1; c <= 2 * k - 1; c++)
            std::cout << "*";

        std::cout << std::endl;
    }

    space = 1;

    for (k = 1; k <= n - 1; k++) {
        for (c = 1; c <= space; c++)
            std::cout << " ";

        space++;

        for (c = 1; c <= 2 * (n - k) - 1; c++)
            std::cout << "*";

        std::cout << std::endl;
    }

	system("pause");
    return 0;
}