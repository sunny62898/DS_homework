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
		int dir,dirX,dirY;
		for(evo = 0;evo < evolution;evo++){
			live = 0;   //clear live 
			neighbor = 0;  //clear neighbor
			for(j = 0;j < arrayN;j++){
				for(k = 0;k < arrayN;k++){
					
					count = 0;  //clear count
					
					
					for(dir = 0;dir < 8;dir++){
					
						if(dir == 0){	//�k 
							dirX = k+1;
							dirY = j;
						}
						if(dir == 1){	//�� 
							dirX = k-1;
							dirY = j;
						}
						if(dir == 2){	//�W 
							dirX = k;
							dirY = j-1;
						}
						if(dir == 3){	//�U 
							dirX = k;
							dirY = j+1;
						}
						if(dir == 4){	//�k�W 
							dirX = k+1;
							dirY = j-1;
						}
						if(dir == 5){	//�k�U 
							dirX = k+1;
							dirY = j+1;
						}
						if(dir == 6){	//���W 
							dirX = k-1;
							dirY = j-1;
						}
						if(dir == 7){	//���U 
							dirX = k-1;
							dirY = j+1;
						}
						
						//�W�X���
						if(dirX < 0 || dirX >= arrayN || dirY < 0 || dirY >= arrayN){
							continue;
						}
						
						else{
							if(before[dirY][dirX] == 1){
								count++;
							}
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
					
					for(dir = 0;dir < 8;dir++){
					
						if(dir == 0){	//�k 
							dirX = k+1;
							dirY = j;
						}
						if(dir == 1){	//�� 
							dirX = k-1;
							dirY = j;
						}
						if(dir == 2){	//�W 
							dirX = k;
							dirY = j-1;
						}
						if(dir == 3){	//�U 
							dirX = k;
							dirY = j+1;
						}
						if(dir == 4){	//�k�W 
							dirX = k+1;
							dirY = j-1;
						}
						if(dir == 5){	//�k�U 
							dirX = k+1;
							dirY = j+1;
						}
						if(dir == 6){	//���W 
							dirX = k-1;
							dirY = j-1;
						}
						if(dir == 7){	//���U 
							dirX = k-1;
							dirY = j+1;
						}
						
						//�W�X���
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





