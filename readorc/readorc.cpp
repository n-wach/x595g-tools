#include <iostream>
#include "ca7_read.h"

int POS = 0;
B7* DATA;

void read(uint8_t* buf, int n) {
  for (int i = 0; i < n; i++) {
    buf[i] = DATA[POS++].val;
  }
}

uint32_t readWord() {
  uint8_t word[4];
  read(word, 4);

  uint32_t val = word[0] | (word[1] << 7) | (word[2] << 14) | (word[3] << 21);
  return val;
}

bool readBool() {
  uint8_t b;
  read(&b, 1);
  return b == '\x1';
}

std::string readString() {
  std::string res;
  uint8_t c;
  read(&c, 1);
  while (c != '\0') {
    res += c;
    read(&c, 1);
  }
  return res;
}

int main(int argc, char *argv[]) {
  if(argc < 2){
    fprintf(stderr, "include file to read");
    return 1;
  }

  DATA = read7File(argv[1]);
  
  uint8_t head1[5];
  read(head1, 5);

  uint8_t ORC_o = head1[0];
  uint8_t ORC_r = head1[1];
  uint8_t ORC_c = head1[2];

  std::cout << "Head: " << ORC_o << ORC_r << ORC_c << std::endl;

  uint8_t fileType = head1[4];
  std::cout << "FileType: " << ((fileType == '\0') ? "EXE" : "OBJ") << std::endl;

  bool hasEntryPoint = readBool();
  std::cout << "HasEntryPoint: " << (hasEntryPoint ? "NO" : "YES") << std::endl;
  
  if(hasEntryPoint) {
    uint32_t entryPoint = readWord();
    std::cout << "EntryPoint: " << entryPoint << std::endl;
  }

  uint32_t numSymbols = readWord();
  std::cout << "SymbolCount: " << numSymbols << std::endl;
  for (int i = 0; i < numSymbols; i++) {
    std::string symbolName = readString();
    std::cout << "  Name:" << symbolName << std::endl;
    bool isDefined = readBool();
    std::cout << "  Defined:" << isDefined << std::endl;
  }
}
