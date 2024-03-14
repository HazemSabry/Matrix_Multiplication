#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define DEFAULT_FIRST_MATRIX_SURCE "a.txt"
#define DEFAULT_SECOND_MATRIX_SURCE "b.txt"
#define DEFAULT_RESULT_MATRIX_DESTINATION "c.txt"

typedef struct {
    int row;
    int col;
} thread_args_t;


int row1, col1, row2, col2;
int** matrix1;
int** matrix2;
int** result_matrix;

void free_space (int** mtrx, int row) {
	for (int i = 0; i < row; i++) {
		free(mtrx[i]);
	}
	free(mtrx);
}

void read_matrix_from_file(char* file_name, int matrix_num){
	FILE* file;
	char* line;
	int row, col = 3;
	int** matrix;

//	sprintf(file_name + strlen(file_name),".txt");
//printf("%s\n",file_name);
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
			free_space(matrix, i);
			exit(1);
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
			free_space(matrix, row);
			exit(1);
		}
		for (int i = 0; i < row; i++) {
			matrix1[i] = (int*)malloc(col * sizeof(int));
			if (matrix1[i] == NULL) {
				printf("Memory allocation for matrix%d[%d] failed", matrix_num, i);
				free_space(matrix1, i);
				free_space(matrix, row);
				exit(1);
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix1[i][j] = matrix[i][j];
			}
		}
		free_space(matrix, row);

	} else {
		row2 = row;
		col2 = col;
		matrix2 = (int**) malloc(row * sizeof(int *));
		if(matrix2 == NULL){
			printf("Memory allocation for matrix%d failed", matrix_num);
			free_space(matrix, row);
			free_space(matrix1, row1);
			exit(1);
		}
		for (int i = 0; i < row; i++) {
			matrix2[i] = (int*)malloc(col * sizeof(int));
			if (matrix2[i] == NULL) {
				printf("Memory allocation for matrix%d[%d] failed", matrix_num, i);
				free_space(matrix2, i);
				free_space(matrix, row);
				free_space(matrix1, row1);
				exit(1);
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix2[i][j] = matrix[i][j];
			}
		}
		free_space(matrix, row);
	}
}

void result_matrix_allocate_memory (void) {
	if (col1 != row2) {
		printf("Number of colums in the first matrix not equal number of rows in the second matrix");
		free_space(matrix1, row1);
		free_space(matrix2, row2);
		exit(0);
	}

	result_matrix = (int**) malloc(row1 * sizeof(int*));
	if (result_matrix == NULL) {
		printf("Memory allocation for the result matrix failed");
		free_space(matrix1, row1);
		free_space(matrix2, row2);
		exit(1);
	}
	for (int i = 0; i < row1; i++) {
		result_matrix[i] = (int*)malloc(col2 * sizeof(int));
		if (result_matrix[i] == NULL) {
			printf("Memory allocation for result_matrix[%d] failed", i);
			free_space(result_matrix, i);
			free_space(matrix1, row1);
			free_space(matrix2, row2);
			exit(1);
		}
	}
}

void write_on_file (char* file_name) {
	FILE* file = fopen(file_name, "w");
	if (file == NULL) {
		printf("Failed to create the file \"%s\"\n", file_name);
		free_space(result_matrix, row1);
		free_space(matrix1, row1);
		free_space(matrix2, row2);
		exit(1);
	}
	
	fprintf(file, "row1 = %d ", row1);
	fprintf(file, "col2 = %d\n", col2);
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			fprintf(file, "%d\t", result_matrix[i][j]);
		}
		fprintf(file, "\n");
	}
	
	printf("row1 = %d ", row1);
	printf("col2 = %d\n", col2);
	printf("result mattrix:\n");
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			printf("%d\t", result_matrix[i][j]);
		}
		printf("\n");
	}
}

void mult_per_matrix(void) {
	int temp;

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			temp = 0;
			for (int u = 0; u < row2; u++) {
				temp += (matrix1[i][u] * matrix2[u][j]);
			}
			result_matrix[i][j] = temp;
		}
	}
	write_on_file("c_per_matrix.txt");
}

void* multiply_row(void* arg) {
	int row = *((int *)arg);
	int temp;

	for (int j = 0; j < col2; j++) {
		temp = 0;
		for (int u = 0; u < row2; u++) {
			temp += (matrix1[row][u] * matrix2[u][j]);
		}
		result_matrix[row][j] = temp;
	}

	pthread_exit(NULL);
}

void mult_per_row (void) {
	pthread_t threads[row1];
	int thread_args[row1];
	int num_threads = 0;

	for (int i = 0; i < row1; i++) {
		thread_args[num_threads] = i;
		pthread_create(&threads[num_threads], NULL, multiply_row, &thread_args[num_threads]);
		num_threads++;
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	write_on_file("c_per_row.txt");
}

void *multiply_element(void *arg) {
	thread_args_t *args = (thread_args_t *)arg;
	int row = args->row;
	int col = args->col;
	int temp = 0;

	for (int u = 0; u < row2; u++) {
		temp += (matrix1[row][u] * matrix2[u][col]);
	}
	result_matrix[row][col] = temp;

	pthread_exit(NULL);
}

void mult_per_element (void) {
	pthread_t threads[row1 * col2];
	thread_args_t thread_args[row1][col2];
	int num_threads = 0;

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			thread_args[i][j].row = i;
			thread_args[i][j].col = j;
			pthread_create(&threads[num_threads], NULL, multiply_element, &thread_args[i][j]);
			num_threads++;
		}
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	write_on_file("c_per_element.txt");
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
	result_matrix_allocate_memory();
//	mult_per_matrix();
//	mult_per_row();
	mult_per_element();

	free_space(result_matrix, row1);
	free_space(matrix1, row1);
	free_space(matrix2, row2);

	return 0;
}
