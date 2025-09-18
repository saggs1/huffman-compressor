#include "../include/huffman.hpp"

Node *buildTree(const map<char, int> &freq)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (const auto &p : freq)
    {
        pq.push(new Node(p.first, p.second));
    }
    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.empty() ? nullptr : pq.top();
}

void generateCodes(Node *root, string code, unordered_map<char, string> &codes)
{
    if (!root)
        return;
    if (root->left == nullptr && root->right == nullptr)
    {
        if (root->data != '\0')
        {
            codes[root->data] = code;
        }
        return;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

void freeTree(Node *root)
{
    if (!root)  return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
