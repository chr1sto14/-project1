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
		//printf("%s",str);
		strcat(S, str); //collect input into a string
	}
	printf("%s\n",S);
	printf("length of S: %lu\n",strlen(S));
	printf("\n");

	int array[matSize][matSize];
	printf("a\n");
	int i = 0;
	int j = 0;
	int k = 0;
	while (S[k] != '\0') { //collect numbers into a matrix
		printf("S[k] = %c\n",S[k]);
		if ((S[k] == '\n') && (S[k+1]!='\n')) {	
			i++; //problem bc have two end of line chars (i is being updated to 3 when it should be 2
			j=0;
			printf("i++; j=0\n");
		}
		else if ((S[k] != ' ') && (S[k] != '\n')){
			printf("Add to mat\n");
			array[i][j] = S[k] - '0';
			printf("array[%d][%d] = %d\n",i,j,array[i][j]);
			j++;	
		}
		printf("update k\n"); 
		k++;	
	}
	printf("array[0][0]=%d\n",array[0][0]);
	
	//Print the matrix
	printf("printing matrix\n");
	for (int a = 0; a<matSize; a++) {
		for (int b=0; b<matSize; b++) {
			printf("array[%d][%d] = %d\n",a,b,array[a][b]);
		}
		printf("\n");
	}
	fclose(f);
}
