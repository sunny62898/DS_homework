#include<stdio.h>
#include<stdlib.h>

struct through{
	int row;
	int col;
};

struct information{
	int height;
	int weight;
	int pass;
};

struct ready{
	int row;
	int col;
	int weight;
	int pass;
};

int inputQueue(struct ready*  , int , int , int );
int popQueue(struct ready*  , int );
void push(struct ready* , int , int);

int main(){
	
	int number;
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");
	
	if(fp == NULL){
		printf("Error ! opening file");
		exit(1); 
	}
	
	fscanf(fp, "%d", &number);  //���X�Ӵ���
	//printf("%d\n", number);
	
	int i,j,k;
	int destinations;		//�@�g�L�X���I 
	int size;
	int front;				//map�j�p 
	int nowRow, nowCol;
	int nowHeight;
	int nowWeight;
	int goalRow, goalCol;
	int cal;
	int first;  //queue�{�bpop����m 
	int rear;
	int sum;
	
	for(i = 0;i < number;i++){
		sum = 0;
		fscanf(fp, "%d", &destinations);
		fscanf(fp, "%d", &size);
		
		struct through point[destinations+1];   //�n�g�L���I(�]�Astart end) 
		struct information map[size][size];
		struct ready queue[size*size];		//�ǳƭn�Qpop���I 
		struct ready *Qptr = &queue;
		
		/*���Ū�J*/ 
		for(j = 0;j < destinations+1;j++){
			fscanf(fp, "%d", &point[j].row);
			fscanf(fp, "%d", &point[j].col);
		}
		
		for(j = 0; j < size;j++){
			for(k = 0;k < size;k++){
				fscanf(fp, "%d", &map[j][k].height);
				map[j][k].pass = 0;
				map[j][k].weight = 100000;
			}
		}
		/*Ū�J����*/
		
		 
		front = 0;
		
		while(front < destinations){
			/*�_�l��m*/ 
			//�N�_�I���queue 
			queue[0].row = point[front].row;
			queue[0].col = point[front].col;
			
			
			queue[0].weight = 0;  //�ۤv��ۤv�v�� = 0 
			first = 0;  //queue�{�bpop����m 
			rear = 1;	//queue�U�@�ӭn�s����m 
			map[nowRow][nowCol].weight = 0;  //�쥻�a�Ϫ��v�� 
			
			/*�ؼЦ�m*/
			goalRow = point[front+1].row;
			goalCol = point[front+1].col;
			
			
			while(queue[first].row != goalRow || queue[first].col != goalCol){
				/*�]�w�{�b�Ҧb�I�����*/
				nowRow = queue[first].row;
				nowCol = queue[first].col;
				nowWeight = queue[first].weight;
				nowHeight = map[nowRow][nowCol].height;
				
				//�]�w���wpop�L 
				queue[first].pass = 1;
				map[nowRow][nowCol].pass = 1;
				
				int dir;
				int dirX,dirY;
				
				for(dir = 0;dir < 8;dir++){
					
					if(dir == 0){	//�k 
						dirX = nowCol+1;
						dirY = nowRow;
					}
					if(dir == 1){	//�� 
						dirX = nowCol-1;
						dirY = nowRow;
					}
					if(dir == 2){	//�W 
						dirX = nowCol;
						dirY = nowRow-1;
					}
					if(dir == 3){	//�U 
						dirX = nowCol;
						dirY = nowRow+1;
					}
					if(dir == 4){	//�k�W 
						dirX = nowCol+1;
						dirY = nowRow-1;
					}
					if(dir == 5){	//�k�U 
						dirX = nowCol+1;
						dirY = nowRow+1;
					}
					if(dir == 6){	//���W 
						dirX = nowCol-1;
						dirY = nowRow-1;
					}
					if(dir == 7){	//���U 
						dirX = nowCol-1;
						dirY = nowRow+1;
					}
					
					//�W�X���
					if(dirX < 0 || dirX >= size || dirY < 0 || dirY >= size){
						continue;
					}
					
					else{
						if(map[dirY][dirX].pass != 1){
							//�Spop�L 
							cal = nowWeight + abs(nowHeight-map[dirY][dirX].height);
							
							//�˴����S���Q��Lqueue
							int index = inputQueue(Qptr, rear, dirY, dirX);
							
							if(index == -10){  //�S��L
								//��Jqueue 
								queue[rear].row = dirY;
								queue[rear].col = dirX;
								queue[rear].weight = cal;
								queue[rear].pass = 0;
								map[dirY][dirX].weight = cal;
								map[dirY][dirX].pass = 0;
								rear++;
							
							}
							else{  //����L 
								if(cal < queue[index].weight){
									queue[index].weight = cal;
								}
							}
						}
						
						push(Qptr, rear, first);
					}
				}
				
				first++;
			}
			sum = sum + queue[first].weight;
			front++;
		}
		//printf("cost = %d\n", sum);
		/*�g�J*/
		FILE *foutput;
		foutput = fopen("output_3.txt", "a");
		fprintf(foutput, "#%d\n",i+1);
		fprintf(foutput, "cost:%d\n", sum);
		fclose(foutput);
		
	} 
	
	fclose(fp);  //���� 
	system("pause");
	return 0;
}


int inputQueue(struct ready* ptr, int rear, int row, int col){
	int i;
	int find = 0;
	struct ready *temp;
	for(i = 0;i < rear;i++){
		temp = ptr+i;
		if(temp->row == row && temp->col == col){
			
			find = 1;
			break;
		}
	}
	
	if(find == 1){
		return i;
	}
	else{
		return -10;
	}
}



void push(struct ready* ptr, int rear, int front){
	struct ready* temp;
	struct ready* temp1;
	struct ready* temp2;
	int i;
	for(i = rear-1;i > front;i--){
		temp1 = ptr+i;
		temp2 = ptr+i-1;
		
		if(temp1->weight < temp2->weight){
			temp = temp1;
			temp1 = temp2;
			temp2 = temp;
		}
		
	}
	
	
}


