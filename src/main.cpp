#include <PmergeMe.hpp>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << RED "Error: Insufficient arguments\n" RESET
                  << "Purpose: Sort a sequence of positive integers using merge-insert sort\n"
                  << "Usage:   " << argv[0] << " <positive_integer_1> <positive_integer_2> [...]\n"
                  << "Example: " << argv[0] << " 3 5 9 7 4\n"
                  << "Note:    Requires at least 2 integers as input\n";
        return 1;
    }
    PmergeMe p;
    std::cout << "Before: ";
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << "\n";
    try
    {
        // p.timeSortVector(argc, argv);
        p.timeSortDeque(argc, argv);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << RED << e.what() << RESET << std::endl;
        return 1;
    }
    // p.sortVectorTest();
    p.sortDequeTest();
    return 0;
}