#include "../include/huffman.hpp"

void calculateFrequency(const string& filename, map<char, int>& freq) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) return;
    char ch;
    while (file.get(ch)) {
        freq[ch]++;
    }
    file.close();
}

void encodeFile(const string& input, const string& output, const map<char, int>& freq, const unordered_map<char, string>& codes) {
    ofstream out(output, ios::binary);
    if (!out.is_open()) return;

    int num = freq.size();
    out.write(reinterpret_cast<const char*>(&num), sizeof(int));

    for (const auto& p : freq) {
        out.write(&p.first, 1);
        out.write(reinterpret_cast<const char*>(&p.second), sizeof(int));
    }

    ifstream fin(input, ios::binary);
    if (!fin.is_open()) {
        out.close();
        return;
    }

    char ch;
    unsigned char byte = 0;
    int bitCount = 0;
    while (fin.get(ch)) {
        const string& code = codes.at(ch);
        for (char b : code) {
            int bit = b - '0';
            if (bit) {
                byte |= (1u << (7 - bitCount));
            }
            bitCount++;
            if (bitCount == 8) {
                out.write(reinterpret_cast<char*>(&byte), 1);
                bitCount = 0;
                byte = 0;
            }
        }
    }
    if (bitCount > 0) {
        out.write(reinterpret_cast<char*>(&byte), 1);
    }

    fin.close();
    out.close();
}

void decode(ifstream& in, ofstream& out, Node* root, long long total_bits) {
    if (!root || total_bits == 0) return;

    Node* curr = root;
    long long bits_read = 0;
    unsigned char byte = 0;
    int bit_index = 0;

    while (bits_read < total_bits) {
        if (bit_index == 0) {
            if (!in.read(reinterpret_cast<char*>(&byte), 1)) {
                break;
            }
            bit_index = 8;
        }
        if (bit_index == 0) break;

        int bit = (byte >> (bit_index - 1)) & 1;
        bit_index--;
        bits_read++;

        if (bit == 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            out << curr->data;
            curr = root;
        }
    }
}
