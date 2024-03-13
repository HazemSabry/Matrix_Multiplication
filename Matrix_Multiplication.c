#include <stdio.h>
#include <string.h>
#define DEFAULT_FIRST_MATRIX_SURCE "a.txt"
#define DEFAULT_SECOND_MATRIX_SURCE "b.txt"
#define DEFAULT_RESULT_MATRIX_DESTINATION "c.txt"


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
	//printf("%s", sources_destination[0]);
	//printf("%s", sources_destination[1]);
	//printf("%s", sources_destination[2]);
	return 0;
}
