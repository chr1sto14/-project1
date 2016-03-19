#include <stdio.h>
#include <string.h>

int main() {
//**************************** Open the file ********************************
	FILE *f; //create file pointer
	f = fopen("sudokutest.txt", "r"); //open file
	if (f == NULL) {
		printf("Error: File not found\n");
		fclose(f);
	}
//***************************************************************************	
	int matSize = 4;
	char str[1000];
	char S[1000];
	while (fgets(str, 1000, f) != NULL) {
		strcat(S, str); //collect input into a string
	}
	printf("%s\n",S);

	int array[matSize][matSize];
	int i = 0;
	int j = 0;
	int k = 0;
	char out[1000];
	
	while (S[k] != '\0') { //collect numbers into a matrix
		if ((S[k] == '\n') && (S[k+1]!='\n')) {	
			i++; 
			j=0;
		}
		else if ((S[k] != ' ') && (S[k] != '\n')){
			array[i][j] = S[k] - '0';
			j++;	
		}
		k++;	
	}
	
	
	//Print the matrix
	printf("printing matrix\n");
	for (int a = 0; a<matSize; a++) {
		for (int b=0; b<matSize; b++) {
			printf("array[%d][%d] = %d\n",a,b,array[a][b]);
		}
		printf("\n");
	}
	
	//Need to change the c==0,2 and d==0,2,3 to automatically change depending on input size
	printf("FIX ME: print input file name\n");
	for (int c = 0; c<matSize; c++) {
		if (c==0)  {
			printf("-------------\n");
		}
		else if (c==2) {
			printf("------+------\n");
		}
		for (int d=0; d<matSize; d++) {
			if ((d==0) || (d==2)) {
				printf("| ");
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
					printf("%d ", array[c][d]);
				}
			}
			else if (d==3) {
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
				printf("%d ", array[c][d]);
				}
				printf("|\n");
			}
			else {
				if (array[c][d]==0) {
					printf(". ");
				}
				else {
				printf("%d ", array[c][d]);
				}
			}
		}
		if (c==3) {
			printf("-------------\n");	
		}
	}
	fclose(f);
}
