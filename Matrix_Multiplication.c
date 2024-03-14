#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_FIRST_MATRIX_SURCE "a.txt"
#define DEFAULT_SECOND_MATRIX_SURCE "b.txt"
#define DEFAULT_RESULT_MATRIX_DESTINATION "c.txt"

int row1, col1, row2, col2;
int** matrix1, matrix2;

void read_matrix_from_file(char* file_name, int matrix_num){
	FILE* file;
	char* line;
	int row, col = 3;
	int** matrix;

	file = fopen(file_name, "r");
	if(file == NULL){
		printf("File name \"%s\" not found in the direction.\n", file_name);
		exit(1);
	}
	fscanf(file, "row=%d col=%d", &row, &col);
	matrix = (int**) malloc(row * sizeof(int *));
	for (int i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(col * sizeof(int));
	}
	if(matrix == NULL){
		printf("Memory allocation for matrix%d failed", matrix_num);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(file, "%d", &matrix[i][j]);
		}
	}
	fclose(file);

	printf("row%d = %d\n", matrix_num, row);
	printf("col%d = %d\n", matrix_num, col);
	printf("mattrix%d:\n", matrix_num);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	
}

int main(int argc, char* args[]){
	char* sources_destination [3] = {
					 DEFAULT_FIRST_MATRIX_SURCE,
					 DEFAULT_SECOND_MATRIX_SURCE,
					 DEFAULT_RESULT_MATRIX_DESTINATION
					};
	//printf("%d", argc);
	for (int i = 1; i < argc; i++){
		sources_destination[i-1] = args[i];
	}
	printf("%s\n", sources_destination[0]);
	//printf("%s", sources_destination[1]);
	//printf("%s", sources_destination[2]);

	read_matrix_from_file(sources_destination[0], 1);
	return 0;
}
