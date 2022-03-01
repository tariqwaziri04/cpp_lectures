#include <array>
#include <cstdio>

int main()
{
        std::array<int, 5> x = {1, 2, 3, 4, 5};
        for (int i = 0; i < x.size(); i += 1)
        {
                if (x[i] % 2 == 0) { std::printf("Even: x[%d] = %d\n", i, x[i]); }
                else { std::printf("Odd: x[%d] = %d\n", i, x[i]); }
        }

        // Task: Add the even numbers in the array `x`.
}