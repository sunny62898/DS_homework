#include<stdio.h>
#include<stdlib.h>


int main(){
	
	FILE *fp;
	fp = fopen("input_3.txt", "r");
	
	int areaNum, relation, listNum;
	fscanf(fp, "%d %d %d", &areaNum, &relation, &listNum);
	printf("%d %d %d\n", areaNum, relation, listNum);
	
	int i;
	int area[areaNum];	//�U�Ӱ϶����ϰ�j�p 
	for(i = 0;i < areaNum;i++){
		fscanf(fp, "%d", &area[i]);
	}
	
	int side1, side2;
	for(i = 0;i < relation;i++){
		fscanf(fp, "%d %d", &side1, &side2);
		printf("%d %d\n", side1, side2); 
	}
	
	int color[listNum][2];	//�x�s�U�C��Ҧ����ƶq�M�һݦ��� 
	char ch0, ch1, ch2;	//Ū���h�l��char 
	for(i = 0;i < listNum;i++){
		fscanf(fp, "%c%c%c", &ch0, &ch1, &ch2);
		fscanf(fp, "%d %d", &color[i][0], &color[i][1]);
		printf("%d %d\n", color[i][0], color[i][1]);
	}
	
	fclose(fp);
	system("pause");
	return 0;
}
