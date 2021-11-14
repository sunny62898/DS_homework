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
	
	fscanf(fp, "%d", &number);  //有幾個測資
	//printf("%d\n", number);
	
	int i,j,k;
	int destinations;		//共經過幾個點 
	int size;
	int front;				//map大小 
	int nowRow, nowCol;
	int nowHeight;
	int nowWeight;
	int goalRow, goalCol;
	int cal;
	int first;  //queue現在pop的位置 
	int rear;
	int sum;
	
	for(i = 0;i < number;i++){
		sum = 0;
		fscanf(fp, "%d", &destinations);
		fscanf(fp, "%d", &size);
		
		struct through point[destinations+1];   //要經過的點(包括start end) 
		struct information map[size][size];
		struct ready queue[size*size];		//準備要被pop的點 
		struct ready *Qptr = &queue;
		
		/*資料讀入*/ 
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
		/*讀入結束*/
		
		 
		front = 0;
		
		while(front < destinations){
			/*起始位置*/ 
			//將起點放到queue 
			queue[0].row = point[front].row;
			queue[0].col = point[front].col;
			
			
			queue[0].weight = 0;  //自己到自己權重 = 0 
			first = 0;  //queue現在pop的位置 
			rear = 1;	//queue下一個要存的位置 
			map[nowRow][nowCol].weight = 0;  //原本地圖的權重 
			
			/*目標位置*/
			goalRow = point[front+1].row;
			goalCol = point[front+1].col;
			
			
			while(queue[first].row != goalRow || queue[first].col != goalCol){
				/*設定現在所在點的初值*/
				nowRow = queue[first].row;
				nowCol = queue[first].col;
				nowWeight = queue[first].weight;
				nowHeight = map[nowRow][nowCol].height;
				
				//設定為已pop過 
				queue[first].pass = 1;
				map[nowRow][nowCol].pass = 1;
				
				int dir;
				int dirX,dirY;
				
				for(dir = 0;dir < 8;dir++){
					
					if(dir == 0){	//右 
						dirX = nowCol+1;
						dirY = nowRow;
					}
					if(dir == 1){	//左 
						dirX = nowCol-1;
						dirY = nowRow;
					}
					if(dir == 2){	//上 
						dirX = nowCol;
						dirY = nowRow-1;
					}
					if(dir == 3){	//下 
						dirX = nowCol;
						dirY = nowRow+1;
					}
					if(dir == 4){	//右上 
						dirX = nowCol+1;
						dirY = nowRow-1;
					}
					if(dir == 5){	//右下 
						dirX = nowCol+1;
						dirY = nowRow+1;
					}
					if(dir == 6){	//左上 
						dirX = nowCol-1;
						dirY = nowRow-1;
					}
					if(dir == 7){	//左下 
						dirX = nowCol-1;
						dirY = nowRow+1;
					}
					
					//超出邊界
					if(dirX < 0 || dirX >= size || dirY < 0 || dirY >= size){
						continue;
					}
					
					else{
						if(map[dirY][dirX].pass != 1){
							//沒pop過 
							cal = nowWeight + abs(nowHeight-map[dirY][dirX].height);
							
							//檢測有沒有被放過queue
							int index = inputQueue(Qptr, rear, dirY, dirX);
							
							if(index == -10){  //沒放過
								//放入queue 
								queue[rear].row = dirY;
								queue[rear].col = dirX;
								queue[rear].weight = cal;
								queue[rear].pass = 0;
								map[dirY][dirX].weight = cal;
								map[dirY][dirX].pass = 0;
								rear++;
							
							}
							else{  //有放過 
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
		/*寫入*/
		FILE *foutput;
		foutput = fopen("output_3.txt", "a");
		fprintf(foutput, "#%d\n",i+1);
		fprintf(foutput, "cost:%d\n", sum);
		fclose(foutput);
		
	} 
	
	fclose(fp);  //關檔 
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


