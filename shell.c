#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define SIZE 100
//#define ESCAPE_CHARACTER " \t\r\a\n"

char* takeInput();
char** tokenizer();


char* takeInput(void){
    
    int position=0;
    char *buffer = malloc(sizeof(char) * SIZE);
    int charac;
    while(1){
     charac = getchar();
     if(charac == EOF || charac == '\n'){
         buffer[position] = '\0';
         return buffer;
     }else{
      buffer[position] == charac;   
     }
     position+1;
    }

}
char** tokenizer(char* input){
  //int buffersize = SIZE;
  int index= 0;
  int charac;
  char** word_array = malloc(sizeof(char) * SIZE);
  char* word;

  word = strtok(input," \t\a\r\n");
      
  while(word){
    word_array[index] = word;
    index ++;
    word = strtok(NULL, "\t\a\r\n");
    }
  word_array[index] = NULL;
  return word_array;
}

int main(int argc, char **argv){
  
  char* prompt;
  while(1){
    prompt = getenv("PS1");
    if(!prompt){
        printf("$");
    }else{
    printf("%s",prompt);
    }
    char* input = takeInput();
  }
}

