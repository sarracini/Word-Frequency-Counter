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

typedef struct {
	char word[101];
	int frequency;
} WordArray ;

typedef struct {
	WordArray file[3];
	char fileName[101];
	int frequency;
} FileArray ;

FileArray finalArray[101];

int compareWords(const void *f1, const void *f2){
	WordArray *a = (WordArray *)f1;
	WordArray *b = (WordArray *)f2;
	return (b->frequency - a->frequency);
}

int main(int argc, char *argv[]){

	int counter;
	int isUnique;
	int i;

	for (i = 1; i < argc; i++){
			
			FILE *file;
			char buff[1000];
			WordArray words[10000];
			FileArray files[3];
			counter = 0;

		if ( argc < 2){
			printf("usage %s filename invalid", argv[i]);
		}

		else{

			file = fopen(argv[i], "r");
			if (file == NULL){
				printf("Couldn't open file\n");
			}
			else {
				while ( (fscanf(file, "%s", buff)) != EOF)
				{
					isUnique = -1;

					for (int k = 0; k < counter; k++){
						if (strcmp(words[k].word, buff) == 0){
							isUnique = k;
						}
					}
					if (isUnique == -1){
						strcpy(words[counter].word, buff);
						words[counter].frequency = 1;
						counter++;
					}
					else {
						words[isUnique].frequency++;
					}	
				}	
			}
		}
		qsort(words, counter, sizeof(WordArray), compareWords);

		for (int m = 0; m < 3; m++){
			finalArray[i].file[m] = words[m];
		}
		finalArray[i].frequency = counter;
		strcpy(finalArray[i].fileName, argv[i]);
		fclose(file);
	}

	for (int j = 1; j < i; j++){
		if (finalArray[j].file[j].word != NULL){
			printf("FileName: %s ", finalArray[j].fileName);
			printf(" Unique Words: %d", finalArray[j].frequency);
			for (int l = 0; l < 3; l++){
				printf(" Word%d: %s", l+1, finalArray[j].file[l].word);
			}
			
		}
		printf("\n");
		
	}		
	
	return 0;
}