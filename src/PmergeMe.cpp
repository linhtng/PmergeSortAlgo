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

std::vector<int> PmergeMe::generatePowerSequence(size_t length)
{
    std::vector<int> sequence;

    for (size_t i = 0; i < JACOBSTHAL_SEQUENCE.size() && JACOBSTHAL_SEQUENCE[i] <= length; ++i)
    {
        sequence.push_back(JACOBSTHAL_SEQUENCE[i]);
    }

    return sequence;
}

std::deque<int> PmergeMe::generatePowerSequenceDeque(size_t length)
{
    std::deque<int> sequence;

    for (size_t i = 0; i < JACOBSTHAL_SEQUENCE_DEQUE.size() && JACOBSTHAL_SEQUENCE_DEQUE[i] <= length; ++i)
    {
        sequence.push_back(JACOBSTHAL_SEQUENCE_DEQUE[i]);
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

/*
Step 6: Insert the remaining elements into the sorted sequence using binary search
        First, find the length of the subsequence to insert the element into
        As we are inserting in order y_4, y_3, y_6, y_5, y_12, y_11, y_10, y_9, y_8, y_7, y_22, y_21...
        The subsequence length to insert will be up to but not including x_i.
        We then perform a binary search on that subsequence to find the location to insert the element.
*/
void PmergeMe::insertElementVector(int elementToInsert, const std::unordered_map<int, int> &reversePairMap)
{
    auto elemPairedLarger = reversePairMap.find(elementToInsert);
    if (elemPairedLarger != reversePairMap.end())
    {
        int elemToInsertUpperBound = elemPairedLarger->second;
        auto boundaryIt = std::find(sortedVec.begin(), sortedVec.end(), elemToInsertUpperBound);
        if (boundaryIt != sortedVec.end())
        {
            // std::cout << "Lower bound search range for element " << elementToInsert << ":\n";
            // for (auto it = sortedVec.begin(); it != boundaryIt; ++it)
            // {
            //     std::cout << *it << " ";
            // }
            // std::cout << "\n";
            auto insertPos = std::lower_bound(sortedVec.begin(), boundaryIt, elementToInsert);
            sortedVec.insert(insertPos, elementToInsert);
            return;
        }
    }
    // std::cout << "Element " << elementToInsert << " doesn't have a pair\n";
    sortedVec.insert(std::lower_bound(sortedVec.begin(), sortedVec.end(), elementToInsert), elementToInsert);
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
    sortedVec.clear();
    for (const std::pair<int, int> &pair : paired)
    {
        sortedVec.push_back(pair.second);
    }
    // Create a map from the pairs
    std::unordered_map<int, int> pairMap;
    for (const std::pair<int, int> &pair : paired)
    {
        pairMap[pair.second] = pair.first;
    }
    MergeInsertionSort(sortedVec);
    unsortedVec.clear();
    if (paired.size() > 1)
    {
        for (const int &element : sortedVec) // complexity O(n)
        {
            std::unordered_map<int, int>::iterator it = pairMap.find(element);
            if (it != pairMap.end())
                unsortedVec.push_back(it->second);
        }
    }
    else
    {
        unsortedVec.push_back(paired.front().first);
    }
    if (oddSize)
        unsortedVec.push_back(lastElement);
    // std::cout << "Sorted atfer step 1 - 3: \n";
    // printVector(sortedVec);
    // std::cout << "Unsorted: \n";
    // printVector(unsortedVec);

    // Step 4: Insert the element paired with the smallest element at the start of the sorted sequence
    sortedVec.insert(sortedVec.begin(), unsortedVec.front());
    unsortedVec.erase(unsortedVec.begin());
    // std::cout << "[Vector] Sorted after step 4: \n";
    // printVector(sortedVec);
    // std::cout << "Unsorted: \n";
    // printVector(unsortedVec);

    /*
    Step 5 : Partition the unsorted elems into groups with contiguous indexes.
    The sums of sizes of every two adjacent groups form a sequence of powers of two
    */
    std::unordered_map<int, int> reversePairMap;
    for (const auto &pair : pairMap)
    {
        reversePairMap[pair.second] = pair.first;
    }
    if (unsortedVec.size() > 1)
    {
        std::vector<int> groupSizes = generatePowerSequence(unsortedVec.size());
        // std::cout << "Groups'sized generated so as the sums of sizes of every two adjacent groups form a sequence of powers of two: \n";
        // printVector(groupSizes);
        // std::cout << "Unsorted partitioned: \n";
        std::vector<std::vector<int>> orderToInsert = partition(unsortedVec, groupSizes);
        // for (const auto &sub_vector : orderToInsert)
        // {
        //     printVector(sub_vector);
        // }
        // Step 6: Insert the remaining elements into the sorted sequence using binary search
        // First, find the length of the subsequence to insert the element into
        // As we are inserting in order y_4, y_3, y_6, y_5, y_12, y_11, y_10, y_9, y_8, y_7, y_22, y_21...
        // The subsequence length to insert will be up to but not including x_i.
        // We then perform a binary search on that subsequence to find the location to insert the element.
        for (const std::vector<int> &uninsertedGroup : orderToInsert)
        {
            for (const int &element : uninsertedGroup)
            {
                insertElementVector(element, reversePairMap);
            }
        }
    }
    else if (unsortedVec.size() == 1)
    {
        // std::cout << "Inserting the only unsorted left " << unsortedVec.front() << '\n';
        // std::cout << "Sorted before insertion: \n";
        // printVector(sortedVec);
        int elemToInsert = unsortedVec.front();
        insertElementVector(elemToInsert, reversePairMap);
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
    if (hasDuplicates(vec))
    {
        throw std::invalid_argument("Error. Duplicate elements found");
    }
    MergeInsertionSort(vec);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "After: ";
    printVector(sortedVec);
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

/*
    Step 6: Insert the remaining elements into the sorted sequence using binary search
    First, find the length of the subsequence to insert the element into
    As we are inserting in order y_4, y_3, y_6, y_5, y_12, y_11, y_10, y_9, y_8, y_7, y_22, y_21...
    The subsequence length to insert will be up to but not including x_i.
    We then perform a binary search on that subsequence to find the location to insert the element.
    When x_i is not found in the pairMap, it means that y_i didn't have a pair,
    e.g. main chain contain x_1, x_2, x_3, while we need to insert y_4
    Binary search range is then the whole sorted chain.
*/
void PmergeMe::insertElementDeque(int elementToInsert, const std::unordered_map<int, int> &reversePairMap)
{
    auto elemPairedLarger = reversePairMap.find(elementToInsert);
    if (elemPairedLarger != reversePairMap.end())
    {
        int elemToInsertUpperBound = elemPairedLarger->second;
        auto boundaryIt = std::find(sortedDeque.begin(), sortedDeque.end(), elemToInsertUpperBound);
        if (boundaryIt != sortedDeque.end())
        {
            // std::cout << "Lower bound search range for element " << elementToInsert << ":\n";
            // for (auto it = sortedDeque.begin(); it != boundaryIt; ++it)
            // {
            //     std::cout << *it << " ";
            // }
            // std::cout << "\n";
            auto insertPos = std::lower_bound(sortedDeque.begin(), boundaryIt, elementToInsert);
            sortedDeque.insert(insertPos, elementToInsert);
            return;
        }
    }
    // std::cout << "Element " << elementToInsert << " doesn't have a pair\n";
    sortedDeque.insert(std::lower_bound(sortedDeque.begin(), sortedDeque.end(), elementToInsert), elementToInsert);
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
    // Create reverse map for lookup of x_i
    std::unordered_map<int, int> reversePairMap;
    for (const auto &pair : pairMap)
    {
        reversePairMap[pair.second] = pair.first;
    }
    if (unsortedDeque.size() > 1)
    {
        std::deque<int> groupSizes = generatePowerSequenceDeque(unsortedDeque.size());
        // std::cout << "Groups'sized generated so as the sums of sizes of every two adjacent groups form a sequence of powers of two: \n";
        // printDeque(groupSizes);
        std::deque<std::deque<int>> orderToInsert = partition(unsortedDeque, groupSizes);
        // std::cout << "Unsorted in groups: \n";
        // for (const auto &sub_deque : orderToInsert)
        // {
        //     printDeque(sub_deque);
        // }
        for (const std::deque<int> &uninsertedGroup : orderToInsert)
        {
            for (const int &element : uninsertedGroup)
            {
                insertElementDeque(element, reversePairMap);
            }
        }
    }
    else if (unsortedDeque.size() == 1)
    {
        int elemToInsert = unsortedDeque.front();
        insertElementDeque(elemToInsert, reversePairMap);
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
    {
        std::cout << RED "Not sorted\n" RESET;
        std::cout << "Sorted deque: \n";
        printDeque(sortedDeque);
        std::cout << "Supposed to be: \n";
        std::deque<int> temp = sortedDeque;
        std::sort(temp.begin(), temp.end());
        printDeque(temp);
    }
}

void PmergeMe::sortVectorTest()
{
    std::cout << "sortVector Test: ";
    if (std::is_sorted(sortedVec.begin(), sortedVec.end()))
        std::cout << CYAN "Sorted\n" RESET;
    else
    {
        std::cout << RED "Not sorted\n" RESET;
        std::cout << "Sorted vector: \n";
        printVector(sortedVec);
        std::cout << "Supposed to be: \n";
        std::vector<int> temp = sortedVec;
        std::sort(temp.begin(), temp.end());
        printVector(temp);
    }
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
            dequ.push_back(num);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << RED "Error. Number out of range: " << input << std::endl
                      << RESET;
            return;
        }
    }
    if (hasDuplicates(dequ))
    {
        throw std::invalid_argument("Error. Duplicate elements found");
    }
    MergeInsertionSort(dequ);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "After: ";
    printDeque(sortedDeque);
    printTime(end - start, argc - 1, "std::deque");
}
