#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;		//記錄是誰
	nodePointer next;	//連到下一個 
};

struct headNode{
	int parent;		//紀錄做他之前要先做的數量
	int pass;
	nodePointer next;	//連到node 
};


struct headNode connect(struct headNode, int);
void calParent(struct headNode*, struct headNode);


int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");
	
	int jobNum, relation;
	int i, j;
	
	fscanf(fp, "%d", &jobNum);
	fscanf(fp, "%d", &relation);
	
	/*job從1開始 所以設job[0]為空(不使用)*/
	struct headNode job[jobNum+1];	//建立每個job的head
	struct headNode* jobPointer = job;
	
	
	/*設定初始值*/
	for(i = 1;i < jobNum+1;i++){
		job[i].parent = 0;
		job[i].pass = 0;
		job[i].next = NULL;
	}
	
	int before, after;
	
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d", &before);
		fscanf(fp, "%d", &after);
	
		job[before] = connect(job[before], after);
		job[after].parent += 1;
		
	}
	
	int ans[jobNum];	//存答案的array 
	int ansNum = 0;
	int cycle = 1;
	for(i = 0;i < jobNum;i++){
		for(j = 1;j < jobNum+1;j++){
			if(job[j].parent == 0 && job[j].pass == 0){		//前面沒有事情要做且沒走過 
				job[j].pass = 1;	//標示走過
				ans[ansNum] = j;
				ansNum++;
				calParent(jobPointer, job[j]);
				cycle = 0;
				break;
			}
			else{
				cycle = 1;
			}
		}
		if(cycle == 1){
			printf("not exist");
			break;
		}
	}
	
	if(cycle != 1){
		for(i = 0;i < jobNum;i++){
			printf("%d ", ans[i]);
		}
	}
	printf("\n");
	
	fclose(fp);
	system("pause");
	return 0;
}


struct headNode connect(struct headNode head, int num){
	nodePointer now = head.next;
	nodePointer NewNode = (nodePointer)malloc(sizeof(struct node));
	NewNode->next = NULL;
	NewNode->number = num;
	
	if(now == NULL){
		
		head.next = NewNode;
	}
	else{
		while(now->next != NULL){
			now = now->next;
		}
		
		now->next = NewNode;
	}
	
	return head;
}

void calParent(struct headNode* array, struct headNode head){
	nodePointer now = head.next;
	while(now != NULL){
		array[now->number].parent -= 1; 
		now = now->next;
	}
}



