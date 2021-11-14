#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	
	int number;
	int arrayN;
	int evolution;

	int i,j,k;
	
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	if(fp == NULL){
		printf("Error ! opening file");
		exit(1); 
	}
	
	fscanf(fp, "%d", &number);  //有幾個測資 
	

	for(i = 0;i < number;i++){
		fscanf(fp, "%d", &arrayN);  //array的大小 
		fscanf(fp, "%d", &evolution);  //演化次數
		
		
		int before[arrayN][arrayN];
		int after[arrayN][arrayN];
		
		/*填入初始array*/
		for(j = 0;j < arrayN;j++){
			for(k = 0;k < arrayN;k++){
				fscanf(fp, "%d", &before[j][k]);
				
			}
		}
		
		
		/*演化開始*/
		int count = 0;
		int live = 0;  //紀錄live的個數 
		int neighbor = 0;  //紀錄鄰居存活的個數 
		int evo;
		int dir,dirX,dirY;
		for(evo = 0;evo < evolution;evo++){
			live = 0;   //clear live 
			neighbor = 0;  //clear neighbor
			for(j = 0;j < arrayN;j++){
				for(k = 0;k < arrayN;k++){
					
					count = 0;  //clear count
					
					
					for(dir = 0;dir < 8;dir++){
					
						if(dir == 0){	//右 
							dirX = k+1;
							dirY = j;
						}
						if(dir == 1){	//左 
							dirX = k-1;
							dirY = j;
						}
						if(dir == 2){	//上 
							dirX = k;
							dirY = j-1;
						}
						if(dir == 3){	//下 
							dirX = k;
							dirY = j+1;
						}
						if(dir == 4){	//右上 
							dirX = k+1;
							dirY = j-1;
						}
						if(dir == 5){	//右下 
							dirX = k+1;
							dirY = j+1;
						}
						if(dir == 6){	//左上 
							dirX = k-1;
							dirY = j-1;
						}
						if(dir == 7){	//左下 
							dirX = k-1;
							dirY = j+1;
						}
						
						//超出邊界
						if(dirX < 0 || dirX >= arrayN || dirY < 0 || dirY >= arrayN){
							continue;
						}
						
						else{
							if(before[dirY][dirX] == 1){
								count++;
							}
						}
					}
					
					/*判斷死活*/
					if(before[j][k] == 1){  //live
						if(count <= 1){
							after[j][k] = 0;  //live -> dead
						}
						else if(count >= 2 && count <= 3){
							after[j][k] = 1;  //live -> live
							live++;
						}
						else{
							after[j][k] = 0;  //live -> dead
						}
					}
					else{  //dead
						if(count == 3){
							after[j][k] = 1;  //dead -> live
							live++;
						}
						else{
							after[j][k] = 0;  //dead -> dead
						}
					}
					
				}
			}
		
			
			if(evo != evolution-1){
				//after -> before
				for(j = 0;j < arrayN;j++){
					for(k = 0;k < arrayN;k++){
						before[j][k] = after[j][k];	
					}
				}
			}
			
		}
		
		/*寫入*/
		FILE *foutput;
		foutput = fopen("output_2.txt", "a");
		fprintf(foutput, "%d %d %d\n", arrayN, arrayN, live);
		
		for(j = 0;j < arrayN;j++){
			for(k = 0;k < arrayN;k++){
				
				if(after[j][k] == 1){  //只看存活的
					neighbor = 0;
					
					for(dir = 0;dir < 8;dir++){
					
						if(dir == 0){	//右 
							dirX = k+1;
							dirY = j;
						}
						if(dir == 1){	//左 
							dirX = k-1;
							dirY = j;
						}
						if(dir == 2){	//上 
							dirX = k;
							dirY = j-1;
						}
						if(dir == 3){	//下 
							dirX = k;
							dirY = j+1;
						}
						if(dir == 4){	//右上 
							dirX = k+1;
							dirY = j-1;
						}
						if(dir == 5){	//右下 
							dirX = k+1;
							dirY = j+1;
						}
						if(dir == 6){	//左上 
							dirX = k-1;
							dirY = j-1;
						}
						if(dir == 7){	//左下 
							dirX = k-1;
							dirY = j+1;
						}
						
						//超出邊界
						if(dirX < 0 || dirX >= arrayN || dirY < 0 || dirY >= arrayN){
							continue;
						}
						
						else{
							if(after[dirY][dirX] == 1){
								neighbor++;
							}
						}
					}
					
					fprintf(foutput, "%d %d %d\n", j, k, neighbor);
					
				}
				
			}
			
		}
		fclose(foutput);
		
	}
	
	fclose(fp);
	
	system("pause");
	return 0;
}





