#include <iostream>
#include <optional>
#include <variant>
#include <filesystem>
#include "config.h";

// 1. Inline variable (C++17)
//inline const int global_value = 42;

// 2. if constexpr (C++17)
template <int N>
void checkValue() {
    if constexpr (N > 10) {
        std::cout << "N is greater than 10." << std::endl;
    } else {
        std::cout << "N is less than or equal to 10." << std::endl;
    }
}

template<typename T>
void withOptional(std::optional<T> element) {
    if (element) {
        std::cout << "Optional contains: " << *element << '\n';
    } else {
        std::cout << "Optional is empty.\n";
    }
}

std::optional<int> myOptional = 34;

void withVariant(std::variant<int, double, std::string> element) {
    /*if(std::holds_alternative<int>(element)) {
        int value = std::get<int>(element);
        std::cout << "Value is Int " <<  value << '\n';
    }
    else if(std::holds_alternative<std::string>(element)) {
        std::string value = std::get<std::string>(element);
        std::cout << "Value is string " <<  value << '\n';
    }*/
    //...

    /*if(auto intPtr = std::get_if<int>(&element)) {
        std::cout << "Value is Int " <<  *intPtr << '\n';
    } else if (auto doublePtr = std::get_if<double>(&element)) {
        std::cout << "Variant contains (via std::get_if<double>): " << *doublePtr << '\n';
    } else if (auto stringPtr = std::get_if<std::string>(&element)) {
        std::cout << "Variant contains (via std::get_if<std::string>): " << *stringPtr << '\n';
    }*/

    std::visit([](auto&& arg) {
        std::cout << "Variant contains (via std::visit): " << arg << '\n';

        // Type checking using traits
        if constexpr (std::is_same_v<decltype(arg), int>) {
            std::cout << "The type of the variant value is int.\n";
        } else if constexpr (std::is_same_v<decltype(arg), double>) {
            std::cout << "The type of the variant value is double.\n";
        } else if constexpr (std::is_same_v<decltype(arg), std::string>) {
            std::cout << "The type of the variant value is std::string.\n";
        }
    }, element);

}

// 5. Fold expressions (C++17)
auto sum(auto... numbers) {
    constexpr std::size_t size = sizeof...(numbers);
    std::cout << "Number of elements: " << size << '\n';
    return (... + numbers); // Fold expression
}

// 6. Structured bindings (C++17)
void structuredBinding() {
    std::tuple<int, double, std::string> myTuple = {1, 3.14, "C++17"};
    auto [myInt, myDouble, myString] = myTuple;
    std::cout << "myInt: " << myInt << ", myDouble: " << myDouble << ", myString: " << myString << '\n';
}


// 7. std::filesystem (C++17)
void checkFileSystem() {
    std::filesystem::path path = "/tmp/test.txt";
    if (!std::filesystem::exists(path)) {
        std::cout << path << " does not exist.\n";
    }
}

using namespace  std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    cout << global_value << '\n';

    // Demo 1: if constexpr
    checkValue<5>();  // N = 5, so the second branch runs
    checkValue<15>(); // N = 15, so the first branch runs

    withOptional(myOptional);


    // Demo 3: std::variant with additional functions
    std::variant<int, double, std::string> element = "C++ 17 is cool !";
    withVariant(element);
    return 0;
}
