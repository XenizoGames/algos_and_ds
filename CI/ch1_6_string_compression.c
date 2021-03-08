#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------
//1.6 string compression
//-----------------
//Simple string compression aabccccaaa would become a2b1c5a3
//If compressed string not smaller then original then return original
//Assume - only upper and lowercase a-z letters in the string

// T: O(n) S: O(m) - loop through all characters once in a string, compressed string created

char int_to_char(char val)
{
  if (val < 10 && val >= 0)
  {
    //int to ascii
    return val + '0';
  }
  //for now return 9 when more then 9 consecutive...lossy ehh :)
  return '9';
}
//Assume caller will free the memory
//Assume ascii
char * compress_string(char str[])
{
  int len = strlen(str);
  char current = str[0];
  int char_count = 0;
  char * compressed = malloc(sizeof(char) * len); //string same length as uncompressed
  int index = 0;
  for (int i = 0; i < len; i++)
  {
    //handle initial case and different case
    //printf("\ncurrent %c str[i] %c index %d char_count %d",current,str[i],index,char_count);
    if (current != str[i])
    {
      //different character
      //compress and move forward
      compressed[index]   = current;
      compressed[index+1] = int_to_char(char_count+1); //0-based to 1-based
      index += 2;
      current = str[i];
      char_count = 0;
    }
    else
    {
      char_count++;
    }
  }

  //Check if there are leftovers to write
  if (char_count > 0)
  {
    compressed[index]   = current;
    compressed[index+1] = int_to_char(char_count+1);
    index += 2;   
  }

  //printf("\nindex %d len %d",index,len);
  if (index < len)
  {
    compressed[index] = '\0';
    return compressed;
  }
  else
  {
    //return malloc'd string so you have to free() no matter what
    //i.e. if compressed, or orig string would be returned
    compressed = str;
    return compressed;
  }
}

int main() {    
  char testString[] = "aabccccccccaaaaaabbbbbbaaaadddddhhhaaajjjjjjjssssiiiiiiiaa";
  
  printf("\nINPUT : test string %s",testString);
  printf("\nRESULT: Compressed String %s ",compress_string(testString));
  
  return 0;
}