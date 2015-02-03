/**
 ** Sarracini
 ** Ursula
 ** Section Z
 ** 211535432
 ** CSE13208
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

// A structure for the words
typedef struct {
	char word[101];
	int frequency;
} WordArray ;

WordArray words[10000];

int compareWords(const void *f1, const void *f2){
	WordArray *a = (WordArray *)f1;
	WordArray *b = (WordArray *)f2;
	return (b->frequency - a->frequency);
}

char *countFreq(char *string){
	int counter;
	int isUnique;
	int i;
	FILE *file;
	char buff[1000];
	counter = 0;
	
	file = fopen(string, "r");
	while ( (fscanf(file, "%s", buff)) != EOF)
	{
		isUnique = -1;

		// String comparison - to check if the word is already in the array
		int k;
		for (k = 0; k < counter; k++){
			if (strcmp(words[k].word, buff) == 0){
				isUnique = k;
			}
		}
		// If the string is not in the array, put it in the array
		if (isUnique == -1){
			strcpy(words[counter].word, buff);
			words[counter].frequency = 1;
			counter++;
		}
		// Increase frequency of non-unique words
		else {
			words[isUnique].frequency++;
		}	
	}	
	// Sort the words to find most frequent words
	qsort(words, counter, sizeof(WordArray), compareWords);

	// Store the 3 more frequent words as the result, as a single string
	char *result = malloc(1000);
	snprintf(result, 100, "%s %d %s %s %s", string, counter, words[0].word, words[1].word, words[2].word);
	fclose(file);
	return result;
}

int main(int argc, char *argv[]){

	int fd[2];
	int fde[2];
	pid_t child;
	char buff[100];
	char tmpbuff[100];
	pipe(fd);
	pipe(fde);
	
	int i;
	for (i = 1; i <= argc - 1; i++){
		child = fork();
		write(fd[1], argv[i], 100);
	}

	if (child < 0){
		perror("Error");
	}
	else if (child > 0){
		close(fd[0]);
		close(fde[1]);
		read(fde[0], tmpbuff, 100);
		printf("%s\n", tmpbuff);
		
		// parent stuff
	}
	else {
		close(fd[1]);
		close(fde[0]);
		read(fd[0], buff, 100);
		char *res = countFreq(buff);
		write(fde[1], res, 100);
		exit(0);
		//child stuff
	}


	
	

	return 0;
}

