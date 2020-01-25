#include <iostream>

int readWord() {
  char word[4];
  std::cin.get(&word[0], 4);

  int val = word[0] | (word[1] << 7) | (word[2] << 14) | (word[3] << 21);
  return val;
}

bool readBool() {
  char b;
  std::cin.get(b);
  return b == '\x1';
}

std::string readString()

int main() {
  char head1[5];
  std::cin.get(&head1[0], 5);

  char fileType = head1[4];
  std::cout << "FileType: " << ((fileType == '\0') ? "EXE" : "OBJ") << std::endl;

  bool hasEntryPoint = readBool();
  std::cout << "HasEntryPoint: " << (hasEntryPoint ? "NO" : "YES") << std::endl;
  
  if(hasEntryPoint) {
    int entryPoint = readWord();
    std::cout << "EntryPoint: " << entryPoint << std::endl;
  }


}


