#include<stdio.h>
#include<stdlib.h>
/*
	上機考1-1 建立一棵binary tree
	其中功能包含
		1. I x 插入節點
		2. D x 刪除節點
		3. P x y 計算從x到y的總和 (只有這個要output result)	
*/

typedef struct node* nodePointer;
typedef struct node{
	int number;
	nodePointer left;
	nodePointer right;
};

nodePointer insertNode(nodePointer, int);
nodePointer deleteNode(nodePointer, int);
void printSum(nodePointer, int, int);
void search(nodePointer, int, int);
void preorder(nodePointer);

int main(){
	
	/*read file*/
	FILE *fp;
	fp = fopen("input_1.txt", "r");
	
	int nodeNum, comNum;
	fscanf(fp, "%d %d", &nodeNum, &comNum);
	
	int i;
	int number;
	nodePointer head = NULL;
	
	/*建立原始的樹*/
	for(i = 0;i < nodeNum;i++){
		fscanf(fp, "%d", &number);
		head = insertNode(head, number);
		
	}
	
	
	/*讀指令做事*/
	char com;
	int num1, num2;
	for(i = 0;i < comNum;i++){
		fscanf(fp, "%c", &com);
		if(com == 'I'){		//insert
			fscanf(fp, "%d", &num1);
			head = insertNode(head, num1);
			
		}
		else if(com == 'D'){	//delete
			fscanf(fp, "%d", &num1);
			head = deleteNode(head, num1);
		}
		else if(com == 'P'){	//print sum
			fscanf(fp, "%d %d", &num1, &num2);
			printSum(head, num1, num2);
		}
		
		else{	//讀到空或是換行
			i--; 
			
		}
	}
	
	
	return 0;
}

nodePointer insertNode(nodePointer head, int number){
	//建立新節點 
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->number = number;
	newNode->left = newNode->right = NULL;
	
	//插入新節點
	if(head == NULL){	//原本tree是空的
		head = newNode;
		return head; 
		
	}
	else{
		//小的在左 大的在右
		nodePointer now = head;
		while(1){
			if(number > now->number){	//往右
				if(now->right == NULL){
					now->right = newNode;
					return head;
				}
				else{
					now = now->right;
				}
				
			}
			else if(number < now->number){	//往左
				if(now->left == NULL){
					now->left = newNode;
					return head;
				}
				else{
					now = now->left;
				}
				
			}
			else{	//相同忽略 
				return head;
			}
		}
		
		return head;
	}
	
}

nodePointer deleteNode(nodePointer head, int number){
	nodePointer now = head;
	nodePointer parent = NULL;
	while(1){
		if(now == NULL){
			break;
		}
		
		if(number == now->number){	//找到要刪的數字 
		
			if(now->left != NULL){	//找左邊最大 
				nodePointer find = now->left;
				if(find->right != NULL){
					/*找要被搬移的上一個*/
					while(find->right->right != NULL){
						find = find->right;
					}
					now->number = find->right->number;
					find->right = find->right->left;
				}
				else{
					now->number = find->number;
					now->left = find->left;
				}
				
				
			}
			else if(now->right != NULL){	//找右邊最小 
				nodePointer find = now->right;
				if(find->left != NULL){
					/*找要被搬移的上一個*/
					while(find->left->left != NULL){
						find = find->left;
					}
					now->number = find->left->number;
					find->left = find->left->right;
				}
				else{
					now->number = find->number;
					now->right = find->right;
				}
				
			}
			else{
				if(parent != NULL){
					if(parent->left == now){
						parent->left = NULL;
						free(now);
					}
					else{
						parent->right = NULL;
						free(now);
					}
				}
				else{	//刪除head 
					free(head);
					head = NULL;
					return head;
				}
			}
			return head;
		}
		else if(number > now->number){	//大於往右找 
			parent = now;
			now = now->right;
		}
		else if(number < now->number){	//小於往左找 
			parent = now;
			now = now->left;
		}
	}
	
	return head;
	
}

void printSum(nodePointer head, int num1, int num2){
	nodePointer now = head;
	
	while(1){
		if(num1 > now->number && num2 > now->number){
			now = now->right;	
		}
		else if(num1 < now->number && num2 < now->number){
			now = now->left;
		}
		else{
			search(now, num1, num2);
			break;
		}
		
		if(now == NULL){
			break;
		}
		
	}
}

void search(nodePointer now, int num1, int num2){
	nodePointer now1 = (nodePointer)malloc(sizeof(struct node)); 
	nodePointer now2 = (nodePointer)malloc(sizeof(struct node)); 
	
	now1 = now2 = now;
	
	int sum1 = 0;
	int sum2 = 0;
	
	int find1 = 0;
	int find2 = 0;	//記錄有沒有找到 
	
	if(now->number > 0){
		sum1 = now->number;
	}
	
	/*從now1開始找num1在哪裡*/
	while(now1 != NULL){
		if(num1 > now1->number){
			now1 = now1->right;
		}
		else if(num1 < now1->number){
			now1 = now1->left;
		}
		else{
			find1 = 1;
			break;
		}
		
		if(now1 == NULL){
			break;
		}
		
		if(now1->number > 0){
			sum1 += now1->number;
		}
	
		
	}
	
	while(now2 != NULL){
		if(num2 > now2->number){
			now2 = now2->right;
		}
		else if(num2 < now2->number){
			now2 = now2->left;
		}
		else{
			find2 = 1;
			break;
		}
		
		if(now2 == NULL){
			break;
		}
		
		if(now2->number > 0){
			sum2 += now2->number;
		}
	
		
	}
	
	if(find1 == 1 && find2 == 1){
		int sum = sum1 + sum2;
		printf("%d\n", sum);
	}

}



