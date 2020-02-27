#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#define SIZE 100
//#define ESCAPE_CHARACTER " \t\r\a\n"
int redirect();
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

int redirect(){
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if(rc == 0){
    close(SDTOUT_FILENO);
    open("./p4-output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    char *myargs[3];
    myargs[0] = strdup("WC");
    myargs[1] = strdup("redirect.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);
  }
  else{
    int wc = wait(NULL);
  }
  return 0;

}

int main(int argc, char *argv[]){
  
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

