#include<stdio.h>
#include<stdlib.h>
/*
	�W����1-1 �إߤ@��binary tree
	�䤤�\��]�t
		1. I x ���J�`�I
		2. D x �R���`�I
		3. P x y �p��qx��y���`�M (�u���o�ӭnoutput result)	
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
	
	/*�إ߭�l����*/
	for(i = 0;i < nodeNum;i++){
		fscanf(fp, "%d", &number);
		head = insertNode(head, number);
		
	}
	
	
	/*Ū���O����*/
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
		
		else{	//Ū��ũάO����
			i--; 
			
		}
	}
	
	
	return 0;
}

nodePointer insertNode(nodePointer head, int number){
	//�إ߷s�`�I 
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->number = number;
	newNode->left = newNode->right = NULL;
	
	//���J�s�`�I
	if(head == NULL){	//�쥻tree�O�Ū�
		head = newNode;
		return head; 
		
	}
	else{
		//�p���b�� �j���b�k
		nodePointer now = head;
		while(1){
			if(number > now->number){	//���k
				if(now->right == NULL){
					now->right = newNode;
					return head;
				}
				else{
					now = now->right;
				}
				
			}
			else if(number < now->number){	//����
				if(now->left == NULL){
					now->left = newNode;
					return head;
				}
				else{
					now = now->left;
				}
				
			}
			else{	//�ۦP���� 
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
		
		if(number == now->number){	//���n�R���Ʀr 
		
			if(now->left != NULL){	//�䥪��̤j 
				nodePointer find = now->left;
				if(find->right != NULL){
					/*��n�Q�h�����W�@��*/
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
			else if(now->right != NULL){	//��k��̤p 
				nodePointer find = now->right;
				if(find->left != NULL){
					/*��n�Q�h�����W�@��*/
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
				else{	//�R��head 
					free(head);
					head = NULL;
					return head;
				}
			}
			return head;
		}
		else if(number > now->number){	//�j�󩹥k�� 
			parent = now;
			now = now->right;
		}
		else if(number < now->number){	//�p�󩹥��� 
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
	int find2 = 0;	//�O�����S����� 
	
	if(now->number > 0){
		sum1 = now->number;
	}
	
	/*�qnow1�}�l��num1�b����*/
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



