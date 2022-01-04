#include<stdio.h>
#include<stdlib.h>

typedef struct node* nodePointer;
typedef struct node{
	int number;			//所代表的區域 
	nodePointer next;	//指向下一個相鄰的區域 
};

struct headNode{
	int color;			//區域顏色 
	int size;			//區域大小 
	nodePointer beside;	//指向在隔壁的區域 
};

struct colorNode{
	int number;		//現在所擁有的數量 
	int cost;		//花費成本 
	int noOther;	//紀錄已經確定沒辦法填入此牆壁的 
};

void createMap(struct headNode*, int, int);
int findMaxArea(struct headNode*, int);
int findColor(struct colorNode*, int, int);
void paintArea(nodePointer, int*);
void paintBeside(struct headNode*, struct colorNode*, int*, int, int);
int chooseBeside(struct headNode*, int*, int);
void testPrint(struct headNode*, int);


int main(){
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");
	
	
	int i;
	int areaNum, relation, listNum;
	fscanf(fp, "%d %d %d", &areaNum, &relation, &listNum);
	//printf("%d %d %d\n", areaNum, relation, listNum);
	
	struct headNode area[areaNum+1];
	struct headNode * areaPointer = &area;
	/*初始struct*/
	for(i = 0;i < areaNum+1;i++){
		area[i].beside = NULL;
		area[i].color = -1;
		area[i].size = -1;
	}
	
	/*填入各區域的大小*/
	for(i = 1;i < areaNum+1;i++){
		fscanf(fp, "%d", &area[i].size);
	}
	
	/*建立牆壁地圖*/ 
	int side1, side2;
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d %d", &side1, &side2);
		//printf("%d %d\n", side1, side2);
		createMap(areaPointer, side1, side2);
	}
	
	/*test print*/
	//testPrint(areaPointer, areaNum+1);
	
	
	/*各顏色的數量及成本*/ 
	struct colorNode color[listNum];
	struct colorNode* colorPointer = &color;
	char ch0, ch1, ch2;	//讀掉多餘的char 
	for(i = 0;i < listNum;i++){
		fscanf(fp, "%c%c%c", &ch0, &ch1, &ch2);
		fscanf(fp, "%d %d", &color[i].number, &color[i].cost);
		color[i].noOther = -1;	//如果為不能填的會換成'1' 
		//printf("%d %d\n", color[i].number, color[i].cost);
	}
	
	fclose(fp);
	
	/*開始填顏色*/
	/*
		填顏色想法
		先找最大的開始填
		填完之後看顏料有沒有剩下
		假如有那就找完全沒有交集的區域(找之中最大且可以夠填的)填上顏色
		假如顏色已經填完且沒有符合的顏色可以填(color中的noOther設為1) 
		那就再找下一個面積最大的來填入其他顏色 
	*/
	/*建立部接下來要填的array*/ 
	int areaFull[areaNum+1];
	int maxArea;
	int inputColor;
	
	while(1){
		//找最大面積
		maxArea = findMaxArea(areaPointer, areaNum+1);
		
		if(maxArea == 0){	//所有點都被填過顏色了 
			break;
		}
		
		inputColor = findColor(colorPointer, area[maxArea].size, listNum);
		area[maxArea].color = inputColor;
		color[inputColor].number = color[inputColor].number - area[maxArea].size;
		
		/*先將不相鄰的填入剩餘的相同顏色*/
		//先選不相鄰中最大的且可填入的
		
		/*建立不相鄰且沒填過的array*/
		for(i = 0;i < areaNum+1;i++){
			areaFull[i] = 1;	//初始值為1 如果遇相鄰的為0(不是接下來要填的) 
		}
	
		paintArea(area[maxArea].beside, &areaFull);
		
		paintBeside(area, color, &areaFull, areaNum+1, listNum);
		color[inputColor].noOther = 1;
		
	}
	
	//計算答案
	int ans = 0; 
	for(i = 1;i < areaNum+1;i++){
		//printf("%d = %d\n", i, area[i].color);
		ans = ans + (area[i].size * color[area[i].color].cost);
	}
	printf("%d\n", ans);
	
	system("pause");
	return 0;
}

void createMap(struct headNode* array, int num1, int num2){
	nodePointer new1 = (nodePointer)malloc(sizeof(struct node));
	nodePointer new2 = (nodePointer)malloc(sizeof(struct node));
	new1->number = num1;
	new2->number = num2;
	new1->next = new2->next = NULL;
	
	if(array[num1].beside == NULL){
		array[num1].beside = new2;
	}
	else{
		nodePointer now1 = array[num1].beside;
		while(now1->next != NULL){
			now1 = now1->next;
		}
		now1->next = new2;
	}
	
	if(array[num2].beside == NULL){
		array[num2].beside = new1;
	}
	else{
		nodePointer now2 = array[num2].beside;
		while(now2->next != NULL){
			now2 = now2->next;
		}
		now2->next = new1;
	}
	
}

int findMaxArea(struct headNode* array, int num){
	int i;
	int max = 0;
	for(i = 1;i < num;i++){
		if(array[max].size < array[i].size && array[i].color == -1){
			
			max = i;
		}
	}
	
	return max;
	
}

int findColor(struct colorNode* array, int areaSize, int num){
	int i;
	int color = -1;
	
	for(i = 0;i < num;i++){
		if(array[i].noOther != 1 && array[i].number >= areaSize){
			if(color == -1){	//還沒有符合的color 
				color = i;
			}
			else{
				//選cost小的 
				if(array[color].cost > array[i].cost){
					color = i;
				}
			}
		}
	}
	return color;
}

void paintArea(nodePointer now, int* area){
	while(now != NULL){
		area[now->number] = 0;	//為相鄰的
		now = now->next; 
	}
}

void paintBeside(struct headNode* area, struct colorNode* color, int* noBeside, int Nnum, int Cnum){
	/*從最大的開始填*/
	int maxArea = 0;
	int inputColor = 0;
	while(1){
		maxArea = chooseBeside(area, noBeside, Nnum);
		if(maxArea == 0){
			break;
		}
		inputColor = findColor(color, area[maxArea].size, Cnum);
		
		noBeside[maxArea] = 0;
		area[maxArea].color = inputColor;
		color[inputColor].number = color[inputColor].number - area[maxArea].size;
		
	}
}

int chooseBeside(struct headNode* area, int* array, int Nnum){
	int i;
	int max = 0;
	for(i = 1;i < Nnum;i++){
		if(array[i] == 1 && area[i].color == -1){
			if(area[i].size > area[max].size){
				max = i;
			}
		}
	}
	return max;
}



void testPrint(struct headNode* array, int num){
	int i;
	nodePointer now = array[0].beside;
	for(i = 1;i < num;i++){
		now = array[i].beside;
		printf("%d = ", i);
		while(now != NULL){
			printf("%d ", now->number);
			now = now->next;
		}
		printf("\n");
	}
}

