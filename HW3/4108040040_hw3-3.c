#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");		//開檔
	
	int wallSize, comNum;
	int i, j;
	
	fscanf(fp, "%d", &wallSize);
	fscanf(fp, "%d", &comNum);
	
	//printf("%d %d\n", wallSize, comNum); 
	
	char wall[wallSize];
	//填入 _ 
	for(i = 0;i < wallSize;i++){
		wall[i] = '_';
	}
	char outputColor[1000];
	int top;
	char com, color;
	int start, end;
	
	for(i = 0;i < comNum;i++){
		fscanf(fp, "%c", &com);
		if(com == '\n' || com == ' '){
			i--;
			continue;
		}
		
		if(com == 'P'){
			fscanf(fp, "%d", &start);
			fscanf(fp, "%d", &end);
			fscanf(fp, "%c", &color);	//多的空格 
			fscanf(fp, "%c", &color);
			
			//printf("%c %d %d %c\n", com, start, end, color);
			
			//paint
			for(j = start-1;j < end;j++){
				wall[j] = color;
			}
			
		}
		else if(com == 'Q'){
			fscanf(fp, "%d", &start);
			fscanf(fp, "%d", &end);
			//printf("%c %d %d\n", com, start, end);
			
			//check
			top = 0;
			for(j = start-1;j < end;j++){
				if(top == 0){
					outputColor[0] = wall[j];
					top++;
				}
				else{
					if(wall[j] != outputColor[top-1]){
						outputColor[top] = wall[j];
						top++;
					}
				}
			}
			
			/*寫入output*/
			FILE *fout;
			fout = fopen("output_3.txt", "a");  //開檔
			
			for(j = 0;j < top;j++){
				fprintf(fout, "%c ", outputColor[j]);
			}
			fprintf(fout, "\n");
			
			fclose(fout);
			
		}
		
	}
	
	
	
	system("pause");
	return 0;
}
