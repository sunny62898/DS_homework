#include<stdio.h>
#include<stdlib.h>

/*
	�W����3-3 overcook
	�Q�k : �Τ@��for�h�]�ɶ�i = 0�}�l
		   �@�}�lŪ��Ū�i�ӥ���linked list�h��s�[�Ƨ�
		   �A�}�l�]�ɶ�
		   ��}�l�����ɭԴN������
		   �ɶ��C�]�@�� �N�h�ݦ��S���@�ǳ�Ӥ��ΰ�(�N�L�h��)
		   ����A�q�i�H���o��X�һݮɶ��̵u���ӻs�@
		   (�ȴ��Ѹո�) 
*/

typedef struct node* nodePointer;
typedef struct node{
	int arrival;
	int deadline;
	int cookTime;
	nodePointer next;
};

nodePointer createQueue(nodePointer, int, int, int);
void sorting(nodePointer);
void swap(nodePointer, nodePointer);
void test(nodePointer);
//int findMaxDeadline()

int main(){
	
	FILE* fp;
	fp = fopen("input_3.txt", "r");
	
	int orderNum;
	fscanf(fp, "%d", &orderNum);	//Ū���q��ƶq
	
	nodePointer head = NULL;
	
	//Ū���q�� 
	int i;
	int order, arrival, deadline, time;
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d %d %d", &order, &arrival, &deadline, &time);
		printf("%d %d %d %d\n", order, arrival, deadline, time);
		head = createQueue(head, arrival, deadline, time);
	}
	
	test(head);
	
	/*��̫᪺�ɶ�(deadline�̤j��)*/
	
	
	
	
	return 0;
}

nodePointer createQueue(nodePointer head, int arrival, int deadline, int time){
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->arrival = arrival;
	newNode->cookTime = time;
	newNode->deadline = deadline;
	
	newNode->next = head;	//�C���[���[��Ĥ@��
	head = newNode;
	
	sorting(head);	//�i��Ƨ� 

	
	return head;
}

void sorting(nodePointer now){	//�̷�arrival �Ѥp��j�Ƨ� 
	
	/*1.arrival 2.cookTime 3.deadline*/
	
	while(now->next != NULL){
		if(now->arrival > now->next->arrival){
			swap(now, now->next);
		}
		else if(now->arrival == now->next->arrival){
			if(now->cookTime > now->next->cookTime){
				swap(now, now->next);
			}
			else if(now->cookTime == now->next->cookTime){
				if(now->deadline > now->next->deadline){
					swap(now, now->next);
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
		else{
			break;
		}
		now = now->next;
	}
	
}

void swap(nodePointer now1, nodePointer now2){
	int tempA, tempD, tempC;
	tempA = now1->arrival;
	tempD = now1->deadline;
	tempC = now1->cookTime;
	
	now1->arrival = now2->arrival;
	now1->deadline = now2->deadline;
	now1->cookTime = now2->cookTime;
	
	now2->arrival = tempA;
	now2->deadline = tempD;
	now2->cookTime = tempC; 
}

void test(nodePointer now){
	while(now != NULL){
		printf("%d %d %d\n", now->arrival, now->deadline, now->cookTime);
		now = now->next;
	}
}
