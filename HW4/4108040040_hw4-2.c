#include<stdio.h>
#include<stdlib.h>

int main(){

	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int pointNum, orderNum;
	fscanf(fp, "%d", &pointNum);	//可能需要出貨的地點數量 
	fscanf(fp, "%d", &orderNum);	//訂單需求的數量
	
	printf("%d %d\n", pointNum, orderNum);
	
	int i;
	int source, dist, cost;
	
	for(i = 0;i < pointNum-1;i++){
		fscanf(fp, "%d %d %d", &source, &dist, &cost);
		printf("%d %d %d\n", source, dist, cost);
	}
	
	int outset, number;
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d", &outset, &number);
		printf("%d %d\n", outset, number);
	}
	 
	
	
	
	fclose(fp);	

    system("pause");
    return 0;
}
