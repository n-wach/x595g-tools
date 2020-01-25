#include <iostream>

int POS = 0;

void read(char* buf, int n) {
  std::cin.get(&buf[0], n);
  POS += n;
}

uint32_t readWord() {
  char wT[1];
  read(wT, 1);
  std::cout << "read w0: " << (int) wT[0] << std::endl;

  char word[4];
  read(word, 4);

  std::cout << "w0:" << (int)word[0] << " w1:" << (int)word[1] << " w2:" << (int)word[2] << " w3:" << (int)word[3] << std::endl;
  uint32_t val = word[0] | (word[1] << 7) | (word[2] << 14) | (word[3] << 21);
  return val;
}

bool readBool() {
  char b;
  read(&b, 1);
  return b == '\x1';
}

std::string readString() {
  std::string res;
  char c;
  read(&c, 1);
  while (c != '\0') {
    res += c;
    read(&c, 1);
  }
  return res;
}

int main() {
  char head1[5];
  read(head1, 5);

  char fileType = head1[4];
  std::cout << "FileType: " << ((fileType == '\0') ? "EXE" : "OBJ") << std::endl;

  bool hasEntryPoint = readBool();
  std::cout << "HasEntryPoint: " << (hasEntryPoint ? "NO" : "YES") << std::endl;
  
  if(hasEntryPoint) {
    uint32_t entryPoint = readWord();
    std::cout << "EntryPoint: " << entryPoint << std::endl;
  }

  std::cout << "pos: " << POS << std::endl;
  uint32_t numEntries = readWord();
  std::cout << numEntries << " symbols." << std::endl;
  std::string symbolName = readString();
  std::cout << "symbol 0 name: " << symbolName;
}
