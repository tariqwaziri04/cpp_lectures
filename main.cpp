#include <cstdio>
#include <array>

int main()
{
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    for (int i = 0; i < arr.size(); i += 1)
    {
        arr[i] *= 2;
        std::printf("arr[%d] = %d\n", i, arr[i]);
    }
}