#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	int number;		//�O���O��
	nodePointer next;	//�s��U�@�� 
};

struct headNode{
	int parent;		//�������L���e�n�������ƶq
	int pass;
	nodePointer next;	//�s��node 
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
	
	/*job�q1�}�l �ҥH�]job[0]����(���ϥ�)*/
	struct headNode job[jobNum+1];	//�إߨC��job��head
	struct headNode* jobPointer = job;
	
	
	/*�]�w��l��*/
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
	
	int ans[jobNum];	//�s���ת�array 
	int ansNum = 0;
	int cycle = 1;
	for(i = 0;i < jobNum;i++){
		for(j = 1;j < jobNum+1;j++){
			if(job[j].parent == 0 && job[j].pass == 0){		//�e���S���Ʊ��n���B�S���L 
				job[j].pass = 1;	//�Хܨ��L
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



