#include<stdio.h>
#include<stdlib.h>

/*
	上機考3-1 Huffman code
	想法 : 先讀入這題有幾行字串(如果讀到0就break)
		   再依照所規定的行數去讀取字串
		   建立struct去存取left, right, next, char, times(等等在struct說明)
		   將讀到的字元放入queue中(其中字元不重複)
		   如果找到重複的那就他的times+1，再把他丟去排序 
		   接下來開始合併節點
		   因為在建立queue時已經有排序過，所以就直接拿前面兩個進行合併 
		   合併完之後一樣丟去排序
		   (一直循環這樣的步驟，直到只剩下一個節點)
		   去計算總共所花了多少byte(用遞迴) 
*/

typedef struct node* nodePointer;
typedef struct node{
	int times;	//累加記錄次數
	char character;	//記錄這是哪個字元(如果是之後合併所產生的node，那就會是NULL)
	nodePointer next;	//queue的下一個
	nodePointer left;	//用來合併所產生的tree left
	nodePointer right;	//用來合併所產生的tree right 
};

int existfun(nodePointer, char);
void swap(nodePointer);
nodePointer inputQueue(nodePointer, char);
nodePointer combine(nodePointer);
void sum(nodePointer, int);

int Sans;

int main(){
	
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int strNum;
	nodePointer head = NULL;
	char ch;
	int i; 
	int exist;
	while(1){
		Sans = 0;
		fscanf(fp, "%d", &strNum);	//讀取這題有幾行
		
		if(strNum == 0){	//結束 
			
			break;
		}
		
		fscanf(fp, "%c", &ch);	//讀掉前面的\n
		head = NULL;	//重設head 
		for(i = 0;i < strNum;i++){
			while(1){
				exist = 0;
				fscanf(fp, "%c", &ch);
				if(ch == '\n'){	//換下一行 
					break;
				}
				
				//判別這個字元有沒有存在在queue中
				exist = existfun(head, ch);
				
				if(exist == 0){	//這個字元沒有出現過
					 head = inputQueue(head, ch);
					
				}
			}	
		}
		
		head = combine(head);
		
		sum(head, 0);
		printf("%d\n", Sans);
		
		
		
	}
	 
	
	return 0;
}


int existfun(nodePointer head, char ch){
	int exist = 0;
	if(head == NULL){
		return 0;
	}
	else{
		nodePointer now = head;
		while(now != NULL){
			if(now->character == ch){
				now->times += 1;
				swap(now);	//有加要重新排序 
				exist = 1;
				break;
			}
			now = now->next;
		}
		
		return exist;
	}
}

void swap(nodePointer now){	/*由小排到大*/
	nodePointer tempL = (nodePointer)malloc(sizeof(struct node));
	nodePointer tempR = (nodePointer)malloc(sizeof(struct node));
	int tempT;
	char tempC;
	
	while(now->next != NULL){
		if(now->times > now->next->times){
			/*交換*/
			tempL = now->left;
			tempR = now->right;
			tempT = now->times;
			tempC = now->character;
			
			now->left = now->next->left;
			now->right = now->next->right;
			now->times = now->next->times;
			now->character = now->next->character;
			
			now->next->left = tempL;
			now->next->right = tempR;
			now->next->times = tempT;
			now->next->character = tempC;
			
		}
		else{
			break;
		}
		now = now->next;
	}
	
}

nodePointer inputQueue(nodePointer head, char ch){
	/*新增節點*/
	//每次加入節點都加到第一個 
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->character = ch;
	newNode->times = 1;
	newNode->next = head;
	newNode->left = newNode->right = NULL;
	
	head = newNode;
	
	return head;
}

nodePointer combine(nodePointer head){
	/*合併*/
	//取前兩個合併 再丟去排序 直到只剩一個節點
	
	
	while(head->next != NULL){
		
		nodePointer temp = (nodePointer)malloc(sizeof(struct node));
		temp->left = head;
		temp->right = head->next;
		temp->character = NULL;
		temp->times = head->times + head->next->times;
		temp->next = head->next->next;
		
		head = temp;
		
		swap(head);
		
	}
	
	return head;
	
}

void sum(nodePointer now, int num){
	if(now != NULL){
		if(now->character != NULL){
			Sans = Sans + ((now->times) * num);
		}
		num++;
		sum(now->left, num);
		sum(now->right, num);
	}
	
}


