#include <stdio.h>
#include <string.h>

int main() {
	FILE *f; //create file pointer
	f = fopen("sudokutest.txt", "r"); //open file
	if (f == NULL) {
		printf("Error: File not found\n");
		fclose(f);
	}
	
	char str[1000];
	char S[1000];
	while (fgets(str, 1000, f) != NULL) {
		//printf("%s",str);
		strcat(S, str);
	}
	//int array[4] = {(int col1[4]) (int col2[4]) (int col3[4]) (int col4[4])};
	int array[4][4];
	int i = 0;
	int j = 0;
	for (int k=0; i<strlen(S);i++) {
		if (S[k] == '\n') {
			i++;
			j=0;
		}
		if (S[k] != ' '){
			array[i][j] = S[k];
			j++;	
		} 	
	}
	printf("%s\n",S);
	for (int i=0;i<strlen(array);i++) {
		printf(array[i]);	
	}
	
	fclose(f);
}
