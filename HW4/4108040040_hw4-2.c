#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;
	int cost;
	nodePointer next;
};

struct dot{
	int pass;
	nodePointer next;
};

void createMap(struct dot*, int, int, int);
void dfs(struct dot*, int*, int, int);
void test(struct dot*, int);

int main(){

	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int pointNum, orderNum;
	fscanf(fp, "%d", &pointNum);	//可能需要出貨的地點數量 
	fscanf(fp, "%d", &orderNum);	//訂單需求的數量
	
	
	int i, j;
	struct dot point[pointNum+1];
	struct dot *pointer = &point;
	
	/*初始陣列*/
	for(i = 1;i < pointNum+1;i++){
		point[i].next = NULL;
		point[i].pass = -1;
	
	}
	
	int quantity[orderNum+1];	//紀錄訂單各要運送的數量 
	int costArray[2][pointNum+1];	//紀錄每個訂單到每一點的cost 
	for(i = 0;i < pointNum+1;i++){
		costArray[0][i] = costArray[1][i] = 0;
	} 
	int *Apointer = &costArray;
	
	int source, dist, cost;
	
	for(i = 0;i < pointNum-1;i++){
		fscanf(fp, "%d %d %d", &source, &dist, &cost);
		createMap(pointer, source, dist, cost);
	}
	
	int outset, number;
	int seq = 1;	//紀錄現在是在第幾個訂單 
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d", &outset, &number);
		quantity[seq] = number; 
		dfs(pointer, &costArray[1], outset, 0);
		/*初始map*/
		for(j = 1;j < pointNum+1;j++){
			point[j].pass = -1;
			costArray[0][j] += costArray[1][j] * number * 2;
		}
		seq++;
	}
	
	int minCost;
	int minPoint[pointNum];
	int top = 0;
	for(i = 1;i < pointNum+1;i++){
		
		/*比較是否為最小cost*/
		if(top == 0){
			minCost = costArray[0][i];
			minPoint[top] = i;
			top++;
		}
		else{
			if(costArray[0][i] < minCost){
				top = 0;
				minCost = costArray[0][i];
				minPoint[top] = i;
				top++;
			}
			else if(costArray[0][i] == minCost){
				minPoint[top] = i;
				top++;
			}
		}
	
	}
	
	/*print answer*/
	printf("%d\n", minCost);
	for(i = 0;i < top;i++){
		printf("%d ", minPoint[i]);
	}
	printf("\n");
	

	fclose(fp);	

    system("pause");
    return 0;
}


void createMap(struct dot* array, int num1, int num2, int cost){

	nodePointer new1 = (nodePointer)malloc(sizeof(struct node));
	nodePointer new2 = (nodePointer)malloc(sizeof(struct node));
	new1->number = num1;
	new2->number = num2;
	new1->cost = new2->cost = cost;
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

void dfs(struct dot* map, int* array , int source, int sum){
	//printf("cost = %d\n", *(array+source));
	if(map[source].pass != -1){
		return;
	}
	nodePointer now = map[source].next;		//接下來要走的點 
	*(array+source) = map[source].pass = sum;
	
	while(now != NULL){
		dfs(map, array, now->number, (now->cost+sum));
		now = now->next;
	}
	
	
}


void test(struct dot* array, int num){
	int i;
	nodePointer now = array[0].next;
	for(i = 1;i < num;i++){
		now = array[i].next;
		printf("%d = ", i);
		while(now != NULL){
			printf("%d ", now->cost);
			now = now->next;
		}
		printf("\n");
	}
}


