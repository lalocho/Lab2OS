#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 100

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
    int buffersize = SIZE;
    int position = 0;
    int charac;
    char** tokens = malloc(sizeof(char) * SIZE);
    char* token;
    while(1){
        
    }
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

