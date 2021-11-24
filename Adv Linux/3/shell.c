/** 	Mosa Thoukwho
		311590707
		shell
**/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>

#define BUFFER_SIZE 1024
#define BUFFER_SIZE_OF_TOKEN 64
#define DELIM_OF_TOKEN " \t\r\n\a"
#define FAIL -1
#define TRUE 1
#define FALSE 0


int launch(char** );
int run_in_bg = 0, input=-1, out=-1;
int i  = 0;
char* in_file;
char* out_file;
int background_count = 0;
char lastDir[BUFFER_SIZE];
char *lineSave;

void cd(char *path){
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    char *s = "/";
    char *newpath;
    char cwd[BUFFER_SIZE];
    char *c;

    if (path != NULL && strcmp(path, "-") == 0)
    { //return to last directory
        if (chdir(lastDir) == FAIL)
        {
            perror("chdir-lastdir");
            return;
        }
    }
    else
    {
        if (getcwd(lastDir, sizeof(lastDir)) == NULL)
        {
            perror("getcwd");
            return;
        }
        if (path == NULL || (strcmp(path, "~") == 0))
        {
            if (chdir(homedir) == FAIL)
            {
                perror("chdir-homedir");
                return;
            }
        }
        else
        {
            if (path[0] == '/')
            {
                if (chdir(path) == FAIL)
                {
                    perror("chdir-fullpath");
                    return;
                }
            }
            else
            {
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                {
                    perror("getcwd");
                    return;
                }
                c = &cwd[0];
                newpath = (char *)malloc(sizeof(char) * (strlen(path) + strlen(c) + 2));
                strcat(newpath, c);
                strcat(newpath, s);
                strcat(newpath, path);
                if (chdir(newpath) == FAIL)
                {
                    perror("chdir-newpath");
                    free(newpath);
                    return;
                }
                free(newpath);
            }
        }
    }
}

void handle_in_out_file(char **args){
        
		while(args[i]!=NULL){i++;}
		if(args[i-1][0]=='&'){
					run_in_bg = 1;
					background_count++;
					args[i-1] = NULL;
				}
		i = 0;
		while(args[i]!= NULL){
                if(args[i][0]=='<')
                        {
                                input = i;
                                in_file=args[i+1];
                        }
                 if(args[i][0]=='>')
                        {
                                out = i;
                                out_file=args[i+1];
                        }
                        i++;
        }
		
}

void in_file_handle(char **args){
	
	pid_t pid2;
	int status2;
	if(run_in_bg == 1){
			run_in_bg = 0;
			if(pid2 = fork() == 0){ //grandchild
				if(args[input][0]=='<') {             
					args[input] = "--color=auto";	
				}
				close(0);
				if(open(in_file,O_RDONLY,0766)==-1){
					perror("open from err");
					exit(1);
				}
				input = -1;
				if(execvp(args[0],args) == -1){
					perror("error in executing program");
					exit(1);
				}
				exit(1);
			}
			else{ do {
				
					waitpid(pid2, &status2, WUNTRACED);
					if ( WIFEXITED(status2) != 0 ) {
						int es = WEXITSTATUS(status2);
					}
				} while (!WIFEXITED(status2) && !WIFSIGNALED(status2));
				printf("[%d]+	DoneIn	%s\n? ",background_count,lineSave);
				run_in_bg = 0;
				background_count--;
				input = -1;
				exit(1);
			}
	}
		
		
		if(args[input][0]=='<') {             
			args[input] = "--color=auto";	
		}
		close(0);
		input = -1;
        if(open(in_file,O_RDONLY,0766)==-1){
            perror("open from err");
            exit(1);
        }
		if(execvp(args[0],args) == -1){
			perror("error in executing program");
            exit(1);
        }
}


