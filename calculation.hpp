#ifndef calculation
#define calculation

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <locale>
#include <codecvt>

class MyString {
private:
    std::vector<std::string> word_data;
    std::ofstream& outfile;

public:
    MyString(const std::vector<std::string>& w, std::ofstream& out);
    void getStrings();
    void showPromp(std::string f_name, int word_count);
    void countAndDelDup(std::vector<std::string>& pS, std::unordered_map<std::string, int>& fmap);
    void getUniqueCount(std::vector<std::string>& concat, std::unordered_map<std::string, int>& map);
    void sortKeyValue(std::unordered_map<std::string, int> map);
    ~MyString();
};

std::string stripEnd(const std::string& str);
std::string stripBeginning(const std::string& str);
std::string removeAscii(const std::string& str);
std::string getValidFilename();
std::string getOutfileName();
std::string removeDoubleDashAndSplit(const std::string& input, std::string& firstPart, std::string& secondPart);
bool isAcceptable(char c);
bool isAcceptableString(std::string& s);

#endif /* calculation.hpp */
