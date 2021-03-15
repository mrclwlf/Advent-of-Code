#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
jmp_buf buf;

struct Vector {
	
	int size;
	int length; //elements in the vector
	int *data;
};

void add(int element, struct Vector *vector) {
	

	if(vector->length < vector->size)
		vector->data[vector->length] = element;
	else{
		int new_size = vector->size * 2;
		if(NULL == (vector->data = (int*)realloc(vector->data,sizeof(int) * new_size)))
			longjmp(buf,1);
		vector->size = new_size;
		vector->data[vector->length] = element;
	}
	
	vector->length++;
}

void print_vector(struct Vector *vector) {
	printf("Vector = [ ");
	for(int i = 0; vector->length > i; i++)
		printf("%d, ",vector->data[i]);
	printf("]\n");
}


int main(int argc, char **argv){
	
	if(argc < 2){
		printf("use: ./main <filename>\n");
		return 0;
	}

	char* file= argv[1];
	int element;
	struct Vector vector;
	FILE *fptr;

	vector.size = 1;
	vector.length = 0;
	if(NULL == (vector.data = (int*)malloc(sizeof(int)*1))){
		printf("Cannot alloacate memory");
		return -1;
	}
	
	if(setjmp(buf)){
		printf("Cannot reallocate memory");
		return -1;
	}

	if(NULL == (fptr = fopen(file,"r"))){
		printf("Cannot open file %s\n", file);
		return 0;
	}

	while(1){

		fscanf(fptr,"%d", &element);
		if(feof(fptr))
			break;
		add(element, &vector);

	}

	for(int i = 0; vector.length > i++;){
		for(int j = i+1; vector.length > j; j++) {
			for(int k = j+1; vector.length > k; k++) {
				if(vector.data[i] + vector.data[j] + vector.data[k]== 2020)
					printf("%d\n", vector.data[i] * vector.data[j] * vector.data[k]);

			}
		}
	}
			       
	//print_vector(&vector);
	fclose(fptr);
	free(vector.data);
	return 0;
}
	
