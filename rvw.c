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

FILE *file;
char buff[1000];
WordArray words[10000];
FileArray files[3];

int main(int argc, char *argv[]){

	int wordCount = 0;
	int isUnique = 0;
	int arguments;

	for (int i = 1; i < argc; i++){
		if ( argc < 2){
			printf("usage %s filename", argv[0] );
		}

		else{

			file = fopen(argv[i], "r");
			if (file == NULL){
				printf("Couldn't open file\n");
			}
			else {
				while (fscanf(file, "%s", buff) != EOF)
				{
					wordCount++;
					printf("%s\n", buff);
					for (int k = 0; k < 300; k++){
						if (strcmp(words[k].word, buff) == 0){
							isUnique = 1;
						}
						if (isUnique != 1){
							strcpy(words[k].word, buff);
							words[k].frequency++;
						}
						else {
							words[k].frequency++;
						}
					}
				}
			
			fclose(file);
			}
		}
	}		
	
	
	printf("%s ", argv[1]);
	printf("%d \n", wordCount);

	return 0;
}