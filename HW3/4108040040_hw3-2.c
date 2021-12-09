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
void swap(nodePointer);
nodePointer combine(nodePointer);
void sum(nodePointer, int);

void test_print(nodePointer);
void preorder(nodePointer);

int Snumber = 0;

int main(){
	
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int col;	//行數
	char ch;
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
		
		//讀入字元並形成初始linklist 
		for(i = 0;i < col;i++){
			while(1){
				fscanf(fp, "%c", &ch);
				//printf("%c", ch);
				if(ch == '\n'){
					break;
				}
				
				exist = searchExist(head, ch);	//存在1 不存在0
				if(exist == 0){		//不存在 
					//如果沒出現過這個字元放入queue裡
					head = inputQueue(head, ch);
				}
				
			}
		}
		
		//test print 
		test_print(head);
		
		head = combine(head);
		preorder(head);
		
		sum(head, 0);
		printf("sum = %d\n", Snumber);
		
		
		
	} 
	
	
	
	fclose(fp);
	
	system("pause");
	return 0;
}


nodePointer inputQueue(nodePointer head, char ch){
	//新增新的節點
	/*加入新節點都加到第一個*/
	nodePointer node = (nodePointer)malloc(sizeof(struct node));
	node->word = ch;
	node->next = head;
	node->right = node->left = NULL;
	node->times = 1;
	
	head = node;
	
	return head;
}

int searchExist(nodePointer now, char ch){
	int exist = 0;
	while(now != NULL){
		if(now->word == ch){
			exist = 1;
			now->times++;
			swap(now);		//排序 
			return exist;
		}
		now = now->next;
	}
	return exist;
	
}

void swap(nodePointer now){		/*小到大*/ 
	nodePointer tempL = (nodePointer)malloc(sizeof(struct node));
	nodePointer tempR = (nodePointer)malloc(sizeof(struct node));
	int tempT;
	char tempC;
	
	while(now->next != NULL){
		if(now->times > now->next->times){
			tempL = now->left;
			tempR = now->right;
			tempT = now->times;
			tempC = now->word;
			
			
			now->left = now->next->left;
			now->right = now->next->right;
			now->times = now->next->times;
			now->word = now->next->word;
			
			now->next->left = tempL;
			now->next->right = tempR;
			now->next->times = tempT;
			now->next->word = tempC;
			
		}
		
		else{
			break;
		}
		
		now = now->next;
	}
	
}

nodePointer combine(nodePointer head){
	
	while(head->next != NULL){
		
		nodePointer temp = (nodePointer)malloc(sizeof(struct node));
		temp->word = NULL;
		temp->times = head->times + head->next->times;
		temp->left = head;
		temp->right = head->next;
		temp->next = head->next->next;
		
		head = temp;
		
		swap(head);
	}
	
	return head;
	
	
}

void sum(nodePointer now, int num){
	if(now != NULL){
		if(now->word != NULL){
			printf("sum = %c * %d\n", now->word, num);
			Snumber = Snumber + (num * (now->times));
		}
		num++;
		sum(now->left, num);
		sum(now->right, num);
		
	}
	
}





void test_print(nodePointer now){
	while(now != NULL){
		printf("%c\t%d\n", now->word, now->times);
		now = now->next;
	}
}

void preorder(nodePointer now){
	if(now != NULL){
		printf("%d\n", now->times);
		preorder(now->left);
		preorder(now->right);
		
	}
	
}




