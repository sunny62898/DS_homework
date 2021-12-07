#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
	int data;
	treePointer left;
	treePointer right;
};

treePointer inittree(treePointer, int);
void preorder(treePointer);

void insert(treePointer, int);
treePointer delFun(treePointer, int);
void query(treePointer, int);
void maxSum(treePointer, int, int);


treePointer findLeftMax(treePointer);
treePointer findRightMax(treePointer);
void search(treePointer, int, int);




int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");  //�}��
	
	int initialNode, comNum;
	
	int i;
	int times = 0;
	
	while(1){
		
		fscanf(fp, "%d", &initialNode);	//Ū��l�𪺸`�I�ƶq 
		fscanf(fp, "%d", &comNum);		//Ū���X��command
		
		if(initialNode == 0 && comNum == 0){	//��ӳ���0 ��ܵ��� 
			break;
		}
		
		/*�g�Joutput*/
		FILE *fout;
		fout = fopen("output_1.txt", "a");  //�}��
		times++;
		fprintf(fout, "# %d\n", times);
		fclose(fout);
		
		
		treePointer head = (treePointer)malloc(sizeof(struct treeNode));	//�إ�head 
		head = NULL;
		
		/*Ū�ɶ}�l*/
		
		//Ū�J�ëإߪ�ltree
		int number; 
		for(i = 0;i < initialNode;i++){
			fscanf(fp, "%d", &number);	//Ūtree data
			
			head = inittree(head, number);
			
		}
		//preorder(head);  //test print initial tree
		
		//Ū�Jcommand�ð���
		char com;
		int number1, number2;
		for(i = 0;i < comNum;i++){
			
			fscanf(fp, "%c", &com);
			
			if(com == '\n'){	//Ū���h�l������ 
				i--;
				continue;
			}
			
			if(com == 'I'){		//�[�J�`�I 
				
				fscanf(fp, "%d", &number1);
				insert(head, number1);
				
				
				
			}
			else if(com == 'D'){	//�R���`�I 
				
				fscanf(fp, "%d", &number1);
				
				head = delFun(head, number1);
				
				
				
			}
			else if(com == 'Q'){	//�d�߸`�I 
				
				fscanf(fp, "%d", &number1);
				query(head, number1);
				
			}
			else if(com == 'P'){	//�̤j�M 
				
				fscanf(fp, "%d", &number1);
				fscanf(fp, "%d", &number2);
				//printf("max\n");
				maxSum(head, number1, number2);
				
			}
			
		} 
		
		
		
	}
	
	fclose(fp);
	
	
	system("pause");
	return 0;
}

treePointer inittree(treePointer head, int number){
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
	//printf("This is I command\n");
	head = inittree(head, number);
	
}

treePointer delFun(treePointer head, int number){	//�R���`�I 

	//printf("This is D command\n");
	
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
					
				}
				else{
					now = NULL;		//�R�ۤv�N�n
					
					return head; 
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
	//printf("This is Q command\n");
	
	int depth = 1;
	
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//�إ�now 
	now = head;
	
	while(now != NULL){
		if(now->data == number){
			/*�g�Joutput*/
			FILE *fout;
			fout = fopen("output_1.txt", "a");  //�}��
			fprintf(fout, "%d\n", depth);
			
			fclose(fout);
			
			break;
		}
		
		else if(number > now->data){
			depth++;
			now = now->right;
		}
		else if(number < now->data){
			depth++;
			now = now->left;
		}
		
	}
	
	
	
}

void maxSum(treePointer head, int number1, int number2){	//�̤j�M 
	//printf("This is P command\n");
	treePointer now = (treePointer)malloc(sizeof(struct treeNode));	//�إ�now 
	now = head;
	
	
	
	//�p�G�P�ɤj�ΦP�ɤp���ܴN�Nnow�@�_���k���Υ���
	//�p�G�@�j�@�p�N�q����now�}�l�� 
	
	if(number1 == number2){
		return number1;
	}
	
	while(1){
		
		if(number1 < now->data && number2 < now->data){
			now = now->left;
		}
		
		else if(number1 > now->data && number2 > now->data){
			now = now->right;
		}
		
		else{
			search(now, number1, number2);
			break;
		}
		
		if(now == NULL){
			break;
		}
		
	}
	
	
	
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


void search(treePointer now, int num1, int num2){
	
	
	treePointer now1 = (treePointer)malloc(sizeof(struct treeNode));
	treePointer now2 = (treePointer)malloc(sizeof(struct treeNode));
	
	int road1 = 0;
	int road2 = 0;
	
	int find1 = 0;
	int find2 = 0;
	
	now1 = now;
	now2 = now;
	
	
	if(now->data > 0){
		road1 = now->data;
	}
	
	
	
	while(now1 != NULL){
		if(num1 > now1->data){
			now1 = now1->right;
		}
		else if(num1 < now1->data){
			now1 = now1->left;
		}
		else{
			find1 = 1;
			break;
		}
		
		if(now1 == NULL){
			break;
		}
		
		if(now1->data > 0){
			road1 = road1 + now1->data;
		}
		
	}

	
	while(now2 != NULL){
		if(num2 > now2->data){
			now2 = now2->right;
		}
		else if(num2 < now2->data){
			now2 = now2->left;
		}
		else{
			find2 = 1;
			break;
		}
		
		if(now2 == NULL){
			break;
		}
		
		if(now2->data > 0){
			road2 = road2 + now2->data;
		}
		
	}
	
	if(find1 == 1 && find2 == 1){
		int sum = road1 + road2;
		
		/*�g�Joutput*/
		FILE *fout;
		fout = fopen("output_1.txt", "a");  //�}��
		fprintf(fout, "%d\n", sum);
			
		fclose(fout);
		
	}
	
	
}


//test print
void preorder(treePointer now){
	if(now != NULL){
		printf("%d\n", now->data);
		preorder(now->left);
		preorder(now->right);
		
	}
	
}
