/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    vector<std::string> wordList;
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            wordList.push_back(word);
        }
    }
    for(auto& worrd: wordList){
        auto temp = dict.find(worrd);
		if(temp == dict.end()){
			std::vector <std::string> vectorString;
            for(auto& CharS: worrd){
                vectorString.push_back(std::string(1,CharS));
            }
			std::sort(vectorString.begin(),vectorString.end());
			dict.insert(std::pair<string, std::vector<std::string>>(worrd, vectorString));
		}
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(auto& worrd: words){
        auto temp = dict.find(worrd);
        if(temp == dict.end()){
            std::vector <std::string> vectorString;
            for(auto& CharS: worrd){
                vectorString.push_back(std::string(1,CharS));
            }
			std::sort(vectorString.begin(),vectorString.end());
			dict.insert(std::pair<string, std::vector<std::string>>(worrd, vectorString));
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> result;
    auto temp = dict.find(word);
    if(temp!=dict.end()){
        vector<string> alpha = temp->second;
        for(auto& dictAna: dict){
            if(alpha == dictAna.second){
                result.push_back(dictAna.first);
            }
        }

    }
    return result;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;
    for(auto& dictAna: dict){
        vector<string> temp = get_anagrams(dictAna.first);
        if(temp.size()>1){
            result.push_back(temp);
        }
    }
    return result;
}
