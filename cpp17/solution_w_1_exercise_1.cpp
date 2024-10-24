
#include <variant>
#include <string>
#include <iostream>

using myVariantType = std::variant<int, double, std::string>;
using namespace std;
void printTypeHeldInVariant(myVariantType var)
{
    if (holds_alternative<std::string>(var))
    {
        std::cout << "Variant holds the string: " << get<std::string>(var) << "\n";
    }
    else if (holds_alternative<double>(var))
    {
        std::cout << "Variant holds the double: " << get<double>(var) << "\n";
    }
    else if (holds_alternative<int>(var))
    {
        std::cout << "Variant holds the int: " << get<int>(var) << "\n";
    } else {
        std::cout << "Unknown type" << "\n";
    }
}

template<typename T>
void displayMessage(const T& value) {
    if constexpr (std::is_same_v<T, int>){
        std::cout << "It's an integer: " << value << std::endl;
    }else if constexpr (std::is_same_v<T, double>) {
        std::cout << "It's a double: " << value << std::endl;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "It's a string: " << value << std::endl;
    } else {
        std::cout << "Unknown type." << std::endl;
    }
}

int main() {
    int value;

    value = 10;

    printTypeHeldInVariant(value);

    myVariantType element;
    element = "Some string";
    std::visit([](auto&& args) {
        displayMessage(args);
        }, element);
}