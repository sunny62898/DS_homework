#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
	上機考2-1 singly linked list
	有五個功能
	1. add i 插入i到最後一個 
	2. del i 刪除第i個
	3. ins i j 插入j到第i個的後面
	4. rev k 以k個為一組進行反轉
	5. show 顯示出目前的linked list 
*/

typedef struct listNode *listPointer;
typedef struct listNode{
	int data;
	listPointer link;
};

int whichcom(char*);
listPointer add(listPointer, int);
listPointer del(listPointer, int);
void insert(listPointer, int, int);
void rev(listPointer, int);
void show(listPointer);

int main(){
	
	/*讀檔*/
	FILE *fp;
	
	fp = fopen("input_1.txt", "r");
	int nodeNum, comNum;
	
	fscanf(fp, "%d %d", &nodeNum, &comNum);
	
	int i;
	int num;
	listPointer head = NULL;
	
	for(i = 0;i < nodeNum;i++){
		fscanf(fp, "%d", &num);
		head = add(head, num);
	}
	
	char com[4];
	int number;
	int num1, num2;
	for(i = 0;i < comNum;i++){
		
		fscanf(fp, "%s", com);
		if(strlen(com) < 1){
			i--;
			continue;
		}
		number = whichcom(com);
		if(number == 1){		//add
			//printf("add\n");
			fscanf(fp, "%d", &num1);
			head = add(head, num1);
		}
		else if(number == 2){	//del
			//printf("del\n");
			fscanf(fp, "%d", &num1);
			head = del(head, num1);
		}
		else if(number == 3){	//ins
			//printf("ins\n");
			fscanf(fp, "%d %d", &num1, &num2);
			insert(head, num1, num2);
		}
		else if(number == 4){	//rev
			//printf("rev\n");
			fscanf(fp, "%d", &num1);
			rev(head, num1);
		}
		else if(number == 5){	//show
			//printf("show\n");
			show(head);
		}
		
	}
	
	
	return 0;
}

int whichcom(char* com){
	if(strcmp(com, "add") == 0){
		return 1;
	}
	else if(strcmp(com, "del") == 0){
		return 2;
	}
	else if(strcmp(com, "ins") == 0){
		return 3;
	}
	else if(strcmp(com, "rev") == 0){
		return 4;
	}
	else if(strcmp(com, "show") == 0){
		return 5;
	}
	else{
		return 0;
	}
}

listPointer add(listPointer head, int num){
	listPointer newNode = (listPointer)malloc(sizeof(struct listNode));
	newNode->data = num;
	newNode->link = NULL;
	
	if(head != NULL){
		listPointer now = head;
	
		while(now->link != NULL){
			now = now->link;
		}
		
		now->link = newNode;
	}
	else{
		head = newNode;
	}
	
	return head;
	
}

listPointer del(listPointer head, int num){
	int count = 0;
	listPointer now = head;
	if(num == 1){	//刪除第一個 
		head = now->link;
	}
	
	else{
		listPointer parent = head;
		now = now->link;
		count = 1;
		while(now != NULL){
			count++;
			if(count == num){
				parent->link = now->link;
				
			}
			parent = now;
			now = now->link;
		}
	}
	return head;
}

void insert(listPointer head, int num, int addnum){
	int count = 0;
	listPointer now = head;
	listPointer newNode = (listPointer)malloc(sizeof(struct listNode));
	newNode->data = addnum;
	
	while(now != NULL){
		count++;
		if(count == num){
			newNode->link = now->link;
			now->link = newNode;
			return;
		}
		now = now->link;
	}
	return;
	
}

void rev(listPointer head, int num){
	int array[num];
	int top = 0;
	
	listPointer now = head;
	
	while(now != NULL){
		array[top] = now->data;
		now = now->link;
		top++;
		
		if(top == num){
			
			break;
		}
		
	}
	
	int i;
	listPointer head2 = head;
	for(i = top-1;i >= 0;i--){
		//printf("%d %d\n", i, array[i]);
		head2->data = array[i];
		head2 = head2->link;
	}
	if(now != NULL){
		rev(now, num);
	}
	
	
}

void show(listPointer head){
	listPointer now = head;
	while(now != NULL){
		printf("%d ", now->data);
		now = now->link;
	}
	printf("\n");
}
