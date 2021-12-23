#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;		//記錄是誰
	nodePointer next;	//連到下一個 
};

struct headNode{
	int parent;		//紀錄做他之前要先做的數量
	nodePointer next;	//連到node 
};

struct headNode connect(struct headNode, int);


int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");
	
	int jobNum, relation;
	int i;
	
	fscanf(fp, "%d", &jobNum);
	fscanf(fp, "%d", &relation);
	
	printf("%d %d\n", jobNum, relation);
	
	/*job從1開始 所以設job[0]為空(不使用)*/
	struct headNode job[jobNum+1];	//建立每個job的head
	
	
	/*設定初始值*/
	for(i = 1;i < jobNum+1;i++){
		job[i].parent = 0;
		job[i].next = NULL;
	}
	
	int before, after;
	
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d", &before);
		fscanf(fp, "%d", &after);
		
		printf("%d %d\n", before, after);
	
		job[before] = connect(job[before], after);
		job[after].parent += 1;
		
	}
	
	/*test print*/ 
	for(i = 1;i < jobNum+1;i++){
		if(job[i].next != NULL){
			printf("%d = %d\n", i, job[i].next->number);
		}
		printf("%d = %d\n", i, job[i].parent);
	}
	
	
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



