#include <iostream>
#include <bitset>

#include "ca7_read.h"

int POS = 0;
B7* DATA;
int DATA_LEN;

// types
typedef uint8_t B8;
typedef B8* Text7;
typedef uint32_t Word28;

void read(Text7 buf, int n) {
  for (int i = 0; i < n; i++) {
    buf[i] = DATA[POS++].val;
  }
}

B8 readOne() {
  B8 b;
  read(&b, 1);
  return b;
}

Word28 readWord() {
  uint8_t word[4];
  read(word, 4);

  Word28 val = word[0] | (word[1] << 7) | (word[2] << 14) | (word[3] << 21);
  return val;
}

bool readBool() {
  B8 b;
  read(&b, 1);
  return b == '\x1';
}

std::string readString() {
  std::string res;
  B8 c;
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

  struct read7_result read_out = read7File(argv[1]);
  DATA = read_out.data;
  DATA_LEN = read_out.size;
  
  uint8_t head1[5];
  read(head1, 5);

  B8 ORC_o = head1[0];
  B8 ORC_r = head1[1];
  B8 ORC_c = head1[2];

  std::cout << "Head: " << ORC_o << ORC_r << ORC_c << std::endl;

  B8 fileType = head1[4];
  std::cout << "FileType: " << ((fileType == '\0') ? "EXE" : "OBJ") << std::endl;

  bool hasEntryPoint = readBool();
  std::cout << "HasEntryPoint: " << (hasEntryPoint ? "NO" : "YES") << std::endl;
  
  if(hasEntryPoint) {
    Word28 entryPoint = readWord();
    std::cout << "EntryPoint: " << entryPoint << std::endl;
  }

  std::cout << std::endl;
  Word28 numSymbols = readWord();
  std::cout << "SymbolCount: " << numSymbols << std::endl;
  for (size_t i = 0; i < numSymbols; i++) {
    std::string symbolName = readString();
    std::cout << "  Name: " << symbolName << std::endl;
    bool isDefined = readBool();
    std::cout << "  Defined: " << isDefined << std::endl;
    if (isDefined) {
      Word28 section = readWord();
      std::cout << "  Section: " << section << std::endl;
      Word28 offset = readWord();
      std::cout << "  Offset: " << offset << std::endl;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  Word28 numReloc = readWord();
  std::cout << "RelocCount: " << numReloc << std::endl;
  for (size_t i = 0; i < numReloc; i++) {
    Word28 section = readWord();
    std::cout << "  Section: " << section << std::endl;
    Word28 offset = readWord();
    std::cout << "  Offset: " << offset << std::endl;
    std::string symbol = readString();
    std::cout << "  Symbol: " << symbol << std::endl;
    Word28 plus = readWord();
    std::cout << "  Plus: " << plus << std::endl;
    std::cout << std::endl;
  }

  std::cout << std::endl;
  Word28 numSections = readWord();
  std::cout << "NumSections: " << numSections << std::endl;
  for (size_t i = 0; i < numSections; i++) {
    B8 perms = readOne();
    std::cout << "  Permissions: " << std::bitset<8>(perms) << std::endl;
    Word28 offset = readWord();
    std::cout << "  Offset: " << offset << std::endl;
    std::string symbol = readString();
    std::cout << "  Name: " << symbol << std::endl;
    Word28 size = readWord();
    std::cout << "  Size: " << size << std::endl;
    std::cout << std::endl;
  }

  std::cout << std::endl;
  Word28 numSegments = readWord();
  std::cout << "NumSegments: " << numSegments << std::endl;
  for (size_t i = 0; i < numSegments; i++) {
    std::string symbol = readString();
    std::cout << "  Name: " << symbol << std::endl;
    Word28 offset = readWord();
    std::cout << "  Offset: " << offset << std::endl;
    Word28 base = readWord();
    std::cout << "  Base: " << base << std::endl;
    B8 perms = readOne();
    std::cout << "  Permissions: " << std::bitset<8>(perms) << std::endl;
    Word28 type = readOne();
    std::cout << "  Type: " << type << std::endl;
    std::cout << std::endl;
  }

  // now read contents
  std::cout << std::endl;
  int contentSize = DATA_LEN - POS;
  Text7 contents = new B8[contentSize];
  read(contents, contentSize);
  std::cout << "Content: B8[" << contentSize << "]" << std::endl;
}
