#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// for part two 
std::unordered_map<std::string, int> numberDictionary = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

/**
 * @brief Get the filelines from filename 
 * 
 * @param filename const std::string path to input file 
 * @param filelines std::vector<std::string> & destination 
 * @return true successfully opened file 
 * @return false could not open file 
 */
 bool getFilelines (const std::string filename, std::vector<std::string> &filelines) {
    // Open the input file
    std::ifstream inputFile(filename);

    // Check if the file is open successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file.\n";
        return false;  
    }

    // Read lines from the file and store in the vector
    std::string line;
    while (std::getline(inputFile, line)) {
        filelines.push_back(line);
    }
    inputFile.close();

    return true;
}

/**
 * @brief Parse input line to Part One. First digit and last digit found in line make the answer 
 * 
 * @param line std::string 
 * @return int answer or -1 for processing error 
 */
int questionOne(std::string line) {
    std::string numbers = "";

    // look for digits 
    for (const char& c : line) {
        if(std::isdigit(c)) {
            numbers += c;
        }
    }

    // get full number 
    if (numbers.empty()) {
        return 0;
    }

    if (numbers.length() == 1) {
        return std::stoi(numbers)*11;
    } 
    else {
        return static_cast<int>(numbers.front() - '0')*10 + static_cast<int>(numbers.back() - '0');
    }

    return -1;
}

/**
 * @brief Same as questionOne, but now the text numbers count too 
 * 
 * @param line 
 * @return int 
 */
int questionTwo(std::string line) {

    std::string startPhrase = "";
    std::string endPhrase = "";
    int digitOne = 0;
    int digitTwo = 0;
    int length = line.length();
    char character;
    for (int i = 0; i < length; i++) {
        // search front side for first digit 
        character = line[i];
        if (!digitOne) {
            if (std::isdigit(character)) {
                digitOne = character - '0';
            } else {
                startPhrase += character;
                for (const auto& entry : numberDictionary) {
                    const std::string& key = entry.first;
                    if (startPhrase.find(key) != std::string::npos) {
                        digitOne = entry.second;
                    }
                }
            }
        }
        // search back side for last digit 
        character = line[length -1 - i];
        if (!digitTwo) {
            if (std::isdigit(character)) {
                digitTwo = character - '0';
            } else {
                endPhrase.insert(endPhrase.begin(), character);
                // std::cout << "phrase :" << endPhrase << std::endl;
                for (const auto& entry : numberDictionary) {
                    const std::string& key = entry.first;
                    if (endPhrase.find(key) != std::string::npos) {
                        digitTwo = entry.second;
                    }
                }
            }
        }
        // exit if both found
        if (digitOne && digitTwo){
            break;
        }
    }
    return digitOne*10 + digitTwo;
}

int main() {
    // Load input 
    std::vector<std::string> input;
    if (!getFilelines("input.txt", input)) {
        return -1;
    }

    // Process each line
    int ansOne = 0;
    int ansTwo = 0;
    int sumOne = 0;
    int sumTwo = 0;
    for (const std::string& line : input) {
        ansOne = questionOne(line);
        if (ansOne == -1) {
            std::cout << "error processing line" << std::endl;
            return -1;
        }

        ansTwo = questionTwo(line);
        if (ansTwo < 0) {
            std::cout << "error processing line" << std::endl;
            return -1;
        }
        std::cout << "Line: " << line << " ansOne: " << ansOne << " ansTwo: " << ansTwo << std::endl;
        sumOne += ansOne;
        sumTwo += ansTwo;
    }

    std::cout << "SumOne: " << sumOne << std::endl;
    std::cout << "SumTwo: " << sumTwo << std::endl;

    return 0;  // Return success
}
