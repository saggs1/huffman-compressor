#include "../include/huffman.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./huff <c/d> <input> <output>" << endl;
        return 1;
    }

    string mode = argv[1];
    string input = argv[2];
    string output = argv[3];

    if (mode == "c") {
        map<char, int> freq;
        calculateFrequency(input, freq);
        if (freq.empty()) {
            cout << "Empty file or error reading input." << endl;
            return 0;
        }
        Node* root = buildTree(freq);
        unordered_map<char, string> codes;
        generateCodes(root, "", codes);
        encodeFile(input, output, freq, codes);
        freeTree(root);
        cout << "Compression done: " << input << " -> " << output << endl;
    } else if (mode == "d") {
        ifstream in(input, ios::binary);
        if (!in.is_open()) {
            cout << "Error opening input." << endl;
            return 1;
        }
        int num;
        in.read(reinterpret_cast<char*>(&num), sizeof(int));
        if (num <= 0) {
            cout << "Invalid compressed file." << endl;
            in.close();
            return 1;
        }
        map<char, int> freq;
        for (int i = 0; i < num; i++) {
            char c;
            in.read(&c, 1);
            int f;
            in.read(reinterpret_cast<char*>(&f), sizeof(int));
            freq[c] = f;
        }
        Node* root = buildTree(freq);
        unordered_map<char, string> codes;
        generateCodes(root, "", codes);
        long long total_bits = 0;
        for (const auto& p : freq) {
            total_bits += static_cast<long long>(p.second) * codes[p.first].size();
        }
        ofstream fout(output);
        if (fout.is_open()) {
            decode(in, fout, root, total_bits);
            cout << "Decompression done: " << input << " -> " << output << endl;
        } else {
            cout << "Error opening output." << endl;
        }
        fout.close();
        freeTree(root);
    } else {
        cout << "Invalid mode. Use 'c' for compress or 'd' for decompress." << endl;
        return 1;
    }

    return 0;
}
