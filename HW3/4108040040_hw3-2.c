#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	char word;
	int times;
	nodePointer next;
	nodePointer left;
	nodePointer right;
};

nodePointer inputQueue(nodePointer, char);
int searchExist(nodePointer, char);

void test_print(nodePointer);

int main(){
	
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int col;	//行數
	char array[1000000];
	char ch;
	nodePointer queue[1000];
	int i;
	int exist;
	nodePointer head;
	
	while(1){
		
		fscanf(fp, "%d", &col);
		printf("%d\n", col);
		fscanf(fp, "%c", &ch);	//讀掉多的\n 
		
		if(col == 0){
			break;
		}
		
		head = NULL;
		
		for(i = 0;i < col;i++){
			while(1){
				fscanf(fp, "%c", &ch);
				//printf("%c", ch);
				if(ch == '\n'){
					break;
				}
				
				if(head == NULL){	//第一個直接放 
					head = inputQueue(head, ch);
				}
				else{
					exist = searchExist(head, ch);	//存在1 不存在0
					if(exist == 0){		//不存在 
						//如果沒出現過這個字元放入queue裡
						head = inputQueue(head, ch);
					}
				}
				
				
			}
		
		}
		
		//test print 
		//test_print(head);
		
	} 
	
	
	
	fclose(fp);
	
	system("pause");
	return 0;
}


nodePointer inputQueue(nodePointer head, char ch){
	//新增新的節點
	nodePointer node; 
	node->word = ch;
	node->next = node->right = node->left = NULL;
	node->times = 1;
	
	if(head == NULL){
		head = node;
	}
	
	else{
		nodePointer now = head;
		while(now->next != NULL){
			now = now->next;		//找最後一點 
		}
		
		now->next = node;
	}
	
	return head;
}

int searchExist(nodePointer now, char ch){
	int exist = 0;
	while(now != NULL){
		if(now->word == ch){
			exist = 1;
			now->times++;
			return exist;
		}
		now = now->next;
	}
	return exist;
	
}

void test_print(nodePointer now){
	while(now != NULL){
		printf("%c\t%d\n", now->word, now->times);
		now = now->next;
	}
}



