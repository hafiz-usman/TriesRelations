// TriesRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cassert>

using namespace std;


class Trie
{
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
        vector<Element> v;

        Node()
        {
            v.resize(c_maxCharsSupported);
        }
    };

public:
    Trie() :
        _pSentinal(&_sentinal)
    {
    }

    ~Trie()
    {
        // todo!
    }

    bool insert(string& search)
    {
        Node* prev = _pSentinal;
        Node* temp = _pSentinal;
        int index = -1;
        for (int i = 0; i < search.length(); ++i)
        {
            char ch = search[i];
            index = _getCharIndex(ch);
            assert(index != -1);
            if (temp->v[index].next == nullptr)
            {
                temp->v[index].next = new Node();
            }
            prev = temp;
            temp = temp->v[index].next;
        }
        prev->v[index].isWord = true;
        return true;
    }

    bool search(string& search)
    {
        // todo: empty out search() and startsWith() and use a helper, say, find() method
        Node* prev = _pSentinal;
        Node* temp = _pSentinal;
        int index = -1;

        for (int i = 0; i < search.length(); ++i)
        {
            char ch = search[i];
            index = _getCharIndex(ch);
            assert(index != -1);
            if (temp->v[index].next == nullptr)
            {
                return false;
            }
            prev = temp;
            temp = temp->v[index].next;
        }
        return (prev->v[index].isWord);
    }

    bool startsWith(string& pre)
    {
        // todo: empty out search() and startsWith() and use a helper, say, find() method
        Node* temp = _pSentinal;
        int index = -1;

        for (int i = 0; i < pre.length(); ++i)
        {
            char ch = pre[i];
            index = _getCharIndex(ch);
            assert(index != -1);
            if (temp->v[index].next == nullptr)
            {
                return false;
            }
            temp = temp->v[index].next;
        }
        return true;
    }

private:
    static const int c_maxCharsSupported = 26;
    Node* const _pSentinal;
    Node _sentinal;

    int _getCharIndex(char ch)
    {
        if (ch < 'a' || ch > 'z')
        {
            return -1;
        }
        return (ch - 'a');
    }
    char _getChar(int index)
    {
        return ('a' + index);
    }
};

void testTrieBVT()
{
    string temp;
    Trie t;
    vector<string> input{
        "a",
        "aa",
        "aaa",
        "ab",
        "b",
        "ba",
        "baba",
        "abab",
    };

    for (int i = 0; i < input.size(); ++i)
    {
        t.insert(input[i]);
    }

    for (int i = 0; i < input.size(); ++i)
    {
        temp = input[i];
        assert(t.search(temp) == true);
    }
    temp = "aaaa";
    assert(t.search(temp) == false);
    temp = "aba";
    assert(t.search(temp) == false);
    temp = "bb";
    assert(t.search(temp) == false);
    temp = "babab";
    assert(t.search(temp) == false);

    for (int i = 0; i < input.size(); ++i)
    {
        string temp = input[i];
        assert(t.startsWith(temp) == true);
    }
    temp = "aaaa";
    assert(t.startsWith(temp) == false);
    temp = "aba";
    assert(t.startsWith(temp) == true);
    temp = "bb";
    assert(t.startsWith(temp) == false);
    temp = "babab";
    assert(t.startsWith(temp) == false);
    temp = "a";
    assert(t.startsWith(temp) == true);
    temp = "aa";
    assert(t.startsWith(temp) == true);
    temp = "aaa";
    assert(t.startsWith(temp) == true);
    temp = "baa";
    assert(t.startsWith(temp) == false);
}


int main()
{
    testTrieBVT();
    return 0;
}

