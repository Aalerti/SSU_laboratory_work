#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <set>


std::vector<std::string> findTargetWords(const std::string& text) {
    if (text.empty()) return std::vector<std::string>();

    std::vector<std::string> answer;

    std::unordered_set<std::string> dot_sent;
    std::unordered_set<std::string> exclamation_sent;
    std::unordered_set<std::string> question_sent;

    std::vector<std::string> words;
    std::string curr_word;
    for (std::size_t i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            curr_word += tolower(text[i]);
        }
        else {
            if (!curr_word.empty()) {
                words.push_back(curr_word);
                curr_word = "";
            }

            if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
                for (std::size_t j = 0; j < words.size(); j++) {
                    if (text[i] == '.') dot_sent.insert(words[j]);
                    else if (text[i] == '!') exclamation_sent.insert(words[j]);
                    else if (text[i] == '?') question_sent.insert(words[j]);
                }
                words.clear();
            }
        }
    }

    if (dot_sent.empty() || question_sent.empty()) {
        std::cout << "text hasn't got any question and dot sentences";
        return std::vector<std::string>();
    }

    for (const auto& word: dot_sent) {
        if (question_sent.count(word) > 0 && exclamation_sent.count(word) == 0) {
            answer.push_back(word);
        }
    }
    return answer;
}


int main() {
    std::string text;
    std::getline(std::cin, text);

    std::vector<std::string> words = findTargetWords(text);

    for (const auto& word: words) {
        std::cout << word << '\n';
    }

    return 0;
}
