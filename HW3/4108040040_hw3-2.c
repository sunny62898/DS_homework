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
	
	int col;	//���
	char array[1000000];
	char ch;
	nodePointer queue[1000];
	int i;
	int exist;
	nodePointer head;
	
	while(1){
		
		fscanf(fp, "%d", &col);
		printf("%d\n", col);
		fscanf(fp, "%c", &ch);	//Ū���h��\n 
		
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
				
				if(head == NULL){	//�Ĥ@�Ӫ����� 
					head = inputQueue(head, ch);
				}
				else{
					exist = searchExist(head, ch);	//�s�b1 ���s�b0
					if(exist == 0){		//���s�b 
						//�p�G�S�X�{�L�o�Ӧr����Jqueue��
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
	//�s�W�s���`�I
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
			now = now->next;		//��̫�@�I 
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