void out_file_handle(char **args){
	
		 pid_t pid2;
		 int status2;
		 if(run_in_bg == 1){
			 run_in_bg = 0;
			if(pid2 = fork() == 0){ //grandchild
			printf("[%d]	%d\n",background_count,getppid());
				 if(args[out][0]=='>'){                
					args[out] = NULL;
					args[out+1] = NULL;
				}
				out = -1;
				close(1);
				if(open(out_file , O_RDWR | O_CREAT | O_TRUNC,0766)==-1){
					perror("open from err");
					exit(1);
				}
				out = -1;
				if(execvp(args[0],args) == -1){
					perror("error in executing program");
					exit(1);
				}
				exit(1);
			}
			else{ do {
					waitpid(pid2, &status2, WUNTRACED);
					if ( WIFEXITED(status2) != 0 ) {
						int es = WEXITSTATUS(status2);
					}
				} while (!WIFEXITED(status2) && !WIFSIGNALED(status2));
				printf("[%d]+	DoneOut	%s\n? ",background_count,lineSave);
				run_in_bg = 0;
				out = -1;
				background_count--;
				exit(1);
			}
			
		}
		
		
		 if(args[out][0]=='>'){                
			args[out] = NULL;
            args[out+1] = NULL;
		}
		out = -1;
		close(1);
            if(open(out_file , O_RDWR | O_CREAT | O_TRUNC,0766)==-1){
					perror("open from err");
					exit(1);
				}
				out = -1;
				if(execvp(args[0],args) == -1){
					perror("error in executing program");
					exit(1);
				}
		out = -1;
		exit(1);
}





void inAndOut(char **args){
	
		 pid_t pid2;
		 int status2;
		 if(run_in_bg == 1){
			 run_in_bg = 0;
			if(pid2 = fork() == 0){ //grandchild
			printf("[%d]	%d\n",background_count,getppid());
				 if(args[out][0]=='>'){                
					args[out] = NULL;
					args[out+1] = NULL;
				}
				if(args[input][0]=='<') {             
					args[input] = "--color=auto";	
				}
				close(0);
				if(open(in_file,O_RDONLY,0766)==-1){
					perror("open from err");
					exit(1);
				}
				input = -1;
				out = -1;
				close(1);
				if(open(out_file , O_RDWR | O_CREAT | O_TRUNC,0766)==-1){
					perror("open from err");
					exit(1);
				}
				out = -1;
				if(execvp(args[0],args) == -1){
					perror("error in executing program");
					exit(1);
				}
			}
			else{ do {
					waitpid(pid2, &status2, WUNTRACED);
					if ( WIFEXITED(status2) != 0 ) {
						int es = WEXITSTATUS(status2);
					}
				} while (!WIFEXITED(status2) && !WIFSIGNALED(status2));
				printf("[%d]+	DoneOut	%s\n? ",background_count,lineSave);
				run_in_bg = 0;
				out = -1;
				input = -1;
				background_count--;
				exit(1);
			}		
		} 
			 if(args[out][0]=='>'){                
					args[out] = NULL;
					args[out+1] = NULL;
				}
				if(args[input][0]=='<') {             
					args[input] = "--color=auto";	
				}
				close(0);
				if(open(in_file,O_RDONLY,0766)==-1){
					perror("open from err");
					exit(1);
				}
				input = -1;
				out = -1;
				close(1);
				if(open(out_file , O_RDWR | O_CREAT | O_TRUNC,0766)==-1){
					perror("open from err");
					exit(1);
				}
				out = -1;
				if(execvp(args[0],args) == -1){
					perror("error in executing program");
					exit(1);
				}
	
}







void error_allocation(){
        fprintf(stderr, "failed memmory allocation\n");
}

