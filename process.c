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

#define READ 0
#define WRITE 1

typedef struct {
	char word[101];
	int frequency;
} WordArray ;

WordArray words[1000];

int compareWords(const void *f1, const void *f2){
	WordArray *a = (WordArray *)f1;
	WordArray *b = (WordArray *)f2;
	return (b->frequency - a->frequency);
}

char *countFrequency(char *fileName){
	
	int counter = 0;
	int isUnique;
	FILE *file;
	char buff[10000];

	file = fopen(fileName, "r");

	if (file == NULL){
		printf("Couldn't open file: ");
	}
	
	else {
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
	}	
	// Sort the words to find most frequent words
	qsort(words, counter, sizeof(WordArray), compareWords);

	// Store the 3 more frequent words as the result, as a single string
	char *result = (char*)malloc(sizeof(result)*100);
	snprintf(result, 10000, "%s %d %s %s %s", fileName, counter, words[0].word, words[1].word, words[2].word);
	fclose(file);
	return result;
}

int main(int argc, char *argv[]){
	
	int fd[argc-1][2];
	pid_t child;
	char *buff = (char*)malloc(sizeof(char));
	char *res = (char*)malloc(sizeof(char));
	int i, j, k;

	// Check if user has inputed correct amount of arguments
	if (argc < 2){
		fprintf(stderr, "usage %s filename invalid", argv[1]);
		exit(0);
	}

	// If user has inputed correct amount of arguments, continue with execution
	else {
		for (i = 1; i <= argc -1; i++){
			// Create a new pipe and fork one child per argument passed in by user
			pipe(fd[i]);
			child = fork();

			if (child < 0){
				perror("Error");
			}
			// Child process sends each file's 3 most frequent words to parent
			else if (child == 0){
				res = countFrequency(argv[i]);
				close(fd[i][READ]);
				write(fd[i][WRITE], res, (strlen(res) +1) );
				close(fd[i][WRITE]);
				exit(0);
			}
		}
		// Wait for children to return to parent
		for(k = 1; k <= argc - 1; k++){
			wait(NULL);
		}
		// Parent process reads from child process and prints out results
		for(j = 1; j <= argc - 1; j++){
			close(fd[j][WRITE]);
			read(fd[j][READ], buff, sizeof(char*)* (strlen(buff) + 100000) );
			close(fd[j][READ]);
			printf("%s\n", buff);
		}
	}
		
	return 0;
}

