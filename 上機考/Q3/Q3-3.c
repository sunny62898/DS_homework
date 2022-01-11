#include<stdio.h>
#include<stdlib.h>

/*
	上機考3-3 overcook
	想法 : 用一個for去跑時間i = 0開始
		   一開始讀檔讀進來先用linked list去串連加排序
		   再開始跑時間
		   當開始做的時候就不能放棄
		   時間每跑一格 就去看有沒有一些單來不及做(將他去掉)
		   之後再從可以做得選出所需時間最短的來製作
		   (僅提供試試) 
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
	fscanf(fp, "%d", &orderNum);	//讀取訂單數量
	
	nodePointer head = NULL;
	
	//讀取訂單 
	int i;
	int order, arrival, deadline, time;
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d %d %d", &order, &arrival, &deadline, &time);
		printf("%d %d %d %d\n", order, arrival, deadline, time);
		head = createQueue(head, arrival, deadline, time);
	}
	
	test(head);
	
	/*找最後的時間(deadline最大的)*/
	
	
	
	
	return 0;
}

nodePointer createQueue(nodePointer head, int arrival, int deadline, int time){
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->arrival = arrival;
	newNode->cookTime = time;
	newNode->deadline = deadline;
	
	newNode->next = head;	//每次加都加到第一個
	head = newNode;
	
	sorting(head);	//進行排序 

	
	return head;
}

void sorting(nodePointer now){	//依照arrival 由小到大排序 
	
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
