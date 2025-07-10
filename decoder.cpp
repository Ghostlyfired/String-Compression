// decoder.cpp
#include "huffman.hpp"
using namespace std;

class HuffmanDecoder {
private:
    unordered_map<string, char> reverseMap;

    void loadEncodingMap(const string& fileName) {
        ifstream fin(fileName);
        int ascii; string code;
        while (fin >> ascii >> code) reverseMap[code] = (char)ascii;
        fin.close();
    }

    string readEncodedFileBinary(const string& fileName) {
        ifstream fin(fileName, ios::binary);
        if (!fin) return "";

        uint32_t bitLength;
        fin.read(reinterpret_cast<char*>(&bitLength), sizeof(bitLength));

        string result;
        char byte;
        while (fin.get(byte)) {
            unsigned char ubyte = static_cast<unsigned char>(byte);
            for (int i = 7; i >= 0 && result.size() < bitLength; --i) {
                result += ((ubyte >> i) & 1) ? '1' : '0';
            }
        }
        fin.close();
        return result;
    }

    string decodeText(const string& encodedText) {
        string result, currentCode;
        for (char bit : encodedText) {
            currentCode += bit;
            if (reverseMap.count(currentCode)) {
                result += reverseMap[currentCode];
                currentCode.clear();
            }
        }
        return result;
    }

public:
    void decompress(const string& encodedFile, const string& mapFile) {
        loadEncodingMap(mapFile);
        string encodedText = readEncodedFileBinary(encodedFile);
        string originalText = decodeText(encodedText);
        ofstream fout("decoded.txt");
        fout << originalText;
        fout.close();
    }
};

int main() {
    HuffmanDecoder decoder;
    decoder.decompress("encoded.bin", "encoding_map.txt");
    cout << "Decompression complete.\n";
    return 0;
}
