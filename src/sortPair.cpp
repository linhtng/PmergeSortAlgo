#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> makePairs(const std::vector<int> &vec)
{
    std::vector<std::pair<int, int>> pairs;
    if (vec.size() % 2 != 0)
    {
        throw std::invalid_argument("Vector size must be even");
    }
    for (size_t i = 0; i < vec.size() - 1; i += 2)
    {
        if (vec[i] > vec[i + 1])
            pairs.emplace_back(vec[i], vec[i + 1]);
        else
            pairs.emplace_back(vec[i + 1], vec[i]);
    }
    return pairs;
}

std::vector<int> getLargerElements(const std::vector<std::pair<int, int>> &pairs)
{
    std::vector<int> largerElements;
    for (const auto &pair : pairs)
    {
        int larger = std::max(pair.first, pair.second);
        largerElements.push_back(larger);
    }
    return largerElements;
}

int main()
{
    std::vector<int> input = {3, 5, 9, 7, 6, 4, 8, 2, 1, 0};
    std::vector<std::pair<int, int>> paired = makePairs(input);

    std::cout << "Pairs:" << std::endl;
    for (const auto &pair : paired)
    {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::sort(paired.begin(), paired.end());
    std::cout << "Pairs after sorted:" << std::endl;
    for (const auto &pair : paired)
    {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::vector<int> largerElements = getLargerElements(paired);

    std::cout << "Larger elements:" << std::endl;
    for (const auto &element : largerElements)
    {
        std::cout << element << std::endl;
    }

    // std::cout << "Unpaired elements:" << std::endl;
    // for (const auto &element : result)
    // {
    //     std::cout << element << std::endl;
    // }

    return 0;
}