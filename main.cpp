#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <locale>
#include <codecvt>
#include <fstream>

#include "calculation.hpp"
/*
 Source reference:
 1) Grokking Algorithms - An illustrated guide for programmers and other curious people
 Big O notation page 29- 35
 
 Hash table - Chapter 5 page 73 - 83
 
 2) https://en.cppreference.com/w/cpp/container/unordered_map
 
 3) ChatGPT for syntax check
 
 */

// Constants for setw sizes
//const int W_STYLE_ONE = 25;
//const int W_STYLE_TWO = 40;
//const int W_STYLE_THREE = 50;

// Constants for phrase sizes
const int PHRASE_SIZE_ONE = 1;
const int PHRASE_SIZE_TWO = 2;
const int PHRASE_SIZE_THREE = 3;
const int PHRASE_SIZE_FOUR = 4;
const int PHRASE_SIZE_FIVE = 5;

//const int PRINT_FREQUENCY_LIMIT = 10; // print when Frequency >= 10


int main() {
    // Constants for prompt messages
    const std::string PROMPT_OPENED_FILE = "Opened file";
    const std::string PROMPT_ENTER_PHRASE_SIZE = "How many Adjacent words in a phrase, enter 1-5: ";

    std::string filename = getValidFilename();
    std::ifstream inputFile(filename);

    int num_phrases;
    if (inputFile.is_open()) {
        
        std::cout << PROMPT_OPENED_FILE << std::endl;
        std::cout << PROMPT_ENTER_PHRASE_SIZE;
        std::cin >> num_phrases;

        std::vector<std::string> ph;               // Vector 1 0 1 2 3 4 5 6 (4 bytes * n)
        std::vector<std::string> phTwoPhrases;     // Vector 2 01 12 23 34 45 (4 bytes * n)^2
        std::vector<std::string> phThreePhrases;   // Vector 3 012 123 234 345 (4 bytes * n)^3
        std::vector<std::string> phFourPhrases;    // Vector 4 0123 1234 2345 3456 (4 bytes * n)^4
        std::vector<std::string> phFivePhrases;    // Vector 5 01234 12345 23456 34567 (4 bytes * n)^5

        std::unordered_map<std::string, int> frequencyMap;

        int og_word_count = 0;
        std::string temp;
        while (inputFile >> temp) {
            if (temp.empty()) {
                continue;
            }
            
            if (isAcceptableString(temp)){
                og_word_count = og_word_count + 1 ;
                std::string firstPart, secondPart;
                std::string removeDup = removeDoubleDashAndSplit(temp, firstPart, secondPart);
                std::string processedWord = removeAscii(removeDup);
                std::string strippedWordEnd = stripEnd(processedWord);
                std::string strippedWordBeg = stripBeginning(strippedWordEnd);

                ph.push_back(strippedWordBeg);

                // ... PHRASES CONCAT ...... PHRASES CONCAT ...... PHRASES CONCAT ...... PHRASES CONCAT ...... PHRASES CONCAT ...
                if (ph.size() >= PHRASE_SIZE_ONE &&
                    num_phrases == PHRASE_SIZE_ONE) {
//                    buffer_test_count++;

                } else if (ph.size() >= PHRASE_SIZE_TWO &&
                           num_phrases == PHRASE_SIZE_TWO) {
                    phTwoPhrases.push_back
                    (ph[ph.size() - PHRASE_SIZE_TWO]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_ONE]);
//                    buffer_test_count++;

                } else if (ph.size() >= PHRASE_SIZE_THREE &&
                           num_phrases == PHRASE_SIZE_THREE) {
                    phThreePhrases.push_back
                    (ph[ph.size() - PHRASE_SIZE_THREE]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_TWO]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_ONE]);
//                    buffer_test_count++;

                } else if (ph.size() >= PHRASE_SIZE_FOUR &&
                           num_phrases == PHRASE_SIZE_FOUR) {
                    phFourPhrases.push_back
                    (ph[ph.size() - PHRASE_SIZE_FOUR]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_THREE]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_TWO]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_ONE]);
//                    buffer_test_count++;

                } else if (ph.size() >= PHRASE_SIZE_FIVE &&
                           num_phrases == PHRASE_SIZE_FIVE) {
                    phFivePhrases.push_back
                    (ph[ph.size() - PHRASE_SIZE_FIVE]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_FOUR]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_THREE]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_TWO]
//                     + " "
                     + ph[ph.size() - PHRASE_SIZE_ONE]);
//                    buffer_test_count++;
                }
           }
        }

        std::string outfileName = getOutfileName();
        std::ofstream outfile(outfileName);

        if (num_phrases == PHRASE_SIZE_ONE) { //instances
            MyString phrases_one(ph, outfile);
            phrases_one.showPromp(filename, og_word_count);
            phrases_one.countAndDelDup(ph, frequencyMap);
            phrases_one.getUniqueCount(ph, frequencyMap);
            phrases_one.sortKeyValue(frequencyMap);

        } else if (num_phrases == PHRASE_SIZE_TWO) {
            MyString phrases_two(phTwoPhrases, outfile);
            phrases_two.showPromp(filename, og_word_count);
            phrases_two.countAndDelDup(phTwoPhrases, frequencyMap);
            phrases_two.getUniqueCount(phTwoPhrases, frequencyMap);
            phrases_two.sortKeyValue(frequencyMap);

        } else if (num_phrases == PHRASE_SIZE_THREE) {
            MyString phrases_three(phThreePhrases, outfile);
            phrases_three.showPromp(filename, og_word_count);
            phrases_three.countAndDelDup(phThreePhrases, frequencyMap);
            phrases_three.getUniqueCount(phThreePhrases, frequencyMap);
            phrases_three.sortKeyValue(frequencyMap);

        } else if (num_phrases == PHRASE_SIZE_FOUR) {
            MyString phrases_four(phFourPhrases, outfile);
            phrases_four.showPromp(filename, og_word_count);
            phrases_four.countAndDelDup(phFourPhrases, frequencyMap);
            phrases_four.getUniqueCount(phFourPhrases, frequencyMap);
            phrases_four.sortKeyValue(frequencyMap);

        } else if (num_phrases == PHRASE_SIZE_FIVE) {
            MyString phrases_five(phFivePhrases, outfile);
            phrases_five.showPromp(filename, og_word_count);
            phrases_five.countAndDelDup(phFivePhrases, frequencyMap);
            phrases_five.getUniqueCount(phFivePhrases, frequencyMap);
            phrases_five.sortKeyValue(frequencyMap);
        }
        outfile.close();
    }

    inputFile.close();
    return 0;
}
