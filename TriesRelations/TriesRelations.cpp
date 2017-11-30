// TriesRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int c_numAlphabetChars = 26;


struct Node;

struct Element
{
    bool isWord;
    Node* next;
    Element() :
        isWord(false),
        next(nullptr)
    {}
};

struct Node
{
    vector<Element> alpha;
    Node()
    {
        alpha.resize(c_numAlphabetChars);
    }
};

class Trie
{
public:
    Trie() :
        _pSentinal(&_sentinal)
    {}

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        if (word.length() == 0)
        {
            return;
        }

        Node* _runner = _pSentinal;
        Node* prev = nullptr;
        int iChar = -1;
        for (auto ch : word)
        {
            iChar = _getCharIndex(ch);
            if (_runner->alpha[iChar].next == nullptr)
            {
                _runner->alpha[iChar].next = new Node();
            }
            prev = _runner;
            _runner = _runner->alpha[iChar].next;
        }
        prev->alpha[iChar].isWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        if (word.length() == 0)
        {
            return false;
        }

        Node* prev = nullptr;
        Node* runner = _pSentinal;
        int iChar = -1;
        for (auto ch : word)
        {
            iChar = _getCharIndex(ch);
            if (runner->alpha[iChar].next == nullptr)
            {
                return false;
            }
            prev = runner;
            runner = runner->alpha[iChar].next;
        }
        return prev->alpha[iChar].isWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        if (prefix.length() == 0)
        {
            return false;
        }

        Node* runner = _pSentinal;
        int iChar = -1;
        for (auto ch : prefix)
        {
            iChar = _getCharIndex(ch);
            if (runner->alpha[iChar].next == nullptr)
            {
                return false;
            }
            runner = runner->alpha[iChar].next;
        }
        return true;
    }

private:
    Node _sentinal;
    Node* const _pSentinal;

    int _getCharIndex(char ch)
    {
        int temp = ch - 'a';
        if (temp < 0 || temp >= c_numAlphabetChars)
        {
            // unsupported char
            return -1;
        }
        return temp;
    }
};


int main()
{
    vector<string> input
    {
        "hello",
        "hellokitty",
    };
    int count = 0;
    string temp;
    Trie t1;

    if (input.size() == 0)
    {
        do
        {
            cout << "INSERT: " << endl;
            cout << "String [" << count + 1 << "]: ";
            getline(cin, temp);
            if (temp.length() == 0)
            {
                break;
            }
            t1.insert(temp);
            input.push_back(temp);
            count++;
        } while (true);
    }
    else
    {
        for (auto str : input)
        {
            t1.insert(str);
        }
    }

    do
    {
        cout << endl;
        cout << "1) Search word" << endl;
        cout << "2) Search prefix" << endl;
        cout << "3) Dump word list" << endl;
        cout << "> ";
        getline(cin, temp);
        if (temp.length() == 0)
        {
            break;
        }
        int choice = stoi(temp);
        bool found = false;
        switch (choice)
        {
        case 1:
            cout << "Enter search word: ";
            getline(cin, temp);
            found = t1.search(temp);
            cout << "Found = " << found << endl;
            break;
        case 2:
            cout << "Enter search prefix: ";
            getline(cin, temp);
            found = t1.startsWith(temp);
            cout << "Found = " << found << endl;
            break;
        case 3:
            cout << "Trie WORDS: " << endl;
            for (int i = 0; i < input.size(); i++)
            {
                cout << "  ";
                cout << input[i] << endl;
            }
            break;
        default:
            break;
        }
    } while (true);

    return 0;
}

