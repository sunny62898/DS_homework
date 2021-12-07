#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
	char word;
	int times;
	nodePointer pointer;
};

int main(){
	
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int col;	//行數
	char array[1000000];
	char ch;
	nodePointer queue[1000];
	int i;
	
	while(1){
		
		fscanf(fp, "%d", &col);
		printf("%d\n", col);
		fscanf(fp, "%c", &ch);	//讀掉多的\n 
		
		if(col == 0){
			break;
		}
		
		for(i = 0;i < col;i++){
			while(1){
				fscanf(fp, "%c", &ch);
				printf("%c", ch);
				if(ch == '\n'){
					break;
				}
				
			}
		
		}
		
		
		
		
		
	} 
	
	
	
	fclose(fp);
	
	system("pause");
	return 0;
}
