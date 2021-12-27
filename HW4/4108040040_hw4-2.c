#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;
	nodePointer next;
};

struct dot{
	int pass;
	nodePointer next;
};

void createMap(struct dot*, int, int);
void test(struct dot*, int);

int main(){

	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int pointNum, orderNum;
	fscanf(fp, "%d", &pointNum);	//可能需要出貨的地點數量 
	fscanf(fp, "%d", &orderNum);	//訂單需求的數量
	
	printf("%d %d\n", pointNum, orderNum);
	
	int i;
	struct dot point[pointNum+1];
	struct dot *pointer = &point;

	/*初始陣列*/
	for(i = 1;i < pointNum+1;i++){
		point[i].next = NULL;
		point[i].pass = 0;
	}
	

	int source, dist, cost;
	
	for(i = 0;i < pointNum-1;i++){
		fscanf(fp, "%d %d %d", &source, &dist, &cost);
		printf("%d %d %d\n", source, dist, cost);
		createMap(pointer, source, dist);
	}
	
	int outset, number;
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d", &outset, &number);
		printf("%d %d\n", outset, number);
	}
	 
	/*test print*/

	test(pointer, pointNum+1);
	
	
	fclose(fp);	

    system("pause");
    return 0;
}


void createMap(struct dot* array, int num1, int num2){

	nodePointer new1 = (nodePointer)malloc(sizeof(struct node));
	nodePointer new2 = (nodePointer)malloc(sizeof(struct node));
	new1->number = num1;
	new2->number = num2;
	new1->next = new2->next = NULL;
	
	if(array[num1].next == NULL){
		array[num1].next = new2;
	}
	else{
		nodePointer now1 = array[num1].next;
		while(now1->next != NULL){
			now1 = now1->next;
		}
		now1->next = new2;
	}
	
	
	if(array[num2].next == NULL){
		array[num2].next = new1;
	}
	else{
		nodePointer now2 = array[num2].next;
		while(now2->next != NULL){
			now2 = now2->next;
		}
		now2->next = new1;
	}
}

void test(struct dot* array, int num){
	int i;
	nodePointer now = array[0].next;
	for(i = 1;i < num;i++){
		now = array[i].next;
		printf("%d = ", i);
		while(now != NULL){
			printf("%d ", now->number);
			now = now->next;
		}
		printf("\n");
	}
}


