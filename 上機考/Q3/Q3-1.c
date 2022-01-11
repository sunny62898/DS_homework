#include<stdio.h>
#include<stdlib.h>
/*
	上機考3-1 Topology sort
	想法 : 先建立struct來記錄每個點前置工作數量
		   以及連接在此工作之後才能做的工作
		   每一次做完一個工作的時候會將他所連接的工作們的前置數量-1
		   去搜尋有沒有工作的前置數量為0就去做它 
*/

typedef struct node* nodePointer;
typedef struct node{
	int number;
	nodePointer next;
};

struct headNode{
	int before;
	nodePointer next;
};

void createMap(struct headNode*, int, int);
void deBefore(struct headNode*, int);


int main(){
	
	FILE* fp;
	fp = fopen("input_1.txt", "r");
	
	int i, j;
	int jobNum, relation;
	fscanf(fp, "%d %d", &jobNum, &relation);
	
	struct headNode job[jobNum+1];	//0不使用
	for(i = 0;i < jobNum+1;i++){
		job[i].before = 0;
		job[i].next = NULL;
	}
	
	
	/*建立地圖*/
	int before, after;
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d %d", &before, &after);
		createMap(&job, before, after);
	}
	 
	
	
	/*開始做工作*/
	int cycle = 1;
	int ans[jobNum];
	int ansTop = 0;
	for(i = 0;i < jobNum;i++){
		cycle = 1;
		for(j = 1;j < jobNum+1;j++){
			if(job[j].before == 0){
				ans[ansTop] = j;
				ansTop++;
				deBefore(&job, j);
				job[j].before = -1;
				cycle = 0;
				break;
			} 
		}
		if(cycle == 1){
			break;
		}
	}
	
	/*印出答案*/
	if(cycle == 1){
		printf("not exist");
	}
	else{
		for(i = 0;i < ansTop;i++){
			printf("%d ", ans[i]);
		}
	}
	
	printf("\n");
	return 0;
}

void createMap(struct headNode* array, int before, int after){
	/*建立新節點*/
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->number = after;
	newNode->next = NULL;
	
	/*插入節點*/
	if(array[before].next == NULL){
		array[before].next = newNode;
	}
	else{
		nodePointer now = array[before].next;
		while(now->next != NULL){
			now = now->next;
		}
		now->next = newNode;
	}
	
	/*將後做的點的before+1*/
	array[after].before = array[after].before + 1;
		
}

void deBefore(struct headNode* array, int num){
	nodePointer now = array[num].next;
	
	while(now != NULL){
		array[now->number].before -= 1;
		now = now->next;
	}
}
