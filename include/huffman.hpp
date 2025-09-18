#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <bits/stdc++.h>

using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left, *right;
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

// Function declarations
void calculateFrequency(const string &filename, map<char, int> &freq);
Node *buildTree(const map<char, int> &freq);
void generateCodes(Node *root, string code, unordered_map<char, string> &codes);
void encodeFile(const string &input, const string &output, const map<char, int> &freq, const unordered_map<char, string> &codes);
void decode(ifstream &in, ofstream &out, Node *root, long long total_bits);
void freeTree(Node *root);

#endif
