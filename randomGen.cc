#include <iostream>
#include <random>
#include <chrono>
#include <string>

int main(int argc, char **argv)
{
    /* 
        usage: randomGen [randomLimit] [amount]
            - randomLimit: random generator upper limit
            - amount: amount of numbers generated
     */

    if(argc != 3) return 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed); // Default generator
    // To generate between 1 and randomLimit
    std::uniform_int_distribution<int> distro(1, std::stoi(argv[1]));

    for(auto i = 0; i < std::stoi(argv[2]); i++)
        std::cout << distro(gen) << std::endl;

    return 0;
}