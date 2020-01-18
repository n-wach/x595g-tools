#include <iostream>
#include <fstream>

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

        // if (read > )
        dec[0] = (buf[0] >> 1);
        dec[1] = (buf[0] & 0b1) | (buf[1] >> 2);
        dec[2] = (buf[1] & 0b11) | (buf[2] >> 3);
        dec[3] = (buf[2] & 0b111) | (buf[3] >> 4);
        dec[4] = (buf[3] & 0b1111) | (buf[4] >> 5);
        dec[5] = (buf[4] & 0b11111) | (buf[5] >> 6);
        dec[6] = (buf[5] & 0b111111) | (buf[6] >> 7);
        dec[7] = (buf[6] & 0b1111111);

        // dump decoded bytes
        for (int i = 0; i < processed; i++) {
            std::cout << dec[i];
        }
        std::cout << std::flush;
    }
}