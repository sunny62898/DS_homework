#include<stdio.h>
#include<stdlib.h>

void test(int *array);

int main(){
	
	int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int *ptr = &array;
	
	test(ptr);
	
	system("pause");
	return 0;
}

void test(int *array){
	
	printf("%d\n", array+4);
}


