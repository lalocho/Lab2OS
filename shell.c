/* Authors
 * Luis Ochoa
 * Jacob Padilla
 * 
 * This program emulates a shell that can take commands such as cd, exit, as well as pipes.
 * 
 * 
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#define SIZE  100
#define ESCAPE_CHARACTERS " \a\n\r\t"
char** parser(char* input);
int redirect(char** myargs);
int changeDir(char** input);
int redirect(char** myargs);
int exe(char** myargs);
void redirectIO(char** input);
char** parserPipe(char* input);
void pipeIT(char** inputA,char** inputB,char** allinput);

int redirect(char** myargs){
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
    if (WIFEXITED(wc)) {
        printf(" command not found");
    } 
    return WIFEXITED(wc);
  }
  return 0;

}
int exe(char** parsedCommand){
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if(rc == 0){
      int i = 0;
     
     if(execvp(parsedCommand[0], parsedCommand)){
      printf("command not found \n");
     };
  }
  else{
    int wc = wait(NULL);
    if (WIFEXITED(wc)) {
        printf(" command not found");
    } 
    return WIFEXITED(wc);
  }
  return 0;

}



int changeDir(char** input){
    char s[100];
    
    return chdir(input[1]);
    
}
void redirectIO(char** input){
      
}
void pipeIT(char** inputA,char** inputB,char** allinput){
     int pipefd[2];  
     pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("Pipe Failed\n"); 
        exit(0); 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("fork failed \n"); 
        return;
    } 
  
    if (p1 == 0) { 
        // this is child number 1
        // writing at t he end
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(inputA[0], inputA) != 0) { 
            printf("command not found\n."); 
            exit(0); 
        } 
    } else { 
        // Parent process
        p2 = fork(); 
        if (p2 < 0) { 
            printf("fork failed \n"); 
            return;
        } 
  
        // This is child number 2
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(allinput[0], inputB) < 0) { 
                printf("command not found"); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            int wc1 = wait(NULL); 
            int wc2 = wait(NULL); 
            if (WIFEXITED(wc1)||WIFEXITED(wc2)) {
                printf(" command not found");
    } 
        } 
    } 
}

char** parser(char* input){
  
  //initializing variables
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
char** parserPipe(char* input){
  int index= 0;
  char** word_array = malloc(sizeof(char) * (int)SIZE);
  char* word;

  word = strtok(input," |");
  
  while(word!= NULL){
    
    word_array[index] = word;
    index ++;
    word = strtok(NULL, "|");
    
    }
    if(word_array[1] == NULL){
        return NULL;
    }
  word_array[index] = NULL;
  return word_array;
}
/*
 * The main method has a loop that takes user input and decides what to do
 */
int main(){
  char *command;
  char **parsedCommand;
  int status=1;
  char *prompt;
  while(1){
    prompt = getenv("PS1");
    if(prompt == NULL){
        prompt = "$ ";
    }
    printf("%s",prompt);
    
    //reads input
    ssize_t bufsize=0;
    getline(&command, &bufsize, stdin);
    
    //checks first if command is piped, otherwise executes normally.
    parsedCommand = parserPipe(command);
    
    if(parsedCommand != NULL){
        printf("piped command");
        char* commandA = parsedCommand[0];
        char* commandB = parsedCommand[1];
        char** parsedCommandB = parser(commandB);
        char** parsedCommandA = parser(commandB);
        pipeIT(parsedCommandA,parsedCommandB,parsedCommand);
        
    }
    else{
    parsedCommand = parser(command);
    
    if(strcmp(parsedCommand[0],"exit") == 0){
        break;
    }else if(strcmp(parsedCommand[0] , "cd") == 0){
        status = changeDir(parsedCommand);
    }else if(strcmp(parsedCommand[0] , ">") == 0){
        break;
    }else if(strcmp(parsedCommand[0] , "|") == 0){
        redirectIO(parsedCommand);
    }else{
        status = exe(parsedCommand);
    }
    }
    if(status){
        printf("Program terminated with exit code : %d\n", status);
    }
    free(command);
    free(parsedCommand);
  } 
  printf("Program terminated with exit code : %d\n", status);
  exit(0);
}
