#include <iostream>
#include <variant>

using namespace std;

typedef variant<int, double, string> myVariant;

void checkType(myVariant var){
    visit([](auto&& arg) {
        using T = decay_t<decltype(arg)>;
        cout << "The variable is of type ";
        if constexpr (is_same_v<T, int>) {
            cout << "integer.\n";
        } else if constexpr (is_same_v<T, double>) {
            cout << "double.\n";
        } else if constexpr (is_same_v<T, string>) {
            cout << "string.\n";
        }
    }, var);
}


int main(){
    myVariant test_var = 42;
    checkType(test_var);
}