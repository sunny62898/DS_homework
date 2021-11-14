#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int judgeChar(char ch);

struct block{
	char symbol;
	int priority;
};

int main(){
	
	FILE *fp;
	fp = fopen("input_1.txt", "r");
	
	if(fp == NULL){
		printf("Error ! opening file");
		exit(1); 
	}
	
	struct block str[100];
	int top = 0;
	char ch;
	int i,j;
	
	while((fscanf(fp, "%c", &ch)) != EOF){
		if(ch != ' ' && ch != '\n'){
			/*�N�⦡�s��str��*/
			str[top].symbol = ch;
			str[top].priority = judgeChar(ch);
			top++;
		}
		else if(ch == '\n'){
			if(top == 0){  //�p�Gstack���Ÿ��L 
				continue;
			}
			
			/*��ܪ�l�⦡*/ 
			for(i = 0;i < top;i++){
				printf("%c", str[i].symbol);
			}
			printf("\n");
			
			/*�]�wstack*/
			char prefix[200];
			int pretop = 0;
			struct block operate[100];
			int optop = 0;
			
			for(i = top-1;i >= 0;i--){
				if(str[i].priority == 0){  //�Ʀr�B�^��r �B�p���I 
					prefix[pretop] = str[i].symbol;
					pretop++;
					
				}
				else if(str[i].symbol == '-'){  //�P�_�O���O�t�� 
					if(str[i-1].priority != 0){  //�O�t�� 
						prefix[pretop] = str[i].symbol;  //�����[��prefix 
						pretop++;
					}
					else{  //�O�� 
						prefix[pretop] = '\0';  //�[�Ů� 
						pretop++;
						if(optop != 0){  //operate������
							//compare
							if(operate[optop-1].priority < str[i].priority){  //�̭�������u�� 
								for(j = optop-1;j >= 0;j--){  //��operate stack pop ���u���Ǥ���C 
									if(operate[j+1].symbol != '(' && operate[j].priority >= str[i].priority){
										
										break;
									}
		
									if(operate[j].symbol != ')' && operate[j].symbol != '('){
										prefix[pretop] = operate[j].symbol;
										pretop++;
										prefix[pretop] = '\0';
										pretop++;
									}
								}
									
								optop = j+1;  //���]optop 
							} 
							
						}
						
						operate[optop].symbol = str[i].symbol;
						operate[optop].priority = str[i].priority;
						optop++;
						
					}
				}
				else{  //�B��l 
					prefix[pretop] = '\0';  //�[�Ů�  
					pretop++;
					
					if(optop != 0){  //operate������
					
						//compare
						if(operate[optop-1].symbol != ')' && operate[optop-1].priority < str[i].priority){  //�̭�������u��
							for(j = optop-1;j >= 0;j--){  //��operate stack pop ���u���Ǥ���C
								if(operate[optop-1].symbol == '('){
									if(operate[j+1].symbol != '(' && operate[j].priority >= str[i].priority){
										break;
									}
								}
								else{
									if(operate[j].symbol == ')' || operate[j].priority >= str[i].priority){
										break;
									}
								} 
								
	
								if(operate[j].symbol != ')' && operate[j].symbol != '('){
									prefix[pretop] = operate[j].symbol;
									pretop++;
									prefix[pretop] = '\0';
									pretop++;
								}
							}
								
							optop = j+1;  //���]optop 
						}
							
								
						operate[optop].symbol = str[i].symbol;
						operate[optop].priority = str[i].priority;
						optop++;
					
						
					}
					else{
						operate[optop].symbol = str[i].symbol;
						operate[optop].priority = str[i].priority;
						optop++;
					}
					
				}
			}
			
			//Ū�������ѤU��operate stack pop��
			if(optop != 0){
				prefix[pretop] = '\0';
				pretop++;
				for(i = optop-1;i >= 0;i--){  //��operate stack����pop
					if(operate[i].symbol != ')' && operate[i].symbol != '('){
						prefix[pretop] = operate[i].symbol;
						pretop++;
						if(i != 0){
							prefix[pretop] = '\0';
							pretop++;
						}
					} 
					
					
				}
			}
			
			
			for(i =  pretop-1;i >= 0;i--){
				printf("%c",prefix[i]);
			}
			printf("\n\n");
			
			/*�g�J*/
			FILE *foutput;
			foutput = fopen("output_1.txt", "a");
			for(i =  pretop-1;i >= 0;i--){
				if(prefix[i] == '\0' && prefix[i+1] == '\0'){
					continue;
				}
				fprintf(foutput ,"%c", prefix[i]);
			}
			fprintf(foutput ,"\n");
			fclose(foutput);
			
			
			//��stack�M�Ŭ�0 
			optop = 0;
			pretop = 0;
			top = 0;  
			
		}
	
	}
	
	fclose(fp);  //���� 
	
	system("pause");
	return 0;
}

int judgeChar(char ch){
	switch(ch){ 
		case '(' :
			return 1;
		case ')' :
			return 1;
		case '*' :
			return 2;
		case '%' :
			return 2;
		case '/' :
			return 2;
		case '+' :
			return 3;
		case '-' :
			return 3;
		case '>' :
			return 4;
		case '<' :
			return 4;
		case '&' :
			return 5;
		case '^' :
			return 5;
		case '|' :
			return 5;
		
		default :   //�Ʀr�έ^��r 
			return 0;
			
	} 
}





