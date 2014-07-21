/*
 * Systems Programming Homework#01
 *
 * 101044045
 * Muhammed Maruf KILIC
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define ARRAYSIZE 2048

/*	function prototype						*/
/*	This function takes 2 parameter			*/
/*	fromfd: file pointer of given file		*/
/*	keyString: word to search				*/
void grepM(FILE* open_file_name, char* keyString);


/* function definitions 					*/
int main(int argc, char *argv[]) {
	
	FILE* open_file_name;
	pid_t childpid = 0;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s file_name search_key\n", argv[0]);
		return 1;
	}

	/*	opening to file in read mode 	*/
	if ((open_file_name = fopen(argv[1], "r")) == NULL) {
		perror("Failed to open input file");
		return 1;
	}
	
	/*	creating child		*/
	childpid = fork();
	
	if(childpid == -1){
		perror("Failed to fork");
		return 1;
	}

	
	if(childpid == 0){
		grepM(open_file_name,argv[2]);
		return 0;
	}
	else{
		/*	father is waiting his child		*/
		wait();
	}
	
	/*	close file	*/
	fclose(open_file_name);
	

	/* 	return		*/
	return 0;


}


void grepM(FILE* open_file_name, char* key_string) {
	
	char buffer_of_line[ARRAYSIZE];
	int i , j;	/*these are counters	*/

	int line_number = 1;
	int number_total_key = 0;
	int counter_myString = 0;
	int counter_of_line = 0;

	/*	while end of the file 			*/
	while (fgets(buffer_of_line, ARRAYSIZE , open_file_name) != NULL)
	{
		/*	for end of line				*/
		for(i=0; buffer_of_line[i] != '\n'; ++i)
		{
			counter_of_line = i;
			
			for(j=0; key_string != '\0'; ++j)
			{
				counter_myString = j;
				if(buffer_of_line[counter_of_line++] != key_string[counter_myString])
					break;
				
			}
			
			if(key_string[counter_myString] == '\0'){
				printf("#line number is : %d\n",line_number);
				number_total_key++;
			}
						
		}
	
		++line_number;
		
	}

	printf("#there are %d of %s in this file\n\n",number_total_key,key_string);


}

