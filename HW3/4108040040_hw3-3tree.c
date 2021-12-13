#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
	int min;	//顏色塗到 min <= x < max 
	int max;
	char color;
	int lazy;
	treePointer right;
	treePointer left; 
};

treePointer init(int, int);
void paint(treePointer, int, int, char);
void query(treePointer, int, int);

char output[1000];
int top;

int main(){
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");		//開檔 
	
	int wallSize, comNum;
	fscanf(fp, "%d", &wallSize);
	fscanf(fp, "%d", &comNum);
	
	treePointer head = NULL;
	
	
	//建立初始空白牆
	head = init(0, wallSize);
	

	
	int i, j;
	char ch;
	int start, end;
	char color;
	
	/*讀取指令並執行*/
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
			
			paint(head, start, end, color);		//塗色 
			
		}
		
		else if(ch == 'Q'){
			fscanf(fp, "%d", &start);
			fscanf(fp, "%d", &end);
			
			top = 0;
			query(head, start, end);	//查詢顏色 
			
			//寫檔
			FILE *fout;
			fout = fopen("output_3.txt", "a"); 
			
			for(j = 0;j < top;j++){
				if(j > 0){
					if(output[j] != output[j-1]){
						fprintf(fout, "%c ", output[j]);
					}
				}
				else{
					fprintf(fout, "%c ", output[j]);
				}
			}
			fprintf(fout, "\n");
			
			fclose(fout);
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
	node->color = '_';		//全部填入空白 
	node->lazy = 0;
	node->max = max;
	node->min = min;
	
	int mid = min + (max-min) / 2;
	
	if((max-min) > 1){
		node->left = init(min, mid);
		node->right = init(mid, max);
	}
	
	else{
		node->left = node->right = NULL;
	}
	
	return node;
}

void paint(treePointer now, int left, int right, char color){
	
	if(right <= left || now->min > right || now->max < left){
		return;
	}
	
	
	if(now->lazy == 1){
		now->left->color = now->color;
		if((now->left->max-now->left->min) > 1){
			now->left->lazy = 1;
		}
		now->right->color = now->color;
		if((now->right->max-now->right->min) > 1){
			now->right->lazy = 1;
		}
		now->lazy = 0;
	}
	
	if(left <= now->min && right >= now->max){
		now->color = color;
		
		if((now->max-now->min) > 1){
			now->lazy = 1;
		}
		return;
	}
	
	
	if(right < now->left->max){		//只找左邊
		paint(now->left, left, right, color); 
	}
	else if(left >= now->right->min){	//只找右邊 
		paint(now->right, left, right, color);
	}
	else{
		paint(now->left, left, now->left->max, color);
		paint(now->right, now->right->min, right, color);
	}
	
	
	if(now->left->color != now->right->color || now->left->color == '@' || now->right->color == '@'){
		now->color = '@';	//兩邊color不一樣 
	}
	
	
	
}

void query(treePointer now, int left, int right){
	
	
	if(right <= left || now->min >= right || now->max <= left){
		return;
	}

	if(now->lazy == 1){
		now->left->color = now->color;
		if((now->left->max-now->left->min) > 1){
			now->left->lazy = 1;
		}
		now->right->color = now->color;
		if((now->right->max-now->right->min) > 1){
			now->right->lazy = 1;
		}
		now->lazy = 0;
	}
	
	
	if(left <= now->min && right >= now->max){
		if(now->color == '@'){	//左右兩邊不一樣
			//繼續往下查
			query(now->left, left, now->left->max);
			query(now->right, now->right->min, right);
			
		}
		
		else{
			output[top] = now->color;
			top++;
		}
		
		return;
	}
	
	
	if(right < now->left->max){		//只找左邊
		query(now->left, left, right); 
	}
	else if(left > now->right->min){	//只找右邊 
		query(now->right, left, right);
	}
	else{
		query(now->left, left, now->left->max);
		query(now->right, now->min, right);
	}
	
	
}


