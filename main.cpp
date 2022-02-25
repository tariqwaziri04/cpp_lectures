#include <cstdio>
#include <optional>
#include <string_view>

struct Greeting
{
        static auto say() -> std::optional<std::string_view> { return {"Hello World\n"}; }
};

int main()
{
        if (const auto s = Greeting::say(); s) { std::printf("%s", s->data()); }
}