int launch(char **args)
{
  pid_t pid;
  pid_t pid2;
  int status;
  int status2;
  handle_in_out_file(args);
  fflush(0);
  pid = fork();
  if (pid == 0) { // Child process
 
		 if(run_in_bg == 1){
			 
			 
			 
		if(input !=-1 && out!=-1){
			inAndOut(args);
		} 

			 if (input!=-1){
						in_file_handle(args);
					} 
					if (out!=-1){
						out_file_handle(args);
					}
					run_in_bg = 0;
			if(pid2 = fork() == 0){ //grandchild
			printf("[%d]	%d\n",background_count,getppid());
					if (execvp(args[0], args) == -1) {
						perror("execvp");
					}
				exit(1);
			}
			else {
				do {
					waitpid(pid, &status, WUNTRACED);
					if ( WIFEXITED(status) != 0 ) {
						int es = WEXITSTATUS(status);
					}
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				printf("[%d]+	DoneLaunch	%s\n? ",background_count,lineSave);
				run_in_bg = 0;
				background_count--;
				out = -1;
				input = -1;
				exit(1);
			}
		}
		
		if(input !=-1 && out!=-1){
			inAndOut(args);
		}
		 
		 if (input!=-1){
            in_file_handle(args);
		}
		if (out!=-1){
			out_file_handle(args);
		}
		if (execvp(args[0], args) == -1) {
			perror("execvp");
		}
		exit(1);
	}
	else if (pid < 0) {
			perror("Error forking");
		}
	else { // Parent prog

			if(run_in_bg == 0){
				do {
					waitpid(pid, &status, WUNTRACED);
					if ( WIFEXITED(status) != 0 ) {
						int es = WEXITSTATUS(status);
					}
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				out = -1;
				input = -1;
				//background_count--;
			} 
			else{ 
				out = -1;
				input = -1;
			}
			
    }
  return 1;
}


char *read_command()
{
	int size = BUFFER_SIZE, curser = 0,c;
	char *buff = malloc(sizeof(char) * size);
	if (!buff) {
		error_allocation();
		exit(1);
	}
	while (1) {
		c = getchar();
		if(c == '\n' &&  curser == 0){
			buff[curser] = c;
			return buff;
		}
		if (c == '\n') {
			buff[curser] = '\0';
			return buff;
		}
		if (c == EOF) {
			buff[curser] = '\0';
			return buff;
		}
        else {
			buff[curser] = c;
		}
		curser++;
		if ( size <= curser) {
			size += BUFFER_SIZE;
			buff = realloc(buff, size);
			if (!buff) {
				error_allocation();
				exit(1);
			}
		}
  }
}

char **command_token(char *line)
{
  int size = BUFFER_SIZE_OF_TOKEN, curser = 0;
  char **toks = malloc(size * sizeof(char*));
  char *token;
  if (!toks) {
    error_allocation();
    exit(1);
  }
  token = strtok(line, DELIM_OF_TOKEN);
  while (token != NULL) {
		toks[curser] = token;
		curser++;
		if ( size <= curser) {
			size += BUFFER_SIZE_OF_TOKEN;
			toks = realloc(toks, size * sizeof(char*));
			if (!toks) {
				error_allocation();
				exit(1);
			}
		}
		token = strtok(NULL, DELIM_OF_TOKEN);
  }
  toks[curser] = NULL;
  return toks;
}


int main(int argc, char **argv){
   char *line;
   char **args;
   int size = BUFFER_SIZE, curser = 0,c;
	lineSave = malloc(sizeof(char) * size);
   if (getcwd(&lastDir[0], sizeof(lastDir)) == NULL){
		perror("getcwd");
        exit(EXIT_FAILURE);
    }
   printf("Welcome to Mosa's shell\n");
   do{
		printf("? ");
		line = read_command();
		strcpy(lineSave,line);
		args = command_token(line);
		if(line[0] == '\n'){}
		else
		if (args[0] == NULL || args[0][0] == ' ' || args[0] [0]== '\t' || args[0][0]== '\0'){  //empty command
				printf("\n");
        } else 
			if (strcmp(args[0], "exit") == 0){
				exit(EXIT_SUCCESS);
			} else
        if(strcmp(args[0],"cd")==0){  //cd command
            if (args[1] == NULL) {
                fprintf(stderr, "missing args - cd\n");
            }
            else {
				cd(args[1]);   
            }
        }
        else{
		    launch(args);
			i  = 0;
			out = -1;
			input = -1;
			run_in_bg = 0;
			free(line);
			free(args);
		}
	} while (1);
	free(lineSave);
   return 0;
}

