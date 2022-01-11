#include<stdio.h>
#include<stdlib.h>

/*
	上機考2-2 找倉庫設置最佳地點
	想法 : 利用order地點為起點出發走到每個點
		   並紀錄到每個點所需要的cost
		   將每筆訂單的cost相加 即為那點走過所有訂單所需要的花費
		   最後找出最小的並印出來	 
*/

typedef struct node* nodePointer;
typedef struct node{
	int cost;	//到這點的成本
	int number;	//這是哪一點
	nodePointer next;	//連到下一個 
};

struct dot{
	int pass;	//記錄有沒有被走過以及走到這點時用了多少cost 
	nodePointer next; 
};

void createMap(struct dot*, int, int, int);
void calSumCost(struct dot*, int*, int, int);


int main(){
	
	/*讀檔*/
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int nodeNum, orderNum;
	fscanf(fp, "%d %d", &nodeNum, &orderNum);
	
	int i, j;
	struct dot point[nodeNum+1];	//0不使用
	/*初始point*/
	for(i = 0;i < nodeNum+1;i++){
		point[i].pass = -1;
		point[i].next = NULL;
	}
	
	int sum[2][nodeNum+1];
	for(i = 0;i < nodeNum+1;i++){
		sum[0][i] = 0;
		sum[1][i] = 0;
	}
	
	int source, dist, pathcost;
	/*建立地圖*/
	for(i = 0;i < nodeNum-1;i++){
		fscanf(fp, "%d %d %d", &source, &dist, &pathcost);
		createMap(&point, source, dist, pathcost);
		
	}
	
	/*開始計算cost*/
	int begin, number;	//起點, 數量 
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d", &begin, &number);
		calSumCost(&point, &sum[1], begin, 0);
		
		for(j = 1;j < nodeNum+1;j++){
			
			sum[0][j] = sum[0][j] + sum[1][j] * number * 2;	//將剛剛計算的加到sum[0] 
			point[j].pass = -1;	//初始pass 
		}
		
	} 
	
	int minCost;
	int ans[nodeNum];
	int ansTop = 0;
	
	for(i = 1;i < nodeNum+1;i++){
		if(ansTop == 0){
			minCost = sum[0][i];
			ans[ansTop] = i;
			ansTop++;
		}
		else{
			if(minCost > sum[0][i]){
				minCost = sum[0][i];
				ansTop = 0;
				ans[ansTop] = i;
				ansTop++;
			}
			else if(minCost == sum[0][i]){
				ans[ansTop] = i;
				ansTop++;
			}
		}
	}
	
	/*印出答案*/
	printf("%d\n", minCost);
	for(i = 0;i < ansTop;i++){
		printf("%d ", ans[i]);
	}
	printf("\n");
	
	
	return 0;
}

void createMap(struct dot* array, int num1, int num2, int cost){
	nodePointer new1 = (nodePointer)malloc(sizeof(struct node));
	nodePointer new2 = (nodePointer)malloc(sizeof(struct node));
	
	new1->number = num1;
	new2->number = num2;
	new1->cost = new2->cost = cost;
	new1->next = new2->next = NULL;
	
	nodePointer now = array[0].next;
	/*連接新節點*/
	if(array[num1].next == NULL){
		array[num1].next = new2;
	}
	else{
		now = array[num1].next;
		while(now->next != NULL){
			now = now->next;
		}
		now->next = new2;
	}
	
	if(array[num2].next == NULL){
		array[num2].next = new1;
	}
	else{
		now = array[num2].next;
		while(now->next != NULL){
			now = now->next;
		}
		now->next = new1;
	}
	
}

void calSumCost(struct dot* point, int* sum, int num, int nowSum){
	point[num].pass = nowSum;
	*(sum+num) = nowSum;
	nodePointer now = point[num].next;
	
	while(now != NULL){
		if(point[now->number].pass == -1){	//沒被走過 
		
			calSumCost(point, sum, now->number, (nowSum+now->cost));
		}
		now = now->next;
	}
	
	
	
	
}
