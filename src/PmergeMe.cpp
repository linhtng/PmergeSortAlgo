#include <PmergeMe.hpp>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::printVector(const std::vector<int> &vec)
{
    for (const int &element : vec)
    {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

std::vector<int> PmergeMe::generatePowerSequence(int length)
{
    std::vector<int> sequence;

    int power = 2;
    int sum = 0;
    for (int i = 2; i <= length; i++)
    {
        sequence.push_back(power);
        sum += power;
        if (sum > length)
            break;
        power = std::pow(2, i) - power;
    }

    return sequence;
}

std::deque<int> PmergeMe::generatePowerSequenceDeque(int length)
{
    std::deque<int> sequence;

    int power = 2;
    int sum = 0;
    for (int i = 2; i <= length; i++)
    {
        sequence.push_back(power);
        sum += power;
        if (sum > length)
            break;
        power = std::pow(2, i) - power;
    }

    return sequence;
}

std::vector<std::pair<int, int>> PmergeMe::makePairs(const std::vector<int> &vec)
{
    std::vector<std::pair<int, int>> pairs;
    for (size_t i = 0; i < vec.size() - 1; i += 2)
    {
        std::pair<int, int> pair = std::minmax(vec[i], vec[i + 1]);
        pairs.push_back(pair);
    }
    return pairs;
}

std::vector<std::vector<int>> PmergeMe::partition(std::vector<int> &nums, std::vector<int> &groupSizes)
{
    std::vector<std::vector<int>> partitions;
    int numSize = nums.size();
    int start = 0;
    for (int size : groupSizes)
    {
        int end = start + size;
        if (end >= numSize)
            end = numSize;
        std::vector<int> partition(nums.begin() + start, nums.begin() + end);
        std::reverse(partition.begin(), partition.end());
        partitions.push_back(partition);
        start += size;
    }
    // std::cout << "Partition start: " << '\n';
    // for (const auto &sub_vector : partitions)
    // {
    //     printVector(sub_vector);
    //     std::cout << "Partition done" << '\n';
    // }
    return partitions;
}

void PmergeMe::MergeInsertionSort(std::vector<int> &vec)
{
    // Step 1+2: Group the elements into pairs and perform comparisons to determine the larger element in each pair
    if (vec.size() <= 1)
        return;
    bool oddSize = false;
    int lastElement = 0;
    if (vec.size() % 2 != 0)
    {
        oddSize = true;
        lastElement = vec.back();
        vec.pop_back(); // Remove the last element
    }
    std::vector<std::pair<int, int>> paired = makePairs(vec);

    /* Step 3: Recursively sort the larger elements and create a sorted sequence
    of larger elements in ascending order */
    sorted.clear();
    for (const std::pair<int, int> &pair : paired)
    {
        sorted.push_back(pair.second);
    }
    // Create a map from the pairs
    std::unordered_map<int, int> pairMap;
    for (const std::pair<int, int> &pair : paired)
    {
        pairMap[pair.second] = pair.first;
    }
    MergeInsertionSort(sorted);
    unsorted.clear();
    if (paired.size() > 1)
    {
        for (const int &element : sorted) // complexity O(n)
        {
            std::unordered_map<int, int>::iterator it = pairMap.find(element);
            if (it != pairMap.end())
                unsorted.push_back(it->second);
        }
    }
    else
    {
        unsorted.push_back(paired.front().first);
    }
    if (oddSize)
        unsorted.push_back(lastElement);
    // std::cout << "Sorted atfer step 1 - 3: \n";
    // printVector(sorted);
    // std::cout << "Unsorted: \n";
    // printVector(unsorted);

    // Step 4: Insert the element paired with the smallest element at the start of the sorted sequence
    sorted.insert(sorted.begin(), unsorted.front());
    unsorted.erase(unsorted.begin());
    // std::cout << "[Vector] Sorted after step 4: \n";
    // printVector(sorted);
    // std::cout << "Unsorted: \n";
    // printVector(unsorted);

    /*
    Step 5 : Partition the unsorted elems into groups with contiguous indexes.
    The sums of sizes of every two adjacent groups form a sequence of powers of two
    */
    if (unsorted.size() > 1)
    {
        std::vector<int> groupSizes = generatePowerSequence(unsorted.size());
        // std::cout << "Groups'sized generated so as the sums of sizes of every two adjacent groups form a sequence of powers of two: \n";
        // printVector(groupSizes);
        // std::cout << "Unsorted in groups: \n";
        std::vector<std::vector<int>> orderToInsert = partition(unsorted, groupSizes);
        // Step 6: Insert the remaining elements into the sorted sequence using binary search
        for (const std::vector<int> &uninsertedGroup : orderToInsert)
        {
            for (const int &element : uninsertedGroup)
            {
                sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), element), element);
            }
        }
    }
    else if (unsorted.size() == 1)
    {
        int elemToInsert = unsorted.front();
        sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), elemToInsert), elemToInsert);
    }
}

