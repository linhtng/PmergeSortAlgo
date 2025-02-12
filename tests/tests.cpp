#include <PmergeMe.hpp>
#include <random>
#include <cassert>
#include <set>

struct TestResult
{
    std::string testName;
    bool passed;
    std::string details;
};

std::vector<TestResult> testResults;

void printTestSummary()
{
    int passedTests = 0;
    std::cout << "\n=== Test Summary ===\n";

    for (const auto &result : testResults)
    {
        std::cout << (result.passed ? "✅ " : "❌ ")
                  << result.testName << ": "
                  << (result.passed ? "PASSED" : "FAILED")
                  << "\n";
        if (!result.passed)
        {
            std::cout << "   Details: " << result.details << "\n";
        }
        if (result.passed)
            passedTests++;
    }

    std::cout << "\nTotal: " << testResults.size() << " tests\n"
              << "Passed: " << passedTests << "\n"
              << "Failed: " << testResults.size() - passedTests << "\n";
}

TestResult testSmallSequence()
{
    try
    {
        const char *argv[] = {"./PmergeMe", "3", "5", "9", "7", "4"};
        int argc = 6;

        PmergeMe p;
        std::cout << "Before: ";
        for (int i = 1; i < argc; i++)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << "\n";

        p.timeSortVector(argc, const_cast<char **>(argv));
        p.timeSortDeque(argc, const_cast<char **>(argv));
        p.sortVectorTest();
        p.sortDequeTest();
        return {"Small Sequence Sort", true, "5 numbers sorted successfully"};
    }
    catch (const std::exception &e)
    {
        return {"Small Sequence Sort", false, e.what()};
    }
}

TestResult testLargeSequence()
{
    try
    {
        std::vector<std::string> numbers;
        numbers.push_back("./PmergeMe");

        // Generate unique random numbers
        std::set<int> uniqueNumbers;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100000);

        // Generate until we have 3000 unique numbers
        while (uniqueNumbers.size() < 3000)
        {
            uniqueNumbers.insert(dis(gen));
        }

        // Convert to strings and add to numbers vector
        for (const int &num : uniqueNumbers)
        {
            numbers.push_back(std::to_string(num));
        }

        std::vector<const char *> argv;
        for (const auto &num : numbers)
        {
            argv.push_back(num.c_str());
        }

        PmergeMe p;
        p.timeSortVector(argv.size(), const_cast<char **>(argv.data()));
        p.timeSortDeque(argv.size(), const_cast<char **>(argv.data()));
        p.sortVectorTest();
        p.sortDequeTest();
        return {"Large Sequence Sort", true, "3000 unique random numbers sorted successfully"};
    }
    catch (const std::exception &e)
    {
        return {"Large Sequence Sort", false, e.what()};
    }
}

TestResult testNegativeInput()
{
    try
    {
        const char *argv[] = {"./PmergeMe", "-1", "2"};
        int argc = 3;

        PmergeMe p;
        try
        {
            p.timeSortVector(argc, const_cast<char **>(argv));
            assert(false && "Should have thrown an exception");
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << RED << e.what() << RESET << std::endl;
        }
        return {"Negative Input Test", true, "Exception thrown as expected"};
    }
    catch (const std::exception &e)
    {
        return {"Negative Input Test", false, e.what()};
    }
}

TestResult testLargerRandomSequence()
{
    try
    {
        std::vector<std::string> numbers;
        numbers.push_back("./PmergeMe");

        // Generate unique random numbers
        std::set<int> uniqueNumbers;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000000);

        // Generate until we have 3000 unique numbers
        while (uniqueNumbers.size() < 3000)
        {
            uniqueNumbers.insert(dis(gen));
        }

        // Convert to strings and add to numbers vector
        for (const int &num : uniqueNumbers)
        {
            numbers.push_back(std::to_string(num));
        }

        std::vector<const char *> argv;
        for (const auto &num : numbers)
        {
            argv.push_back(num.c_str());
        }

        PmergeMe p;
        p.timeSortVector(argv.size(), const_cast<char **>(argv.data()));
        p.timeSortDeque(argv.size(), const_cast<char **>(argv.data()));
        p.sortVectorTest();
        p.sortDequeTest();
        return {"Larger Range Large Sequence Sort", true, "3000 unique random numbers sorted successfully"};
    }
    catch (const std::exception &e)
    {
        return {"Larger Range Large Sequence Sort", false, e.what()};
    }
}

int main()
{
    testResults.push_back(testSmallSequence());
    testResults.push_back(testLargeSequence());
    testResults.push_back(testNegativeInput());
    testResults.push_back(testLargerRandomSequence());

    printTestSummary();

    return 0;
}