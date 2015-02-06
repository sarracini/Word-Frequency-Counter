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
#include <pthread.h>
#include <unistd.h>

typedef struct {
	char word[101];
	int frequency;
} WordArray ;

int compareWords(const void *f1, const void *f2){
	WordArray *a = (WordArray *)f1;
	WordArray *b = (WordArray *)f2;
	return (b->frequency - a->frequency);
}

void countFrequency(void *arg){
	
	char *fileName = (char*)malloc(sizeof(char));
	fileName = (char*)arg;
	WordArray *words = (WordArray*)calloc((1000),sizeof(WordArray));
	char *result = (char*)malloc(sizeof(result)*100);
	int counter = 0;
	int isUnique;
	int i = 0;
	FILE *file;
	char buff[1000];

	// Clear the array, so threads don't modify the program after they've been created
	for (i = 0; i < sizeof(WordArray); i++){
		words[i].word[0] = '\0';
		words[i].frequency = 0;
	}

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
			// Re-allocate memory for the array
			words = realloc(words, (sizeof(*words) + counter) * sizeof(WordArray));	
		}
	}

	// Sort the words to find most frequent words
	qsort(words, counter, sizeof(WordArray), compareWords);
	// Store the 3 more frequent words as the result, as a single string and then print that string
	snprintf(result, 10000, "%s %d %s %s %s", fileName, counter, words[0].word, words[1].word, words[2].word);
	fclose(file);
	printf("%s\n", result);

}

int main(int argc, char *argv[]){
	
	// Declare threads and default attributes
	pthread_t threads[argc-1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// Run all threads concurrently
	int i;
	for (i = 1; i < argc; i++){
		char* arguments = (char*)malloc(sizeof(argv[i])+1);
		arguments = argv[i];
		// Create a new thread for every argument passed in by the user, and count word frequency for each
		pthread_create(&threads[i], &attr, (void*) countFrequency, (void*) arguments);
	}
	for (i = 1; i < argc; i++){
		// Join threads to avoid memory leaks
		pthread_join(threads[i], NULL);
	}

	return 0;
}

