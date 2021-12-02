#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
	int data;
	treePointer left;
	treePointer right;
};

treePointer init(treePointer, int);
void preorder(treePointer);

void insert(treePointer, int);
treePointer delFun(treePointer, int);
void query(treePointer, int);
void maxSum(treePointer, int, int);


treePointer findLeftMax(treePointer);




int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");  //開檔
	
	int initialNode, comNum;
	
	int i;
	
	while(1){
		fscanf(fp, "%d", &initialNode);	//讀初始樹的節點數量 
		fscanf(fp, "%d", &comNum);		//讀有幾個command
		
		if(initialNode == 0 && comNum == 0){	//兩個都為0 表示結束 
			break;
		}
		
		//printf("%d, %d\n", initialNode, comNum); 
		
		treePointer head = (treePointer)malloc(sizeof(struct treeNode));	//建立head 
		head = NULL;
		
		/*讀檔開始*/
		
		//讀入並建立初始tree
		int number; 
		for(i = 0;i < initialNode;i++){
			fscanf(fp, "%d", &number);	//讀tree data
			
			head = init(head, number);
			
		}
		preorder(head);  //test print initial tree
		
		//讀入command並執行
		char com;
		int number1, number2;
		for(i = 0;i < comNum;i++){
			fscanf(fp, "%c", &com);
			
			if(com == 'I'){		//加入節點 
				
				fscanf(fp, "%d", &number1);
				insert(head, number1);

			}
			else if(com == 'D'){	//刪除節點 
				
				fscanf(fp, "%d", &number1);
				delFun(head, number1);
			}
			else if(com == 'Q'){	//查詢節點 
				
				fscanf(fp, "%d", &number1);
				query(head, number1);
			}
			else if(com == 'P'){	//最大和 
				
				fscanf(fp, "%d", &number1);
				fscanf(fp, "%d", &number2);
				maxSum(head, number1, number2);
			}
			
		} 
		
		 
		
		
	}
	
	
	
	
	system("pause");
	return 0;
}

treePointer init(treePointer head, int number){
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//建立now 
	
	treePointer newNode = (treePointer)malloc(sizeof(struct treeNode));	//建立新節點
	newNode->data = number;
	newNode->left = NULL;
	newNode->right = NULL;
		 
	if(head == NULL){	//第一點為root 
		head = newNode;
		return head;
			
	}
	else{	//其他節點
		now = head;
		while(1){
		 	if(newNode->data < now->data){	//小的左邊 
		 		if(now->left == NULL){	//空的可以放 
		 			now->left = newNode;
					return head;	
				}
				else{
					now = now->left;
				}
			}
			
			else if(newNode->data > now->data){		//大的右邊 
				if(now->right == NULL){	//空的可以放 
					now->right = newNode;
					return head;
				}
				else{
					now = now->right;
				}
			}
			
			else{	//相同不用管 
				return head;
			}
			
		}
		
	}
	
		 
}


/*command function*/
void insert(treePointer head, int number){	//加入節點 
	printf("This is I command\n");
	init(head, number);
	preorder(head);
}

treePointer delFun(treePointer head, int number){	//刪除節點 
	printf("This is D command\n");
	
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//建立now 
	now = head;
	
	while(1){
		
		if(now == NULL){	//找不到 
			break;
		}
		
		if(now == head && now->data == number){		//刪除的是head 
		
			if(now->left != NULL){
				treePointer left_max = (treePointer)malloc(sizeof(struct treeNode));	//建立left_max
				left_max = findLeftMax(now->left);	//找左邊最大的上一個 
				if(left_max->right != NULL){		//那個節點是leaf
					if(left_max->right->left != NULL){
						treePointer temp = (treePointer)malloc(sizeof(struct treeNode));
						temp = left_max->right;
						temp->left = head->left;
						temp->right = head->right;
						left_max->right = left_max->right->left;
						head = temp;
						
						return head;
					}
					else{
						left_max->right->left = head->left;
						left_max->right->right = head->right;
						head = left_max->right;
						return head;
					} 
					
				}
				else{
					if(left_max->left != NULL){
						//這邊沒有想完善 
						treePointer temp = (treePointer)malloc(sizeof(struct treeNode));
						temp = left_max;
						temp->left = head->left;
						temp->right = head->right;
						left_max->right = left_max->right->left;
						head = temp;
						
						return head;
					}
					
				} 
			}
			else{	//只有right
				head = now->right;
				return head;
				
			}
			
			
			
		}
		else if(now->data == number){		//刪除中間節點 
			
		}
		
		else if(number > now->data){
			now = now->right;
		}
		
		else if(number < now->data){
			now = now->left;
		}
		
		
	}
	
	
	return head;
	
	
} 

void query(treePointer head, int number){	//查詢節點 
	printf("This is Q command\n");
	
	
	
}

void maxSum(treePointer head, int number1, int number2){	//最大和 
	printf("This is P command\n");
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//建立now 
	now = head;
	
}


treePointer findLeftMax(treePointer now){	//找左邊最大的上一個 
	while(now->right->right != NULL){
		now = now->right;
	}
	
	return now;
}



//test print
void preorder(treePointer now){
	if(now != NULL){
		printf("%d\n", now->data);
		preorder(now->left);
		preorder(now->right);
		
	}
}
