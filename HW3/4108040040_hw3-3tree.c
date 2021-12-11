#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
	int min;	//�C���� min <= x < max 
	int max;
	char color;
	int lazy;	//�������L�i�k(�n�Ndata push�U�h)
	treePointer right;
	treePointer left; 
};

treePointer init(int, int);
void preorder(treePointer);
void paint(treePointer, int, int, char);
void query(treePointer, int, int);


int main(){
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");		//�}�� 
	
	int wallSize, comNum;
	fscanf(fp, "%d", &wallSize);
	fscanf(fp, "%d", &comNum);
	
	printf("%d %d\n", wallSize, comNum);
	
	treePointer head = NULL;
	
	
	//�إߪ�l�ť���
	head = init(0, wallSize);
	

	
	int i;
	char ch;
	int start, end;
	char color;
	
	/*Ū�����O�ð���*/
	for(i = 0;i < comNum;i++){
		fscanf(fp, "%c", &ch);
		if(ch == '\n' || ch == ' '){
			i--;
			continue;
		}
		
		if(ch == 'P'){	//paint
			fscanf(fp, "%d", &start);
			fscanf(fp, "%d", &end);
			fscanf(fp, "%c", &ch);
			fscanf(fp, "%c", &color);
			printf("%d %d %c\n", start, end, color);
			
			paint(head, start, end, color);		//��� 
			
			preorder(head);
			
		}
		
		else if(ch == 'Q'){
			fscanf(fp, "%d", &start);
			fscanf(fp, "%d", &end);
			
			printf("%d %d\n", start, end);
			
			query(head, start, end);	//�d���C�� 
		}
		
	}
	
	
	
	system("pause");
	return 0;
}


treePointer init(int min, int max){
	
	if(max < min){
		return (NULL);
	}
	
	treePointer node = (treePointer)malloc(sizeof(struct treeNode));
	node->color = '_';		//������J�ť� 
	node->lazy = 0;
	node->max = max;
	node->min = min;
	
	int mid = min + (max-min) / 2;
	
	if((max-min) > 1){
		node->left = init(min, mid);
		node->right = init(mid+1, max);
	}
	
	else{
		node->left = node->right = NULL;
	}
	
	return node;
}

void paint(treePointer now, int left, int right, char color){
	
	if(right <= left || now->min >= right || now->max <= left){
		return;
	}
	
	if(left <= now->min && right >= now->max){
		now->color = color;
		if((now->max-now->min) > 1){
			now->lazy = 1;
		}
		return;
	}
	
	if(now->lazy == 1){		//push down
		now->left->color = now->color;
		now->right->color = now->color;
	}
	
	if(right < now->left->max){		//�u�䥪��
		paint(now->left, left, right, color); 
	}
	else if(left >= now->right->min){	//�u��k�� 
		paint(now->right, left, right, color);
	}
	else{
		paint(now->left, left, now->left->max, color);
		paint(now->right, now->right->min, right, color);
	}
	
	
	if(now->left->color != now->right->color || now->left->color == '@' || now->right->color == '@'){
		now->color = '@';	//����color���@�� 
	}
	
	
	
}

void query(treePointer now, int left, int right){
	printf("query\n");
	
	if(right <= left || now->min >= right || now->max <= left){
		return;
	}
	
	if(left <= now->min && right >= now->max){
		if(now->color == '@'){	//���k���䤣�@��
			//�~�򩹤U�d
			query(now->left, left, now->left->max);
			query(now->right, now->right->min, right);
			
		}
		
		else{
			printf("color = %c\n", now->color);
		}
		
		return;
	}
	
	if(now->lazy == 1){
		now->left->color = now->color;
		now->right->color = now->color;
	}
	
	if(right < now->left->max){		//�u�䥪��
		query(now->left, left, right); 
	}
	else if(left >= now->right->min){	//�u��k�� 
		query(now->right, left, right);
	}
	else{
		query(now->left, left, now->left->max);
		query(now->right, now->min, right);
	}
	
	
}




void preorder(treePointer now){
	if(now == NULL){
		return;
	}
	printf("%d %d %c lazy = %d\n", now->min, now->max, now->color, now->lazy);
	
	preorder(now->left);
	preorder(now->right);
	
}
