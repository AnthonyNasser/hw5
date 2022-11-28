// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Generates all possible string permutations given the contraints:
// 1. The string must contain all fixed letters (represented by any characters in fixedWord that aren't '-') in the correct positions
// 2. The string must contain at least one of each floating letter (represented by all characters in floatingLetters)
// 3. The string must be in the dictionary (as checked by checkPermutation)
void generatePermutations(std::string fixedWord, std::string floatingLetters, int length, int currentIndex, std::set<std::string> &permutations, const std::set<std::string> &dictionary);

// Checks a single word against the dictionary and returns true if it is a valid word
bool checkPermutation(std::string word, const std::set<std::string> &dictionary);

std::set<std::string> wordle(
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict)
{
    std::set<std::string> solutions;
    std::string floatingLetters = floating;
    std::string fixedWord = in;
    generatePermutations(fixedWord, floatingLetters, in.size(), 0, solutions, dict);
    return solutions;
}

void generatePermutations(std::string fixedWord, std::string floatingLetters, int length, int currentIndex, std::set<std::string> &permutations, const std::set<std::string> &dictionary)
{
    unsigned int toBeFilledCount = 0;
    for (int i = 0; i < length; i++)
    {
        if (fixedWord[i] == '-')
        {
            toBeFilledCount++;
        }
    }
    if (currentIndex == length)
    {
        if (checkPermutation(fixedWord, dictionary))
        {
            permutations.insert(fixedWord);
        }
        return;
    }
    if (fixedWord[currentIndex] != '-')
    {
        generatePermutations(fixedWord, floatingLetters, length, currentIndex + 1, permutations, dictionary);
        return;
    }
    if (toBeFilledCount != floatingLetters.size())
    {
        for (char i = 'a'; i <= 'z'; i++)
        {
            fixedWord[currentIndex] = i;
            if (floatingLetters.find(i) <= floatingLetters.size())
            {
                std::string next = floatingLetters;
                next.erase(std::remove(next.begin(), next.end(), i), next.end());
                generatePermutations(fixedWord, next, length, currentIndex + 1, permutations, dictionary);
            }
            else
            {
                generatePermutations(fixedWord, floatingLetters, length, currentIndex + 1, permutations, dictionary);
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < floatingLetters.size(); i++)
        {
            fixedWord[currentIndex] = floatingLetters[i];
            std::string next = floatingLetters;
            next.erase(i, 1);
            generatePermutations(fixedWord, next, length, currentIndex + 1, permutations, dictionary);
        }
    }
}

bool checkPermutation(std::string word, const std::set<std::string> &dictionary)
{
    return (dictionary.find(word) != dictionary.end());
}