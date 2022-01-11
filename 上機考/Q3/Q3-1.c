#include<stdio.h>
#include<stdlib.h>
/*
	�W����3-1 Topology sort
	�Q�k : ���إ�struct�ӰO���C���I�e�m�u�@�ƶq
		   �H�γs���b���u�@����~�వ���u�@
		   �C�@�������@�Ӥu�@���ɭԷ|�N�L�ҳs�����u�@�̪��e�m�ƶq-1
		   �h�j�M���S���u�@���e�m�ƶq��0�N�h���� 
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
	
	struct headNode job[jobNum+1];	//0���ϥ�
	for(i = 0;i < jobNum+1;i++){
		job[i].before = 0;
		job[i].next = NULL;
	}
	
	
	/*�إߦa��*/
	int before, after;
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d %d", &before, &after);
		createMap(&job, before, after);
	}
	 
	
	
	/*�}�l���u�@*/
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
	
	/*�L�X����*/
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
	/*�إ߷s�`�I*/
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->number = after;
	newNode->next = NULL;
	
	/*���J�`�I*/
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
	
	/*�N�ᰵ���I��before+1*/
	array[after].before = array[after].before + 1;
		
}

void deBefore(struct headNode* array, int num){
	nodePointer now = array[num].next;
	
	while(now != NULL){
		array[now->number].before -= 1;
		now = now->next;
	}
}
