#include <vector>
#include <deque>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <iterator>
#include <unordered_map>
#include <utility> // for std::pair

#define RED "\e[91m"
#define CYAN "\033[36m"
#define RESET "\e[0m"

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void timeSortVector(int argc, char *argv[]);
    void timeSortDeque(int argc, char *argv[]);
    void printVector(const std::vector<int> &vec);
    void printDeque(const std::deque<int> &lst);
    void sortVectorTest();
    void sortDequeTest();

private:
    void MergeInsertionSort(std::vector<int> &vec);
    void MergeInsertionSort(std::deque<int> &lst);

    std::vector<int> generatePowerSequence(size_t length);
    std::deque<int> generatePowerSequenceDeque(size_t length);

    std::vector<std::pair<int, int>> makePairs(const std::vector<int> &vec);
    std::deque<std::pair<int, int>> makePairs(const std::deque<int> &lst);

    std::vector<std::vector<int>> partition(std::vector<int> &nums, std::vector<int> &groupSizes);
    std::deque<std::deque<int>> partition(std::deque<int> &nums, std::deque<int> &groupSizes);

    void insertElementVector(int elementToInsert, const std::unordered_map<int, int> &reversePairMap);
    void insertElementDeque(int elementToInsert, const std::unordered_map<int, int> &reversePairMap);

    bool hasDuplicates(const std::vector<int> &vec);
    bool hasDuplicates(const std::deque<int> &lst);
    void printTime(const std::chrono::high_resolution_clock::duration &duration, int sequenceLen, const std::string &type);

    std::vector<int> sortedVec;
    std::vector<int> unsortedVec;

    std::deque<int> sortedDeque;
    std::deque<int> unsortedDeque;

    const std::vector<size_t> JACOBSTHAL_SEQUENCE = {
        2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766};

    const std::deque<size_t> JACOBSTHAL_SEQUENCE_DEQUE = {
        2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766};
};