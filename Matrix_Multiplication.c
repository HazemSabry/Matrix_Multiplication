#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_FIRST_MATRIX_SURCE "a.txt"
#define DEFAULT_SECOND_MATRIX_SURCE "b.txt"
#define DEFAULT_RESULT_MATRIX_DESTINATION "c.txt"

int row1, col1, row2, col2;
int** matrix1;
int**  matrix2;

void read_matrix_from_file(char* file_name, int matrix_num){
	FILE* file;
	char* line;
	int row, col = 3;
	int** matrix;

	file = fopen(file_name, "r");
	if (file == NULL) {
		printf("File name \"%s\" not found in the direction.\n", file_name);
		exit(1);
	}
	fscanf(file, "row=%d col=%d", &row, &col);
	matrix = (int**) malloc(row * sizeof(int *));

	if (matrix == NULL) {
		printf("Memory allocation for matrix%d failed", matrix_num);
		exit(1);
	}
	for (int i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(col * sizeof(int));
		if (matrix[i] == NULL) {
			printf("Memory allocation for matrix%d[%d] failed", matrix_num, i);
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(file, "%d", &matrix[i][j]);
		}
	}
	fclose(file);

	if (matrix_num == 1) {
		row1 = row;
		col1 = col;
		matrix1 = (int**) malloc(row * sizeof(int *));
		if (matrix1 == NULL) {
			printf("Memory allocation for matrix%d failed", matrix_num);
			for (int i = 0; i < row; i++) {
				free(matrix[i]);
			}
			free(matrix);
			exit(1);
		}
		for (int i = 0; i < row; i++) {
			matrix1[i] = (int*)malloc(col * sizeof(int));
			if (matrix1[i] == NULL) {
				printf("Memory allocation for matrix%d[%d] failed", matrix_num, i);
				for (int j = 0; j < i; j++) {
					free(matrix1[j]);
				}
				free(matrix1);
				for (int i = 0; i < row; i++) {
					free(matrix[i]);
				}
				free(matrix);
				exit(1);
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix1[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < row; i++) {
			free(matrix[i]);
		}
		free(matrix);

		printf("row%d = %d ", matrix_num, row1);
		printf("col%d = %d\n", matrix_num, col1);
		printf("mattrix%d:\n", matrix_num);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%d\t", matrix1[i][j]);
			}
			printf("\n");
		}
	} else {
		row2 = row;
		col2 = col;
		matrix2 = (int**) malloc(row * sizeof(int *));
		if(matrix2 == NULL){
			printf("Memory allocation for matrix%d failed", matrix_num);
			for (int i = 0; i < col; i++) {
				free(matrix[i]);
			}
			free(matrix);
			exit(1);
		}
		for (int i = 0; i < row; i++) {
			matrix2[i] = (int*)malloc(col * sizeof(int));
			if (matrix2[i] == NULL) {
				printf("Memory allocation for matrix%d[%d] failed", matrix_num, i);
				for (int j = 0; j < i; j++) {
					free(matrix2[j]);
				}
				free(matrix2);
				for (int i = 0; i < row; i++) {
					free(matrix[i]);
				}
				free(matrix);
				exit(1);
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix2[i][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < row; i++) {
			free(matrix[i]);
		}
		free(matrix);

		printf("row%d = %d ", matrix_num, row2);
		printf("col%d = %d\n", matrix_num, col2);
		printf("mattrix%d:\n", matrix_num);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%d\t", matrix2[i][j]);
			}
			printf("\n");
		}
	}
}

int main(int argc, char* args[]){
	char* sources_destination [3] = {
					 DEFAULT_FIRST_MATRIX_SURCE,
					 DEFAULT_SECOND_MATRIX_SURCE,
					 DEFAULT_RESULT_MATRIX_DESTINATION
					};
	if (argc > 4) {
		printf("Too many arguments\n");
		exit(1);
	}
	for (int i = 1; i < argc; i++){
		sources_destination[i-1] = args[i];
	}

	read_matrix_from_file(sources_destination[0], 1);
	read_matrix_from_file(sources_destination[1], 2);
	return 0;
}
