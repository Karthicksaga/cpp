#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <locale>
#include <codecvt>

// Case-insensitive string comparison
bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    std::locale loc;
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (std::toupper(str1[i], loc) != std::toupper(str2[i], loc)) {
            return false; // Characters do not match in a case-insensitive manner
        }
    }
    return str1.length() == str2.length();
}

// Remove duplicates from a string vector
std::vector<std::string> removeDuplicates(const std::vector<std::string>& arr) {
    std::unordered_set<std::string> uniqueSet;
    std::vector<std::string> result;
    for (const std::string& str : arr) {
        if (uniqueSet.insert(str).second) {
            result.push_back(str);
        }
    }
    return result;
}

bool compareArrays(const std::vector<std::string>& arr1, const std::vector<std::string>& arr2) {
    // Check for empty arrays
    if (arr1.empty() && arr2.empty()) {
        return false; // Both arrays are empty and considered equal
    } else if (arr1.empty() || arr2.empty()) {
        return true; // One of the arrays is empty, and they are considered different
    }

    // Remove duplicates (if needed)
    std::vector<std::string> uniqueArr1 = removeDuplicates(arr1);
    std::vector<std::string> uniqueArr2 = removeDuplicates(arr2);

    // Case-insensitive comparison
    if (uniqueArr1.size() != uniqueArr2.size()) {
        return true; // Different sizes, considered different
    }

    for (size_t i = 0; i < uniqueArr1.size(); ++i) {
        if (!caseInsensitiveCompare(uniqueArr1[i], uniqueArr2[i])) {
            return true; // Elements are different in a case-insensitive manner
        }
    }

    return false; // Arrays are equal
}

int main() {
    // Test cases
    std::vector<std::string> array1 = {"apple", "banana", "cherry"};
    std::vector<std::string> array2 = {"ChErRy", "apple", "BaNaNa", "banana"};

    if (compareArrays(array1, array2)) {
        std::cout << "Arrays are not equal (considering duplicates, case-insensitive)." << std::endl;
    } else {
        std::cout << "Arrays are equal (considering duplicates, case-insensitive)." << std::endl;
    }

    return 0;
}
