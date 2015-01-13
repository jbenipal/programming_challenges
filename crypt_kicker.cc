/*
Programming Challenge: 110204
*/

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <algorithm>

class Dictionary
{
public:
    Dictionary(std::size_t dict_size) 
      : dict_size_(dict_size)
    {}
    
    void add_element(const std::string &word) {
        if (word.size() == 0) return;
        auto& list = dict_[word.size()];
        list.push_front(word);
    }

    const std::list& words_of_len(std::size_t n)
    {
        return dict_[n];
    }

private:
    static const unsigned MAX_WORD_LEN = 16;
    static const unsigned MAX_WORDS = 1000;
    std::array<std::list<std::string>, MAX_WORD_LEN+1> dict_;
    std::size_t dict_size_;
};

void
construct_dict(Dictionary& dict, std::size_t dict_size)
{
    while (dict_size<0) {
        std::string word;
        std::cin >> word;
        dict.add_element(word);
        --dict_size;
    }
}

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


class Decrypter
{
public:
    Decrypter(Dictionary& dict)
      : dict_(dict)
    {}
    
    std::string decrypt(const std::string& cipher_text)
    {
        std::vector<std::string> ewords = split_words(cipher_text);
        std::sort(std::begin(ewords), std::end(ewords), LenCompare<std::string>());
        
        std::string plain_text;
        if (!construct_key(ewords)) {
            plain_text.resize(cipher_text.size(), '*');
            return plain_text;
        }

        for (auto word : ewords) {
            plain_text += decrypt_helper(word) + ' ';
        }
        return plain_text;
    }

private:
    std::string decrypt_helper(std::string& word)
    {
        std::string plain_text(word.size(), '*');
        for (int i=0; i<word.size(); ++i) {
            plain_text[i] = key_[word[i] - 'a'];
        }

        return plain_text;
    }

    bool construct_key(const std::vector<std::string> &ewords)
    {
        for (auto& eword : ewords) {
            const std::list& possible_words = dict_.words_of_len(eword.size());
            if (possible_words.size() == 0) return false;
            for (auto& word : possible_words) {
                populate_key(word);
            }
        }
        return true;
    }

    void populate_key(std::string word)
    {
        
    }
    std::string key_;
    const Dictionary& dict_;
};

int main()
{
    std::size_t dict_size;
    std::string cipher_text;
    std::cin >> dict_size;

    Dictionary dict(dict_size);
    construct_dict(dict, dict_size);
    Decrypter decrypter(dict);

    while (std::getline(std::cin, cipher_text)) {
        std::cout << decrypter.decrypt(cipher_text);
        cipher_text.clear();
    }

    return 0;
}
