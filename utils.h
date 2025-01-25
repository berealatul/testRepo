#ifndef UTILS
#define UTILS

#include <random>
#include <vector>
#include <iostream>
#include <type_traits> // For std::is_integral

template <class T>
T randomNumber(T low, T high)
{
    // static to avoid reseeding
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd()); // Mersenne Twister 19937 generator

    // constexpr for compile-time checks to improve clarity
    if constexpr (std::is_integral<T>::value)
    {
        // define a range [low, high]
        std::uniform_int_distribution<T> dist(low, high);
        return dist(gen);
    }
    else
    {
        /* template instantiation in C++ occurs even for code
           that is seemingly unreachable at runtime.
           This behavior is a common gotcha when working with if constexpr in templated code.
           Always ensure that invalid code for a particular template
           instantiation is excluded from compilation using if constexpr and else.
        */
        std::uniform_real_distribution<T> dist(low, high);
        return dist(gen);
    }
}

template <class T>
std::vector<T> randomArray(T low = 0, T high = 9, std::size_t length = 10)
{
    std::vector<T> arr;
    // use reserve when size is known and will fill it completely
    arr.reserve(length);
    for (std::size_t i = 0; i < length; ++i)
        arr.push_back(randomNumber<T>(low, high));
    return arr;
}

template <class T>
void printArray(const std::vector<T> &arr, const std::string &delimiter = ", ",
                const std::string &start = "[", const std::string &end = "]")
{
    std::cout << start;
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i];
        if (i < arr.size() - 1)
            std::cout << delimiter;
    }
    std::cout << end << '\n';
}

#endif // UTILS
