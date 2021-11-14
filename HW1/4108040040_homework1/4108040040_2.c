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
	
	fscanf(fp, "%d", &number);  //���X�Ӵ��� 
	

	for(i = 0;i < number;i++){
		fscanf(fp, "%d", &arrayN);  //array���j�p 
		fscanf(fp, "%d", &evolution);  //�t�Ʀ���
		
		
		int before[arrayN][arrayN];
		int after[arrayN][arrayN];
		
		/*��J��larray*/
		for(j = 0;j < arrayN;j++){
			for(k = 0;k < arrayN;k++){
				fscanf(fp, "%d", &before[j][k]);
				
			}
		}
		
		
		/*�t�ƶ}�l*/
		int count = 0;
		int live = 0;  //����live���Ӽ� 
		int neighbor = 0;  //�����F�~�s�����Ӽ� 
		int evo;
		for(evo = 0;evo < evolution;evo++){
			live = 0;   //clear live 
			neighbor = 0;  //clear neighbor
			for(j = 0;j < arrayN;j++){
				for(k = 0;k < arrayN;k++){
					
					count = 0;  //clear count
					
					if(j == 0 && k == 0){  //[0,0] 
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j+1][k+1] == 1){  //�k�U 
							count++;
						}
						
						
					}
					else if(j == 0 && k == arrayN-1){  //[0,arrayN-1]
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j+1][k-1] == 1){  //���U 
							count++;
						}
						
					}
					else if(j == arrayN-1 && k == 0){  //[arrayN-1,0]
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j-1][k+1] == 1){  //�k�W 
							count++;
						}
						
					}
					else if(j == arrayN-1 && k == arrayN-1){  //[arrayN-1, arrayN-1]
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j-1][k-1] == 1){  //���W 
							count++;
						}
						
					}
					else if(j == 0){  //[0, ] 
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j+1][k+1] == 1){  //�k�U 
							count++;
						}
						if(before[j+1][k-1] == 1){  //���U 
							count++;
						}
						
					}
					else if(j == arrayN-1){  //[arrayN-1, ]
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j-1][k+1] == 1){  //�k�W 
							count++;
						}
						if(before[j-1][k-1] == 1){  //���W 
							count++;
						}
						
					}
					else if(k == 0){  //[ ,0] 
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j-1][k+1] == 1){  //�k�W 
							count++;
						}
						if(before[j+1][k+1] == 1){  //�k�U 
							count++;
						}
						
						
					}
					else if(k == arrayN-1){  //[ ,arrayN-1]
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j-1][k-1] == 1){  //���W 
							count++;
						}
						if(before[j+1][k-1] == 1){  //���U 
							count++;
						}
						
					}
					
					else{
						if(before[j][k+1] == 1){  //�k 
							count++;
						}
						if(before[j][k-1] == 1){  //�� 
							count++;
						}
						if(before[j-1][k] == 1){  //�W 
							count++;
						}
						if(before[j+1][k] == 1){  //�U 
							count++;
						}
						if(before[j-1][k+1] == 1){  //�k�W 
							count++;
						}
						if(before[j-1][k-1] == 1){  //���W 
							count++;
						}
						if(before[j+1][k+1] == 1){  //�k�U 
							count++;
						}
						if(before[j+1][k-1] == 1){  //���U 
							count++;
						}
						
					}
					
					
					/*�P�_����*/
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
		
		/*�g�J*/
		FILE *foutput;
		foutput = fopen("output_2.txt", "a");
		fprintf(foutput, "%d %d %d\n", arrayN, arrayN, live);
		
		for(j = 0;j < arrayN;j++){
			for(k = 0;k < arrayN;k++){
				
				if(after[j][k] == 1){  //�u�ݦs����
					neighbor = 0;
					
					if(j == 0 && k == 0){  //[0,0] 
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //�k�U 
							neighbor++;
						}
						
						
					}
					else if(j == 0 && k == arrayN-1){  //[0,arrayN-1]
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //���U 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1 && k == 0){  //[arrayN-1,0]
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //�k�W 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1 && k == arrayN-1){  //[arrayN-1, arrayN-1]
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //���W 
							neighbor++;
						}
						
					}
					else if(j == 0){  //[0, ] 
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //�k�U 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //���U 
							neighbor++;
						}
						
					}
					else if(j == arrayN-1){  //[arrayN-1, ]
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //�k�W 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //���W 
							neighbor++;
						}
						
					}
					else if(k == 0){  //[ ,0] 
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //�k�W 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //�k�U 
							neighbor++;
						}
						
						
					}
					else if(k == arrayN-1){  //[ ,arrayN-1]
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //���W 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //���U 
							neighbor++;
						}
						
					}
					
					else{
						if(after[j][k+1] == 1){  //�k 
							neighbor++;
						}
						if(after[j][k-1] == 1){  //�� 
							neighbor++;
						}
						if(after[j-1][k] == 1){  //�W 
							neighbor++;
						}
						if(after[j+1][k] == 1){  //�U 
							neighbor++;
						}
						if(after[j-1][k+1] == 1){  //�k�W 
							neighbor++;
						}
						if(after[j-1][k-1] == 1){  //���W 
							neighbor++;
						}
						if(after[j+1][k+1] == 1){  //�k�U 
							neighbor++;
						}
						if(after[j+1][k-1] == 1){  //���U 
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





