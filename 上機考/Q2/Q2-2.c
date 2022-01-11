#include<stdio.h>
#include<stdlib.h>

/*
	�W����2-2 ��ܮw�]�m�̨Φa�I
	�Q�k : �Q��order�a�I���_�I�X�o����C���I
		   �ì�����C���I�һݭn��cost
		   �N�C���q�檺cost�ۥ[ �Y�����I���L�Ҧ��q��һݭn����O
		   �̫��X�̤p���æL�X��	 
*/

typedef struct node* nodePointer;
typedef struct node{
	int cost;	//��o�I������
	int number;	//�o�O���@�I
	nodePointer next;	//�s��U�@�� 
};

struct dot{
	int pass;	//�O�����S���Q���L�H�Ψ���o�I�ɥΤF�h��cost 
	nodePointer next; 
};

void createMap(struct dot*, int, int, int);
void calSumCost(struct dot*, int*, int, int);


int main(){
	
	/*Ū��*/
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int nodeNum, orderNum;
	fscanf(fp, "%d %d", &nodeNum, &orderNum);
	
	int i, j;
	struct dot point[nodeNum+1];	//0���ϥ�
	/*��lpoint*/
	for(i = 0;i < nodeNum+1;i++){
		point[i].pass = -1;
		point[i].next = NULL;
	}
	
	int sum[2][nodeNum+1];
	for(i = 0;i < nodeNum+1;i++){
		sum[0][i] = 0;
		sum[1][i] = 0;
	}
	
	int source, dist, pathcost;
	/*�إߦa��*/
	for(i = 0;i < nodeNum-1;i++){
		fscanf(fp, "%d %d %d", &source, &dist, &pathcost);
		createMap(&point, source, dist, pathcost);
		
	}
	
	/*�}�l�p��cost*/
	int begin, number;	//�_�I, �ƶq 
	for(i = 0;i < orderNum;i++){
		fscanf(fp, "%d %d", &begin, &number);
		calSumCost(&point, &sum[1], begin, 0);
		
		for(j = 1;j < nodeNum+1;j++){
			
			sum[0][j] = sum[0][j] + sum[1][j] * number * 2;	//�N���p�⪺�[��sum[0] 
			point[j].pass = -1;	//��lpass 
		}
		
	} 
	
	int minCost;
	int ans[nodeNum];
	int ansTop = 0;
	
	for(i = 1;i < nodeNum+1;i++){
		if(ansTop == 0){
			minCost = sum[0][i];
			ans[ansTop] = i;
			ansTop++;
		}
		else{
			if(minCost > sum[0][i]){
				minCost = sum[0][i];
				ansTop = 0;
				ans[ansTop] = i;
				ansTop++;
			}
			else if(minCost == sum[0][i]){
				ans[ansTop] = i;
				ansTop++;
			}
		}
	}
	
	/*�L�X����*/
	printf("%d\n", minCost);
	for(i = 0;i < ansTop;i++){
		printf("%d ", ans[i]);
	}
	printf("\n");
	
	
	return 0;
}

void createMap(struct dot* array, int num1, int num2, int cost){
	nodePointer new1 = (nodePointer)malloc(sizeof(struct node));
	nodePointer new2 = (nodePointer)malloc(sizeof(struct node));
	
	new1->number = num1;
	new2->number = num2;
	new1->cost = new2->cost = cost;
	new1->next = new2->next = NULL;
	
	nodePointer now = array[0].next;
	/*�s���s�`�I*/
	if(array[num1].next == NULL){
		array[num1].next = new2;
	}
	else{
		now = array[num1].next;
		while(now->next != NULL){
			now = now->next;
		}
		now->next = new2;
	}
	
	if(array[num2].next == NULL){
		array[num2].next = new1;
	}
	else{
		now = array[num2].next;
		while(now->next != NULL){
			now = now->next;
		}
		now->next = new1;
	}
	
}

void calSumCost(struct dot* point, int* sum, int num, int nowSum){
	point[num].pass = nowSum;
	*(sum+num) = nowSum;
	nodePointer now = point[num].next;
	
	while(now != NULL){
		if(point[now->number].pass == -1){	//�S�Q���L 
		
			calSumCost(point, sum, now->number, (nowSum+now->cost));
		}
		now = now->next;
	}
	
	
	
	
}
