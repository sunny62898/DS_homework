#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;		//�O���O��
	nodePointer next;	//�s��U�@�� 
};

struct headNode{
	int parent;		//�������L���e�n�������ƶq
	nodePointer next;	//�s��node 
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
	
	/*job�q1�}�l �ҥH�]job[0]����(���ϥ�)*/
	struct headNode job[jobNum+1];	//�إߨC��job��head
	
	
	/*�]�w��l��*/
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



