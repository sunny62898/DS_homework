#include<stdio.h>
#include<stdlib.h>

/*
	�W����3-1 Huffman code
	�Q�k : ��Ū�J�o�D���X��r��(�p�GŪ��0�Nbreak)
		   �A�̷өҳW�w����ƥhŪ���r��
		   �إ�struct�h�s��left, right, next, char, times(�����bstruct����)
		   �NŪ�쪺�r����Jqueue��(�䤤�r��������)
		   �p�G��쭫�ƪ����N�L��times+1�A�A��L��h�Ƨ� 
		   ���U�Ӷ}�l�X�ָ`�I
		   �]���b�إ�queue�ɤw�g���ƧǹL�A�ҥH�N�������e����Ӷi��X�� 
		   �X�֧�����@�˥�h�Ƨ�
		   (�@���`���o�˪��B�J�A����u�ѤU�@�Ӹ`�I)
		   �h�p���`�@�Ҫ�F�h��byte(�λ��j) 
*/

typedef struct node* nodePointer;
typedef struct node{
	int times;	//�֥[�O������
	char character;	//�O���o�O���Ӧr��(�p�G�O����X�֩Ҳ��ͪ�node�A���N�|�ONULL)
	nodePointer next;	//queue���U�@��
	nodePointer left;	//�ΨӦX�֩Ҳ��ͪ�tree left
	nodePointer right;	//�ΨӦX�֩Ҳ��ͪ�tree right 
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
		fscanf(fp, "%d", &strNum);	//Ū���o�D���X��
		
		if(strNum == 0){	//���� 
			
			break;
		}
		
		fscanf(fp, "%c", &ch);	//Ū���e����\n
		head = NULL;	//���]head 
		for(i = 0;i < strNum;i++){
			while(1){
				exist = 0;
				fscanf(fp, "%c", &ch);
				if(ch == '\n'){	//���U�@�� 
					break;
				}
				
				//�P�O�o�Ӧr�����S���s�b�bqueue��
				exist = existfun(head, ch);
				
				if(exist == 0){	//�o�Ӧr���S���X�{�L
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
				swap(now);	//���[�n���s�Ƨ� 
				exist = 1;
				break;
			}
			now = now->next;
		}
		
		return exist;
	}
}

void swap(nodePointer now){	/*�Ѥp�ƨ�j*/
	nodePointer tempL = (nodePointer)malloc(sizeof(struct node));
	nodePointer tempR = (nodePointer)malloc(sizeof(struct node));
	int tempT;
	char tempC;
	
	while(now->next != NULL){
		if(now->times > now->next->times){
			/*�洫*/
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
	/*�s�W�`�I*/
	//�C���[�J�`�I���[��Ĥ@�� 
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->character = ch;
	newNode->times = 1;
	newNode->next = head;
	newNode->left = newNode->right = NULL;
	
	head = newNode;
	
	return head;
}

nodePointer combine(nodePointer head){
	/*�X��*/
	//���e��ӦX�� �A��h�Ƨ� ����u�Ѥ@�Ӹ`�I
	
	
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


