#include <iostream>
#include <fstream>
#include <bitset>

int main(int argc, char** argv) {
    if (argc < 1) {
        std::cout << "give me an input" << std::endl;
    }
    std::string fn(argv[1]);
    std::ifstream inf(fn);

    char buf[7]; // input buf of bytes
    char dec[8]; // buf of by7es
    while (inf.good()) {
        inf.read(buf, sizeof(buf));
        int read = inf.gcount();
        int processed = (read * 8) / 7;

        // std::cout << "read " << read << " bytes" << std::endl;
        // std::cout << "proc " << processed << " bytes" << std::endl;

        dec[0] = ((buf[0] & 0b11111110) >> 1);
        dec[1] = ((buf[0] & 0b00000001) << 6) | (buf[1] & 0b11111100) >> 2;
        dec[2] = ((buf[1] & 0b00000011) << 5) | (buf[2] & 0b11111000) >> 3;
        dec[3] = ((buf[2] & 0b00000111) << 4) | (buf[3] & 0b11110000) >> 4;
        dec[4] = ((buf[3] & 0b00001111) << 3) | (buf[4] & 0b11100000) >> 5;
        dec[5] = ((buf[4] & 0b00011111) << 2) | (buf[5] & 0b11000000) >> 6;
        dec[6] = ((buf[5] & 0b00111111) << 1) | (buf[6] & 0b10000000) >> 7;
        dec[7] = ((buf[6] & 0b01111111));

        // for (int i = 0; i < read; i++) {
        //     std::bitset<8> bin(buf[i]);
        //     std::cout << "i " << bin << " ";
        // }
        // std::cout << std::endl;

        // dump decoded bytes
        for (int i = 0; i < processed; i++) {
            // std::bitset<8> bin(dec[i]);
            // std::cout << "o " << bin << " ";
            std::cout << dec[i];
        }
        // std::cout << std::endl;

        std::cout << std::flush;
    }
}