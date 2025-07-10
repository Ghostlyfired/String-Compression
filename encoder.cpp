// encoder.cpp
#include "huffman.hpp"
using namespace std;

class HuffmanEncoder {
private:
    unordered_map<char, int> frequencyMap;
    unordered_map<char, string> huffmanCode;
    HuffmanNode* root = nullptr;

    void buildFrequencyMap(const string& text) {
        for (char ch : text) frequencyMap[ch]++;
    }

    void buildHuffmanTree() {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (auto& pair : frequencyMap) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            pq.push(new HuffmanNode('\0', left->freq + right->freq, left, right));
        }
        root = pq.top();
    }

    void generateCodes(HuffmanNode* node, const string& str) {
        if (!node) return;
        if (!node->left && !node->right) huffmanCode[node->ch] = str;
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

    string encodeText(const string& text) {
        string result;
        for (char ch : text) result += huffmanCode[ch];
        return result;
    }

    void writeEncodedFileBinary(const string& encodedText, const string& fileName) {
        ofstream fout(fileName, ios::binary);
        uint32_t bitLength = encodedText.length();
        fout.write(reinterpret_cast<const char*>(&bitLength), sizeof(bitLength));

        unsigned char byte = 0;
        int bitCount = 0;

        for (char bit : encodedText) {
            byte <<= 1;
            if (bit == '1') byte |= 1;
            bitCount++;

            if (bitCount == 8) {
                fout.put(byte);
                byte = 0;
                bitCount = 0;
            }
        }

        if (bitCount > 0) {
            byte <<= (8 - bitCount);
            fout.put(byte);
        }

        fout.close();
    }

    void writeEncodingMap(const string& fileName) {
        ofstream fout(fileName);
        for (auto& pair : huffmanCode) {
            fout << (int)(unsigned char)pair.first << " " << pair.second << "\n";
        }
        fout.close();
    }

    void showCompressionStats(const string& originalFile, const string& encodedFile) {
        ifstream fin1(originalFile, ios::binary | ios::ate);
        ifstream fin2(encodedFile, ios::binary | ios::ate);
        auto originalSize = fin1.tellg(), encodedSize = fin2.tellg();
        fin1.close(); fin2.close();
        cout << "\n--- Compression Stats ---\n";
        cout << "Original size: " << originalSize << " bytes\n";
        cout << "Encoded size : " << encodedSize  << " bytes\n";
        if (originalSize > 0) {
            double ratio = (double)encodedSize / originalSize;
            cout << "Compression Ratio   : " << ratio << "\n";
            cout << "Space Saved         : " << 100.0 * (1 - ratio) << "%\n";
        }
    }

public:
    void compress(const string& inputFile) {
        ifstream fin(inputFile);
        stringstream buffer;
        buffer << fin.rdbuf();
        string text = buffer.str();
        fin.close();

        buildFrequencyMap(text);
        buildHuffmanTree();
        generateCodes(root, "");

        string encodedText = encodeText(text);
        writeEncodedFileBinary(encodedText, "encoded.bin");
        writeEncodingMap("encoding_map.txt");
        showCompressionStats(inputFile, "encoded.bin");
    }
};

int main() {
    string inputFile;
    cout << "Enter file name to encode: ";
    cin >> inputFile;
    HuffmanEncoder encoder;
    encoder.compress(inputFile);
    cout << "Compression complete.\n";
    return 0;
}
