#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listNode *listPointer;   //���V�U�@��struct 
typedef struct listNode {
	int data;
	listPointer link;
};


void show(listPointer);		//print list 
void init(listPointer , char *);		//��l��list 
int command(char *);	//�P�_�O����command

void add(listPointer, int);
listPointer del(listPointer, int);
void ins(listPointer, int, int);
void mul(listPointer, int, int);
void rev(listPointer, int);
 

int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");  //�}��
	
	int i;
	char str[1000];
	
	
	listPointer head = (listPointer)malloc(sizeof(struct listNode));	//�Nhead���VNULL 
	head->link = NULL;
	head->data = -1;
	
	
	/*Ū�ɶ}�l*/
	char ch;
	fscanf(fp, "%[^\n]", str);	//Ū���Ĥ@�� initial list 
	str[strlen(str)] = '\n';	//�[�@��\n�i�h 
	
	fscanf(fp, "%c", &ch);	//Ū���h��\n 
	init(head, str);	//�]�w��llist
	
	
	int comNumber;		//command�Ӽ� 
	fscanf(fp, "%d", &comNumber);
	//printf("com = %d\n", comNumber);
	
	char com[4];	//���O�̪��O4 
	
	/*�}�l�����O*/
	int serial = 0;
	int num1, num2;
	for(i = 0;i < comNumber;i++){
		fscanf(fp,"%s", com);
		serial = command(com);
		//printf("com = %d\n", serial);
		
		/*�P�O�nŪ�X�ӼƦr*/
		if(serial == 1){		//add
			fscanf(fp, "%d", &num1);
			add(head, num1);
		}
		
		else if(serial == 2){	//del
			fscanf(fp, "%d", &num1);
			head = del(head, num1);
		}
		
		else if(serial == 3){	//ins
			fscanf(fp, "%d", &num1);
			fscanf(fp, "%d", &num2);
			ins(head, num1, num2);
		}
		
		else if(serial == 4){	//mul
			fscanf(fp, "%d", &num1);
			fscanf(fp, "%d", &num2);
			mul(head, num1, num2);
			
		}
		
		else if(serial == 5){	//rev
			fscanf(fp, "%d", &num1);
			rev(head, num1);
		}
		
		else if(serial == 6){	//show
			show(head);
		}
		
		
	}
	
	
	
	fclose(fp);  //���� 
	
	system("pause");
	return 0;
}

void show(listPointer head){
	FILE *foutput;
	foutput = fopen("output_1.txt", "a");  //�}��
	
	listPointer now = head->link;
	
	while(now->link != NULL){
		fprintf(foutput, "%d ", now->data);
		//printf("%d ", now->data);
		now = now->link;
	}
	fprintf(foutput, "%d ", now->data);
	//printf("%d\n", now->data);
	
	fprintf(foutput, "\n");
	fclose(foutput);
}

void init(listPointer head, char *str){
	int i;
	int number = 0;
	listPointer now = head;
	
	for(i = 0;i < strlen(str);i++){
		if(str[i] != ' ' && str[i] != '\n'){
			number = number*10 + (str[i] - '0');
		}
		
		else if(str[i] == ' ' || str[i] == '\n'){
			listPointer node = (listPointer)malloc(sizeof(struct listNode));
			node->data = number;
			node->link = NULL;
			now->link = node;
			now = now->link;		//�s��U�@��		
			number = 0;    //�Nnumber�k0 
		}
	} 
}


int command(char * com){
	//printf("%s\n", com);
	
	if(strcmp(com, "add") == 0){
		
		return 1;
		
	}
	else if(strcmp(com,"del") == 0){
		
		return 2;
	}
	
	else if(strcmp(com,"ins") == 0){
		
		return 3;
	}
	
	else if(strcmp(com,"mul") == 0){
		
		return 4;
	}
	
	else if(strcmp(com,"rev") == 0){
		
		return 5;
	}
	
	else if(strcmp(com,"show") == 0){
		
		return 6;
	}
	
	return 0;
	
}

void add(listPointer head, int num){
	listPointer now = head->link;
	
	while(now->link != NULL){	//��̫�@�� 
		now = now->link;
	}
	
	listPointer node = (listPointer)malloc(sizeof(struct listNode));
	node->data = num;
	node->link = NULL;
	now->link = node;
	
}

listPointer del(listPointer head, int num){
	
	if(num == 1){		//�p�G�ؼЬO�Ĥ@��
		head = head->link;
		return head;
	}
	
	else{		//�p�G�O�ĤG�Ӥ��� 
		int check = 0;
		int count = 1;
		listPointer now = head->link;
		
		while(now->link != NULL){	//��n�R��
			if(count == num-1){	//���ؼЪ��e�@�� 
				check = 1;
				break;
			}
			now = now->link;	//�s��U�@�� 
			count++; 
		}
		
		if(check == 1){
			now->link = now->link->link;
		}
		
		
		return head;
	}
	
	
}

void ins(listPointer head, int num1, int num2){
	int count = 1;
	listPointer now = head->link;
		
	while(now->link != NULL){	//��n�[�b�� 
		if(count == num1){	//���ؼ� 
			break;
		}
		now = now->link;	//�s��U�@�� 
		count++; 
	}
	
	/*add to linked list*/
	if(now->link == NULL){	//�p�G�ؼЬO�̫�@�� 
		/*�إ߷s�`�I*/
		listPointer node = (listPointer)malloc(sizeof(struct listNode));
		node->data = num2;
		node->link = NULL;
		
		/*�[��linked list*/ 
		now->link = node;
	}
	
	else{
		/*�إ߷s�`�I*/
		listPointer node = (listPointer)malloc(sizeof(struct listNode));
		node->data = num2;
		
		/*�[��linked list*/
		node->link = now->link;
		now->link = node;
	}
		
}

int cmul = 0;
void mul(listPointer head, int num1, int num2){
	listPointer now = head;
	if(now->link == NULL){
		cmul = 1;
		if(cmul == num1){	//�p�G�n�����O�˼ƲĤ@�� 
			now->data = now->data * num2;
				
		}
		return;
	}
	else{
		mul(now->link, num1, num2);
	}
	
	cmul++;
	if(cmul == num1){
		now->data = now->data * num2;	
	}
	
}

void rev(listPointer head, int num){
	listPointer nhead = head->link;
	listPointer now = head->link;
	int count = 0;
	int array[num];
	
	while(now->link != NULL){
		array[count] = now->data;
		count++;
		if(count < num){
			now = now->link;	
		}
		else{
			break;
		}
	}
	if(now->link == NULL){	//�̫�@�Ӹ`�I 
		array[count] = now->data;
		count++;
	}
	
	int i;
	for(i = count-1;i >= 0;i--){
		nhead->data = array[i];
		nhead = nhead->link;
	}
	
	if(now->link != NULL){
		rev(now, num);
	}
	
}


