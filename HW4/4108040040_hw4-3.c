#include<stdio.h>
#include<stdlib.h>

typedef struct node* nodePointer;
typedef struct node{
	int number;			//�ҥN���ϰ� 
	nodePointer next;	//���V�U�@�Ӭ۾F���ϰ� 
};

struct headNode{
	int color;			//�ϰ��C�� 
	int size;			//�ϰ�j�p 
	nodePointer beside;	//���V�b�j�����ϰ� 
};

struct colorNode{
	int number;		//�{�b�Ҿ֦����ƶq 
	int cost;		//��O���� 
	int noOther;	//�����w�g�T�w�S��k��J������� 
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
	/*��lstruct*/
	for(i = 0;i < areaNum+1;i++){
		area[i].beside = NULL;
		area[i].color = -1;
		area[i].size = -1;
	}
	
	/*��J�U�ϰ쪺�j�p*/
	for(i = 1;i < areaNum+1;i++){
		fscanf(fp, "%d", &area[i].size);
	}
	
	/*�إ�����a��*/ 
	int side1, side2;
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d %d", &side1, &side2);
		//printf("%d %d\n", side1, side2);
		createMap(areaPointer, side1, side2);
	}
	
	/*test print*/
	//testPrint(areaPointer, areaNum+1);
	
	
	/*�U�C�⪺�ƶq�Φ���*/ 
	struct colorNode color[listNum];
	struct colorNode* colorPointer = &color;
	char ch0, ch1, ch2;	//Ū���h�l��char 
	for(i = 0;i < listNum;i++){
		fscanf(fp, "%c%c%c", &ch0, &ch1, &ch2);
		fscanf(fp, "%d %d", &color[i].number, &color[i].cost);
		color[i].noOther = -1;	//�p�G������񪺷|����'1' 
		//printf("%d %d\n", color[i].number, color[i].cost);
	}
	
	fclose(fp);
	
	/*�}�l���C��*/
	/*
		���C��Q�k
		����̤j���}�l��
		�񧹤�����C�Ʀ��S���ѤU
		���p�����N�䧹���S���涰���ϰ�(�䤧���̤j�B�i�H����)��W�C��
		���p�C��w�g�񧹥B�S���ŦX���C��i�H��(color����noOther�]��1) 
		���N�A��U�@�ӭ��n�̤j���Ӷ�J��L�C�� 
	*/
	/*�إ߳����U�ӭn��array*/ 
	int areaFull[areaNum+1];
	int maxArea;
	int inputColor;
	
	while(1){
		//��̤j���n
		maxArea = findMaxArea(areaPointer, areaNum+1);
		
		if(maxArea == 0){	//�Ҧ��I���Q��L�C��F 
			break;
		}
		
		inputColor = findColor(colorPointer, area[maxArea].size, listNum);
		area[maxArea].color = inputColor;
		color[inputColor].number = color[inputColor].number - area[maxArea].size;
		
		/*���N���۾F����J�Ѿl���ۦP�C��*/
		//���藍�۾F���̤j���B�i��J��
		
		/*�إߤ��۾F�B�S��L��array*/
		for(i = 0;i < areaNum+1;i++){
			areaFull[i] = 1;	//��l�Ȭ�1 �p�G�J�۾F����0(���O���U�ӭn��) 
		}
	
		paintArea(area[maxArea].beside, &areaFull);
		
		paintBeside(area, color, &areaFull, areaNum+1, listNum);
		color[inputColor].noOther = 1;
		
	}
	
	//�p�⵪��
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
			if(color == -1){	//�٨S���ŦX��color 
				color = i;
			}
			else{
				//��cost�p�� 
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
		area[now->number] = 0;	//���۾F��
		now = now->next; 
	}
}

void paintBeside(struct headNode* area, struct colorNode* color, int* noBeside, int Nnum, int Cnum){
	/*�q�̤j���}�l��*/
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

