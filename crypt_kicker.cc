#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <algorithm>

const std::string alphabets {"abcdefghijklmnopqrstuvwxyz"};

std::vector<std::string>
split_words(const std::string &text, char delimiter = ' ')
{
    std::size_t len = text.length();
    std::vector<std::string> vec;
    std::string word;
    for(auto c : text) {
        if (c != delimiter) {
            word += c;
        } else {
            vec.push_back(word);
            word.clear();
        }
    }
    return vec;
}

template<typename T>
struct LenCompare {
    bool operator()(const T &lhs, const T& rhs) {
        return lhs.size() < rhs.size();
    }
};

class Dictionary {
    Dictionary() = default;
    void add_element(const std::string &word) {
        if (word.size() == 0) return;
        auto& list = dict[word.size()];
        list.push_front(word);
    }
private:
    static const unsigned MAX_WORD_LEN = 16;
    static const unsigned MAX_WORDS = 1000;
    std::array<std::list<std::string>, MAX_WORD_LEN+1> dict;
};


std::string
decrypt_helper(const Dictionary &dict, std::string word, std::string &key)
{
    std::string plain_text(word.size(), '*');
    for (int i=0; i<word.size(); ++i) {
        if (key[word[i] - 'a'] != '*') {
            plain_text[i] = key[word[i] - 'a'];
        } else {
            
        }
    }

    return plain_text;
}

std::string
decrypt(const Dictionary &dict, std::string cipher_text)
{
    std::string key;
    std::vector<std::string> words = split_words(cipher_text);
    std::sort(std::begin(words), std::end(words), LenCompare<std::string>());
    while (true)
    {
        for (auto c : words) {
            decrypt_helper(dict, c, key);
        }
    }
}

int main()
{
    return 0;
}
