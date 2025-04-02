#include <functional>
#include <iostream>
#include <optional>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>


#include "factorial/factorial.h"
#include "prime/prime.h"

int main(int argc, const char** argv)
{

    CLI::App app{"My App"};

    std::optional<int> factorialNumberInput = 0;
    app.add_option("--factorial", factorialNumberInput, "Factorial to Compute");

    std::optional<int> primeNumberInput = 0;
    app.add_option("--prime", primeNumberInput, "Check if number is prime");


    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e)
    {
        return app.exit(e);
    }

    if (factorialNumberInput)
    {
        if (factorialNumberInput < 0)
        {
            std::cerr << "Cannot compute the factorial of a negative number"
                      << "\n";
        }

        const int fact = factorial::computeFact(factorialNumberInput.value());
        std::cout << "Factorial of  " << factorialNumberInput.value() << " is: " << fact << "\n";
    }

    // Prime
    if (primeNumberInput)
    {
        const bool prime = prime::isPrime(primeNumberInput.value());
        std::cout << primeNumberInput.value() << " is";
        if (!prime)
            std::cout << " not ";
        std::cout << " Prime"
                  << "\n";
    }


    return 0;
}
