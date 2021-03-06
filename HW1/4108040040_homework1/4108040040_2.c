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
		for(evo = 0;evo < evolution;evo++){
			live = 0;   //clear live 
			neighbor = 0;  //clear neighbor
			for(j = 0;j < arrayN;j++){
				for(k = 0;k < arrayN;k++){
					
					count = 0;  //clear count
					
					if(j == 0 && k == 0){  //[0,0] 
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j+1][k+1] == 1){  //右下 
							count++;
						}
						
						
					}
					else if(j == 0 && k == arrayN-1){  //[0,arrayN-1]
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j+1][k-1] == 1){  //左下 
							count++;
						}
						
					}
					else if(j == arrayN-1 && k == 0){  //[arrayN-1,0]
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j-1][k+1] == 1){  //右上 
							count++;
						}
						
					}
					else if(j == arrayN-1 && k == arrayN-1){  //[arrayN-1, arrayN-1]
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j-1][k-1] == 1){  //左上 
							count++;
						}
						
					}
					else if(j == 0){  //[0, ] 
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j+1][k+1] == 1){  //右下 
							count++;
						}
						if(before[j+1][k-1] == 1){  //左下 
							count++;
						}
						
					}
					else if(j == arrayN-1){  //[arrayN-1, ]
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j-1][k+1] == 1){  //右上 
							count++;
						}
						if(before[j-1][k-1] == 1){  //左上 
							count++;
						}
						
					}
					else if(k == 0){  //[ ,0] 
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j-1][k+1] == 1){  //右上 
							count++;
						}
						if(before[j+1][k+1] == 1){  //右下 
							count++;
						}
						
						
					}
					else if(k == arrayN-1){  //[ ,arrayN-1]
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j-1][k-1] == 1){  //左上 
							count++;
						}
						if(before[j+1][k-1] == 1){  //左下 
							count++;
						}
						
					}
					
					else{
						if(before[j][k+1] == 1){  //右 
							count++;
						}
						if(before[j][k-1] == 1){  //左 
							count++;
						}
						if(before[j-1][k] == 1){  //上 
							count++;
						}
						if(before[j+1][k] == 1){  //下 
							count++;
						}
						if(before[j-1][k+1] == 1){  //右上 
							count++;
						}
						if(before[j-1][k-1] == 1){  //左上 
							count++;
						}
						if(before[j+1][k+1] == 1){  //右下 
							count++;
						}
						if(before[j+1][k-1] == 1){  //左下 
							count++;
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
					
					if(j == 0 && k == 0){  //[0,0] 
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //右下 
							neighbor++;
						}
						
						
					}
					else if(j == 0 && k == arrayN-1){  //[0,arrayN-1]
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //左下 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1 && k == 0){  //[arrayN-1,0]
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //右上 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1 && k == arrayN-1){  //[arrayN-1, arrayN-1]
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //左上 
							neighbor++;
						}
						
					}
					else if(j == 0){  //[0, ] 
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //右下 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //左下 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1){  //[arrayN-1, ]
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //右上 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //左上 
							neighbor++;
						}
						
					}
					else if(k == 0){  //[ ,0] 
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //右上 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //右下 
							neighbor++;
						}
						
						
					}
					else if(k == arrayN-1){  //[ ,arrayN-1]
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //左上 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //左下 
							neighbor++;
						}
						
					}
					
					else{
						if(after[j][k+1] == 1){  //右 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //左 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //上 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //下 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //右上 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //左上 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //右下 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //左下 
							neighbor++;
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





