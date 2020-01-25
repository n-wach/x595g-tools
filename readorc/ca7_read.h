#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct by7e {
   unsigned int val : 7;
};

typedef struct by7e B7;

struct by7e reverse(struct by7e in) {
   struct by7e rev;

   for (int i = 0; i < 7; i++) {
      rev.val = rev.val * 2 + in.val % 2;
      in.val >>= 1;
   }

   return rev;
}

struct by7e* read7File(char* fn)
{
   FILE *fp = fopen(fn, "rb");

   if (fp == NULL) {
      fprintf(stderr, "cannot open input file\n");
      return NULL;
    }
   fseek(fp, 0, SEEK_END); // seek to end of file
   int size = ftell(fp); // get current file pointer
   fseek(fp, 0, SEEK_SET);
   size = size * 8 / 7;

//    struct by7e nums[size];
    struct by7e* nums = (struct by7e*) malloc(size * sizeof(struct by7e));

   int c;
   int extra = 0;
   int place = 1;
   int count = 0;
   int mask[] = {0b00000000,0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111};

   while(count<size){
      c = getc(fp);
      nums[count].val = (extra << (8-place)) + (c >> place);
      nums[count] = reverse(nums[count]);
      
    //   printf("%c", nums[count].val);
      
      extra = c & mask[place];
      place += 1;
      if(place == 8) {
         count++;
         nums[count].val = extra;
         nums[count] = reverse(nums[count]);
        //  printf("%c", nums[count].val);
         extra = 0;
         place = 1;        
      }
      count++;
   }

   fclose(fp); 
   return nums;
}