bool PmergeMe::hasDuplicates(const std::vector<int> &vec)
{
    std::unordered_set<int> set(vec.begin(), vec.end());
    return set.size() != vec.size();
}

void PmergeMe::printTime(const std::chrono::high_resolution_clock::duration &duration, int sequenceLen, const std::string &type)
{
    long long time_in_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    std::cout << "Time to process a range of " << sequenceLen << " elements with "
              << type << ": " << time_in_us << " us\n";
}

void PmergeMe::timeSortVector(int argc, char *argv[])
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec;
    for (int i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        if (!std::all_of(input.begin(), input.end(), ::isdigit))
        {
            throw std::invalid_argument("Error. Input must be positive integers");
        }
        try
        {
            int num = std::stoi(input);
            vec.push_back(num);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << RED "Error. Number out of range: " << input << std::endl
                      << RESET;
            return;
        }
    }
    MergeInsertionSort(vec);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "After: ";
    printVector(sorted);
    printTime(end - start, argc - 1, "std::vector");
}

void PmergeMe::printDeque(const std::deque<int> &dequ)
{
    for (const int &element : dequ)
    {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

std::deque<std::pair<int, int>> PmergeMe::makePairs(const std::deque<int> &dequ)
{
    std::deque<std::pair<int, int>> pairs;
    for (size_t i = 0; i < dequ.size() - 1; i += 2)
    {
        std::pair<int, int> pair = std::minmax(dequ[i], dequ[i + 1]);
        pairs.push_back(pair);
    }
    return pairs;
}

std::deque<std::deque<int>> PmergeMe::partition(std::deque<int> &nums, std::deque<int> &groupSizes)
{
    std::deque<std::deque<int>> partitions;
    int start = 0;
    int numSize = nums.size();
    for (int size : groupSizes)
    {
        int end = start + size;
        if (end >= numSize)
            end = numSize;
        std::deque<int> partition(nums.begin() + start, nums.begin() + end);
        std::reverse(partition.begin(), partition.end());
        partitions.push_back(partition);
        start += size;
    }
    return partitions;
}

void PmergeMe::MergeInsertionSort(std::deque<int> &dequ)
{
    // Step 1+2: Group the elements into pairs and perform comparisons to determine the larger element in each pair
    // std::cout << "Dequ: \n";
    // printDeque(dequ);
    if (dequ.size() <= 1)
        return;
    bool oddSize = false;
    int lastElement = 0;
    if (dequ.size() % 2 != 0)
    {
        oddSize = true;
        lastElement = dequ.back();
        dequ.pop_back(); // Remove the last element
    }
    std::deque<std::pair<int, int>> paired = makePairs(dequ);
    /* Step 3: Recursively sort the larger elements
    and create a sorted sequence of larger elements in ascending order
    */
    sortedDeque.clear();
    for (const std::pair<int, int> &pair : paired)
    {
        sortedDeque.push_back(pair.second);
    }
    /* Create a map from the pairs so that we can identify which smaller elem
    that paired with the larger and push them to unsorted chain in corresponding order
    */
    std::unordered_map<int, int> pairMap;
    for (const std::pair<int, int> &pair : paired)
    {
        pairMap[pair.second] = pair.first;
    }
    MergeInsertionSort(sortedDeque);
    unsortedDeque.clear();
    if (paired.size() > 1)
    {
        for (const int &element : sortedDeque) // complexity O(n)
        {
            std::unordered_map<int, int>::iterator it = pairMap.find(element);
            if (it != pairMap.end())
                unsortedDeque.push_back(it->second);
        }
    }
    else
    {
        unsortedDeque.push_back(paired.front().first);
    }
    if (oddSize)
        unsortedDeque.push_back(lastElement);
    // std::cout << "Sorted after step 1 - 3: \n";
    // printDeque(sortedDeque);
    // std::cout << "Unsorted: \n";
    // printDeque(unsortedDeque);

    // Step 4: Insert the element paired with the smallest element at the start of the sorted sequence
    sortedDeque.insert(sortedDeque.begin(), unsortedDeque.front());
    unsortedDeque.erase(unsortedDeque.begin());
    // std::cout << "[deque] Sorted after step 4: \n";
    // printDeque(sortedDeque);
    // std::cout << "Unsorted: \n";
    // printDeque(unsortedDeque);

    /*
    Step 5 : Partition the unsorted elems into groups with contiguous indexes.
    The sums of sizes of every two adjacent groups form a sequence of powers of two
    */
    if (unsortedDeque.size() > 1)
    {
        std::deque<int> groupSizes = generatePowerSequenceDeque(unsortedDeque.size());
        // printdeque(groupSizes);
        // std::cout << "Unsorted in partitioned groups: \n";
        std::deque<std::deque<int>> orderToInsert = partition(unsortedDeque, groupSizes);

        /*
        Step 6: Insert the remaining elements into the sorted sequence using binary search
        First, find the length of the subsequence to insert the element into
        As we are inserting in order y_4, y_3, y_6, y_5, y_12, y_11, y_10, y_9, y_8, y_7, y_22, y_21...
        The subsequence length is to insert will be up to but not including x_i.
        We then perform a binary search on that subsequence to find the location to insert the element.
        */
        for (const std::deque<int> &uninsertedGroup : orderToInsert)
        {
            for (const int &element : uninsertedGroup)
            {
                sortedDeque.insert(std::lower_bound(sortedDeque.begin(), sortedDeque.end(), element), element);
            }
        }
    }
    else if (unsortedDeque.size() == 1)
    {
        int elemToInsert = unsortedDeque.front();
        sortedDeque.insert(std::lower_bound(sortedDeque.begin(), sortedDeque.end(), elemToInsert), elemToInsert);
    }
}

bool PmergeMe::hasDuplicates(const std::deque<int> &dequ)
{
    std::unordered_set<int> set(dequ.begin(), dequ.end());
    return set.size() != dequ.size();
}

void PmergeMe::sortDequeTest()
{
    std::cout << "sortDeque Test: ";
    if (std::is_sorted(sortedDeque.begin(), sortedDeque.end()))
        std::cout << CYAN "Sorted\n" RESET;
    else
        std::cout << RED "Not sorted\n" RESET;
}

void PmergeMe::sortVectorTest()
{
    std::cout << "sortVector Test: ";
    if (std::is_sorted(sorted.begin(), sorted.end()))
        std::cout << CYAN "Sorted\n" RESET;
    else
        std::cout << RED "Not sorted\n" RESET;
}

void PmergeMe::timeSortDeque(int argc, char *argv[])
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::deque<int> dequ;
    for (int i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        if (!std::all_of(input.begin(), input.end(), ::isdigit))
        {
            throw std::invalid_argument("Error. Input must be positive integers");
        }
        try
        {
            int num = std::stoi(input);
            if (num <= 0)
                dequ.push_back(num);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << RED "Error. Number out of range: " << input << std::endl
                      << RESET;
            return;
        }
    }
    MergeInsertionSort(dequ);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    // std::cout << "After: ";
    // printDeque(sortedDeque);
    printTime(end - start, argc - 1, "std::deque");
}
