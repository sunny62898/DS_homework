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
treePointer findRightMax(treePointer);




int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");  //�}��
	
	int initialNode, comNum;
	
	int i;
	
	while(1){
		fscanf(fp, "%d", &initialNode);	//Ū��l�𪺸`�I�ƶq 
		fscanf(fp, "%d", &comNum);		//Ū���X��command
		
		if(initialNode == 0 && comNum == 0){	//��ӳ���0 ��ܵ��� 
			break;
		}
		
		//printf("%d, %d\n", initialNode, comNum); 
		
		treePointer head = (treePointer)malloc(sizeof(struct treeNode));	//�إ�head 
		head = NULL;
		
		/*Ū�ɶ}�l*/
		
		//Ū�J�ëإߪ�ltree
		int number; 
		for(i = 0;i < initialNode;i++){
			fscanf(fp, "%d", &number);	//Ūtree data
			
			head = init(head, number);
			
		}
		//preorder(head);  //test print initial tree
		
		//Ū�Jcommand�ð���
		char com;
		int number1, number2;
		for(i = 0;i < comNum;i++){
			fscanf(fp, "%c", &com);
			
			if(com == 'I'){		//�[�J�`�I 
				
				fscanf(fp, "%d", &number1);
				insert(head, number1);
				
				printf("head = %d\n", head->data);
				
			}
			else if(com == 'D'){	//�R���`�I 
				
				fscanf(fp, "%d", &number1);
				
				head = delFun(head, number1);
				preorder(head);
				
				
			}
			else if(com == 'Q'){	//�d�߸`�I 
				
				fscanf(fp, "%d", &number1);
				query(head, number1);
			}
			else if(com == 'P'){	//�̤j�M 
				
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
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//�إ�now 
	
	treePointer newNode = (treePointer)malloc(sizeof(struct treeNode));	//�إ߷s�`�I
	newNode->data = number;
	newNode->left = NULL;
	newNode->right = NULL;
	
		 
	if(head == NULL){	//�Ĥ@�I��root 
		head = newNode;
		return head;
			
	}
	else{	//��L�`�I
		now = head;
		while(1){
		 	if(newNode->data < now->data){	//�p������ 
		 		if(now->left == NULL){	//�Ū��i�H�� 
		 			now->left = newNode;
					return head;	
				}
				else{
					now = now->left;
				}
			}
			
			else if(newNode->data > now->data){		//�j���k�� 
				if(now->right == NULL){	//�Ū��i�H�� 
					now->right = newNode;
					return head;
				}
				else{
					now = now->right;
				}
			}
			
			else{	//�ۦP���κ� 
				return head;
			}
			
		}
		
	}
	
		 
}


/*command function*/
void insert(treePointer head, int number){	//�[�J�`�I 
	printf("This is I command\n");
	head = init(head, number);
	
}

treePointer delFun(treePointer head, int number){	//�R���`�I 
	printf("This is D command\n");
	printf("head = %d\n", head->data);
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//�إ�now 
	now = head;
	
	while(1){
		
		if(now == NULL){	//�䤣�� 
			break;
		}
		if(now->data == number){
			
			
			if(now->left != NULL){	//��left_max
				treePointer left_max = (treePointer)malloc(sizeof(struct treeNode));	//�إ�left_max
				left_max = findLeftMax(now->left);	//�䥪��̤j���W�@�� 
				
				
				if(left_max->right != NULL){
					
					now->data = left_max->right->data;	//�h����
					left_max->right = left_max->right->left;
						 
					return head;
					
				}
				else{	//�p�G�u�O���ۤv(now->left) 
					now->data = left_max->data;
					now->left = left_max->left;
						
					return head;
					
				} 
				
			}
			else{	//now->left == NULL
				
				if(now->right != NULL){
					
					treePointer right_max = (treePointer)malloc(sizeof(struct treeNode));	//�إ�left_max
					right_max = findRightMax(now->right);	//��k��̤p���W�@�� 
					
					if(right_max->left != NULL){		
						
						now->data = right_max->left->data;	//�h����
						right_max->left = right_max->left->right;
						
						return head;
						
					}
					else{	//�p�G�u�O���ۤv(now->right) 
						now->data = right_max->data;
						now->right = right_max->right;
							
						return head;
						
					} 
					
					return head;
				}
				else{
					now = NULL;		//�R�ۤv�N�n 
				}
			}
			
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

void query(treePointer head, int number){	//�d�߸`�I 
	printf("This is Q command\n");
	
	
	
}

void maxSum(treePointer head, int number1, int number2){	//�̤j�M 
	printf("This is P command\n");
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//�إ�now 
	now = head;
	
}


treePointer findLeftMax(treePointer now){	//�䥪��̤j���W�@�� 
	
	if(now->right != NULL){
		while(now->right->right != NULL){
			now = now->right;
		}
	}
	
	return now;
}
treePointer findRightMax(treePointer now){	//�䥪��̤j���W�@�� 
	
	if(now->left != NULL){
		while(now->left->left != NULL){
			now = now->left;
		}
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
