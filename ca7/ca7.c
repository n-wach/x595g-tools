#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//FLAG: flag{7cats_are_better_than_1}

struct by7e{
   unsigned int val : 7;
};

struct by7e reverse(struct by7e in) {
   struct by7e rev;

   for (int i = 0; i < 7; i++) {
      rev.val = rev.val * 2 + in.val % 2;
      in.val >>= 1;
   }

   return rev;
}

int main(int argc, char *argv[])
{
   if(argc < 2){
    fprintf(stderr, "include file to read");
    return 1;
   }
   
   FILE *fp = fopen(argv[1], "rb");

   if (fp == NULL) {
      fprintf(stderr, "cannot open input file\n");
      return 1;
      }
   fseek(fp, 0, SEEK_END); // seek to end of file
   int size = ftell(fp); // get current file pointer
   fseek(fp, 0, SEEK_SET); 
   size = size * 8 / 7;

   struct by7e nums[size];

   int c;
   int extra = 0;
   int place = 1;
   int count = 0;
   int mask[] = {0b00000000,0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111};

   while(count<size){
      c = getc(fp);
      nums[count].val = (extra << (8-place)) + (c >> place);
      nums[count] = reverse(nums[count]);
      
      printf("%c", nums[count].val);
      
      extra = c & mask[place];
      place += 1;
      if(place == 8) {
         count++;
         nums[count].val = extra;
         nums[count] = reverse(nums[count]);
         printf("%c", nums[count].val);
         extra = 0;
         place = 1;        
      }
      count++;
   }

   fclose(fp); 
   return 0;
}

/*
nums: extra << 7 + c >> 1
extra: c & 00000001

nums: extra << 6 + c >> 2
extra: c & 00000011

nums: extra << 5 + c >> 3
extra: c & 00000111

nums: extra << 4 + c >> 4
extra: c & 00001111

nums: extra << 3 + c >> 5
extra: c & 00011111

nums: extra << 2 + c >> 6
extra: c & 00111111

nums: extra << 1 + c >> 7
extra: c & 01111111

*/
