#include "calculation.hpp"

const int PRINT_FREQUENCY_LIMIT = 3;
const int W_STYLE_THREE = 50;

MyString::MyString(const std::vector<std::string>& w, std::ofstream& out) : word_data(w), outfile(out) {
    getStrings();
}

void MyString::getStrings() {
    // Implement the function body if needed
}

void MyString::showPromp(std::string f_name, int word_count) {
    outfile << "The file: " << f_name << " contains " << word_count << " words, ";
    std::cout << "The file: " << f_name << " contains " << word_count << " words, ";
}

void MyString::countAndDelDup(std::vector<std::string>& pS, std::unordered_map<std::string, int>& fmap) {
    for (const std::string& p : pS) {
        fmap[p]++;  // Simplified logic for counting occurrences
    }

    pS.clear(); // Clear original vector

    // Rebuild the vector from unique entries
    for (const auto& entry : fmap) {
        pS.push_back(entry.first);
    }
}

void MyString::getUniqueCount(std::vector<std::string>& concat, std::unordered_map<std::string, int>& map) {
    int test_count = concat.size();
    outfile << "and " << test_count << " unique phrases." << std::endl;
    std::cout << "and " << test_count << " unique phrases." << std::endl;
}

void MyString::sortKeyValue(std::unordered_map<std::string, int> map) {
    std::vector<std::pair<std::string, int>> keyValuePairs(map.begin(), map.end());

    // Sort by frequency (descending)
    std::sort(keyValuePairs.begin(), keyValuePairs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (const auto& pair : keyValuePairs) {
        if (pair.second >= PRINT_FREQUENCY_LIMIT) {
            outfile << std::left << std::setw(W_STYLE_THREE) << pair.first << std::setw(W_STYLE_THREE) << pair.second << std::endl;
            std::cout << std::left << std::setw(W_STYLE_THREE) << pair.first << std::setw(W_STYLE_THREE) << pair.second << std::endl;
        }
    }
}

MyString::~MyString() {
    outfile.close();
}

// Non-member function implementations
std::string stripEnd(const std::string& str) {
    std::string result = str;
    const std::string charsToStrip = ".;?!-\":','`)";
    size_t lastValidChar = result.find_last_not_of(charsToStrip);

    if (lastValidChar != std::string::npos) {
        result.resize(lastValidChar + 1);
    } else {
        result.clear();
    }
    return result;
}

std::string stripBeginning(const std::string& str) {
    std::string result = str;
    const std::string charsToStrip = ".;?!-\":','`)";
    size_t firstValidChar = result.find_first_not_of(charsToStrip);

    if (firstValidChar != std::string::npos) {
        result = result.substr(firstValidChar);
    } else {
        result.clear();
    }
    return result;
}

std::string removeAscii(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string u32str = converter.from_bytes(str);
    std::u32string removed_str;
    bool previousWasSingleQuote = false;

    for (char32_t c : u32str) {
        if (c == U'â' || c == U'€' || c == U'™') {
            if (!previousWasSingleQuote) {
                removed_str += U"'";
                previousWasSingleQuote = true;
            }
        } else {
            removed_str += c;
            previousWasSingleQuote = false;
        }
    }
    return converter.to_bytes(removed_str);
}

std::string getValidFilename() {
    std::string filename;
    do {
        std::cout << "Enter the source data file name: ";
        std::cin >> filename;
        std::ifstream testFile(filename.c_str());

        if (testFile.good()) {
            testFile.close();
            return filename;
        } else {
            std::cout << "Error: Unable to open the file. Please try again." << std::endl;
        }
    } while (true);
}

std::string getOutfileName() {
    std::string outfileName;
    do {
        std::cout << "Enter the output file name: ";
        std::cin >> outfileName;

        std::ofstream testOutfile(outfileName);
        if (testOutfile.is_open()) {
            testOutfile.close();
            return outfileName;
        } else {
            std::cout << "Error: Unable to create the output file. Please try again." << std::endl;
        }
    } while (true);
}

std::string removeDoubleDashAndSplit(const std::string& input, std::string& firstPart, std::string& secondPart) {
    size_t pos = input.rfind("--");

    if (pos != std::string::npos) {
        firstPart = input.substr(0, pos);
        secondPart = input.substr(pos + 2);
    } else {
        firstPart = input;
        secondPart = "";
    }
    return firstPart + " " + secondPart;
}

bool isAcceptable(char c) {
    return (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

bool isAcceptableString(std::string& s) {
    if (s.empty()) return false;

    auto l = s.length();
    char* p = new char[l + 1];
    strcpy(p, s.c_str());

    if (!isAcceptable(p[0])) {
        delete[] p;
        return false;
    } else {
        for (size_t i = 0; i < l; ++i) {
            p[i] = toupper(p[i]);
        }
        s = std::string(p);
        delete[] p;
        return true;
    }
}

// /Users/danielsan/Desktop
// /Users/danielsan/C++/3100_ASGN_testscore/weshallfight.txt
