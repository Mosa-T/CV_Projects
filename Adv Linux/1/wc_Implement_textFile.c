#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define BUFF_SIZE 512

	int chars;
	int words;
	int lines;

void fileReader(char *from)
{
	int buff_read;
	char buff[BUFF_SIZE];
	int fd;
	int inWord = 0;
	int m_lines,m_words,m_chars;
	
	m_chars = m_words = m_lines = 0;
	
	//check if file is a directory
	if( ( fd = open(from,O_DIRECTORY |O_RDONLY) ) != -1)
	{
		printf("wc: %s Is a directory\n", from );
		printf("	0	0	0 %s\n",from);
		if(  close(fd) == -1)
		{
			perror(from);
			exit(EXIT_FAILURE);
		}
		return;
	}
   
	//open file
	if( ( fd = open(from,O_RDONLY) ) == -1)
  	{
		perror(from);
		exit(EXIT_FAILURE);
	}
	
	//read file and start counting 
	while( (buff_read = read(fd,buff,sizeof(buff))) !=0)
	{
		if(buff_read == -1)
		{
			perror(from);
			exit(EXIT_FAILURE);
		}
		for(int i = 0;i < buff_read ;i++){
      			if(!isspace(buff[i]))
      			{
        			if(!inWord)
        			{
          				inWord = 1;
        			}
      			}
      			else if(inWord){
        			m_words++;
        			inWord = 0;
      			}
      
			if(buff[i] == '\n')
      			{
				m_lines++;
        			if(inWord)
        			{
          				m_words++;
          				inWord = 0;
        			}
      			}
		}
     		if(inWord)
        	{
         		m_words++;
          		inWord = 0;
        	}
		m_chars = m_chars + buff_read;
	}
	printf("	%d	%d	%d %s\n",m_lines, m_words,m_chars,from);
	chars += m_chars;
	words += m_words;
	lines += m_lines;
	close(fd);
}


int main(int argc,char *argv[])
{
	FILE *fp = NULL;
	int ch;
	words = lines = chars = 0;
	fp = stdin; //never used as a file opener only for stdin thus no need to close.
	//in the case where the user doesn't give any args, we wait for the user to give us input in the terminal.	
	if(argc == 1){
		while ((ch = fgetc(fp)) != EOF) {
                	if (ch == '\n') {
                        	words++;
                        	lines++;
                	}

                	if (ch == '\t' || ch == ' ') {
                        	words++;
                	}

                	chars++;
        	}
		printf("	%d	%d	%d\n",lines, words,chars);
		return 0;	
	}
	
 	if(argc >= 2){
		for(int i=1; i < argc; i++)
		{
			fileReader(argv[i]);
		}
		if(argc > 2)
			printf("	%d	%d	%d total\n",lines, words,chars);
	}	
	return 0;
}
