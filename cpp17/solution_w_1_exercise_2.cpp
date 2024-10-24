//
// Created by Ihab ABADI on 24/10/2024.
//

#include <iostream>
#include <variant>

struct Celsius {
    double value;
};

struct Fahrenheit {
    double value;
};

// Celsius -> Fahrenheit conversion function
Fahrenheit toFahrenheit(const Celsius& celsius) {
    return Fahrenheit{celsius.value * 9.0 / 5.0 + 32.0};
}

// Fahrenheit -> Celsius conversion function
Celsius toCelsius(const Fahrenheit& fahrenheit) {
    return Celsius{(fahrenheit.value - 32.0) * 5.0 / 9.0};
}
/*void convertAndPrint(const std::variant<Celsius, Fahrenheit>& temperature) {
    if  (std::holds_alternative<Celsius>(temperature)) {
        // Convert from Celsius to Fahrenheit
        const Celsius&  celsius = std::get<Celsius>(temperature);
        Fahrenheit f = toFahrenheit(celsius);
        std::cout << "Conversion: " << f.value << "°F" << std::endl;
    }
    else if  (std::holds_alternative<Fahrenheit>(temperature)) {
        // Convert from Celsius to Fahrenheit
        const Fahrenheit&  fahrenheit = std::get<Fahrenheit>(temperature);
        Celsius celsius = toCelsius(fahrenheit);
        std::cout << "Conversion: " << celsius.value << "°F" << std::endl;
    }
}*/

void convertAndPrint(const std::variant<Celsius, Fahrenheit>& temperature) {
    std::visit([](auto&& arg) {

        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Celsius>) {
            // Convert from Celsius to Fahrenheit
            Fahrenheit f = toFahrenheit(arg);
            std::cout << "Conversion: " << arg.value << "°C -> " << f.value << "°F" << std::endl;
        }
        else if constexpr (std::is_same_v<T, Fahrenheit>) {
            // Convert from Fahrenheit to Celsius
            Celsius c = toCelsius(arg);
            std::cout << "Conversion: " << arg.value << "°F -> " << c.value << "°C" << std::endl;
        } else {
            std::cout << "Other thinks" << '\n';
        }
    }, temperature);
}

int main() {
    std::variant<Celsius, Fahrenheit> tempC = Celsius{25.0};
    std::variant<Celsius, Fahrenheit> tempF = Fahrenheit{77.0};
    convertAndPrint(tempC);
    convertAndPrint(tempF);
    convertAndPrint(Celsius{37});


    return 0;
}