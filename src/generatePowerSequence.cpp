#include <iostream>
#include <vector>
#include <cmath>
#include <list>

std::vector<int> generatePowerSequence(int length)
{
    std::vector<int> sequence;
    sequence.reserve(length);

    int power = 2;
    for (int i = 2; i < length; i++)
    {
        sequence.push_back(power);
        power = std::pow(2, i) - power;
    }

    return sequence;
}

std::list<int> generatePowerSequenceList(int length)
{
    std::list<int> sequence;

    int power = 2;
    for (int i = 2; i < length; i++)
    {
        sequence.push_back(power);
        power = std::pow(2, i) - power;
    }

    return sequence;
}

int main()
{
    int length = 10; // Change the length as per your requirement
    std::vector<int> sequence = generatePowerSequence(length);
    std::list<int> sequenceList = generatePowerSequenceList(length);

    // Print the generated sequence
    for (const auto &num : sequence)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for (const auto &num : sequenceList)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}