#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
char** parser(char* input);
int redirect(char** myargs);
void changeDir(char** input);
int exe(char** myargs){
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if(rc == 0){
   
    execvp(myargs[0], myargs);
  }
  else{
    int wc = wait(NULL);
  }
  return 0;
 
}
 
int main(){
  char *command;
  char **parsedCommand;
  int status;
  char *prompt;
  do {
    prompt = getenv("PS1");
    if(!prompt){
        printf("$");
    }else{
    printf("%s",prompt);
    }
    //reads input
    ssize_t bufsize=0;
    getline(&command, &bufsize, stdin);
   
    parsedCommand = parser(command);
    if(strcmp(parsedCommand[0],"exit") == 0){
        break;
    }else if(strcmp(parsedCommand[0] , "cd") == 0){
        changeDir(parsedCommand);
    }else if(strcmp(parsedCommand[0] , ">") == 0){
        break;
    }else if(strcmp(parsedCommand[0] , "|") == 0){
        break;
    }else{
        exe(parsedCommand);
    }
   
 
    free(command);
    //free(args);
  } while (1);
}
void changeDir(char** input){
    char s[100];
   
    chdir(input[1]);
    printf("%s", getcwd(s,100));
}
void redirectIO(char** input){
   
}
void pipeIT(char** input){
   
}
#define SIZE  100
#define ESCAPE_CHARACTERS " \a\n\r\t"
char** parser(char* input){
  int index= 0;
  char** word_array = malloc(sizeof(char) * (int)SIZE);
  char* word;
 
  word = strtok(input,ESCAPE_CHARACTERS);
 
  while(word!= NULL){
   
    word_array[index] = word;
    index ++;
    word = strtok(NULL, ESCAPE_CHARACTERS);
   
    }
  word_array[index] = NULL;
  return word_array;
}
