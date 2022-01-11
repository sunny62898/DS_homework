#include<stdlib.h>
#include<stdio.h>

/*
	�W����1-2 ������e��
	�Q�k : Ū�J��l�r��A�b�ѫ�V�e�}�l�P�_
		   �J��^��r�N������Jprefix[]��
		   �J��operators�P�_�u����
		   �p�G�p��쥻�boperator[]�̪��A�Npop���L�p���A�[�J�ۤv 
		   �p�G�j��쥻�̭����N�����[��operator[]��
		    
*/

struct oper{
	char symbol;
	int order;
};
int opjudge(char);

int main(){
	
	/*Ū��*/
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int Snum;	//�`�@���X�Ӧr��
	fscanf(fp, "%d", &Snum);
	
	int i, j, k;
	char str[200];			//�s��lstring
	char prefix[200];		//�ΨӦsprefix
	struct oper operators[200];	//�s�B��l
	 
	char ch;		//Ū�r��� 
	int strTop = 0;	//��l�r��s���
	int preTop = 0;	//prefix[]�s���
	int opTop = 0;	//operators[]�s���
	
	int judge;	//�sorder���G 
	
	fscanf(fp, "%c", &ch);	//Ū���Ĥ@�ӼƦr�᭱��'\n' 
	for(i = 0;i < Snum;i++){
		//��larray�̦s��� 
		strTop = 0;
		preTop = 0;
		opTop = 0; 
		
		while(1){
			fscanf(fp, "%c", &ch);
			if(ch == ' ' || ch == '\n'){	//�o���r�굲�� 
				break;
			}
			
			str[strTop] = ch;
			strTop++;
			
			
		}
		
		if(strTop == 0){	//�SŪ��F�� 
			continue;
		}
		
		for(j = strTop-1;j >= 0;j--){	//�ѫ᭱Ū�^�� 
			if((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z')){
				prefix[preTop] = str[j];	//�r�ꪽ���[�i�h
				preTop++; 
			}
			else{	//operator�n��� 
				if(opTop == 0){
					
					operators[opTop].symbol = str[j];
					operators[opTop].order = opjudge(str[j]);
					opTop++;
				}
				else{
					
					if(str[j] == ')'){	//�����[��operators
						operators[opTop].symbol = str[j];
						operators[opTop].order = opjudge(str[j]);
						opTop++;
					}
					else if(str[j] == '('){	//pop�� ')'
						for(k = opTop-1;k >= 0;k--){
							if(operators[k].symbol == ')'){
								break;
							}
							prefix[preTop] = operators[k].symbol;
							preTop++;
						} 
						opTop = k;
					}
					
					else{
						if(opTop == 0){
							operators[opTop].symbol = str[j];
							operators[opTop].order = opjudge(str[j]);
							opTop++;
						}
						else{
							if(operators[opTop-1].symbol == ')'){
								operators[opTop].symbol = str[j];
								operators[opTop].order = opjudge(str[j]);
								opTop++;
							}
							else{
								judge = opjudge(str[j]);
								if(judge >= operators[opTop-1].order){	//�O�o�P�u���v���n�L�X�� 
									
									for(k = opTop-1;k >= 0;k--){
										if(judge < operators[k].order || operators[k].symbol == ')'){
											break;
										}
										prefix[preTop] = operators[k].symbol;
										preTop++;
										
									}
									opTop = k+1;
									operators[opTop].order = judge;
									operators[opTop].symbol = str[j];
									opTop++;
								}
								else{	//�p�G�u���v������N�����\�ioperators[]
									operators[opTop].symbol = str[j];
									operators[opTop].order = opjudge(str[j]);
									opTop++;
									
								}
							}
						}
					}
				}
			}
		}
		
		//Ū������p�Goperators[]�̭��٦��F�� �N����pop
		if(opTop != 0){
			for(j = opTop-1;j >= 0;j--){
				prefix[preTop] = operators[j].symbol;
				preTop++;
			}
		}
		
		//���ױq�᭱Ū�^�� 
		for(j = preTop-1;j >= 0;j--){
			printf("%c ", prefix[j]);
		}
		printf("\n");
	}
	
	return 0;
}

int opjudge(char ch){
	switch(ch){
		case '(':
			return 1;
		case ')':
			return 1;
		case '*':
			return 2;
		case '%':
			return 2;
		case '/':
			return 2;
		case '+':
			return 3;
		case '-':
			return 3;
		case '>':
			return 4;
		case '<':
			return 4;
		case '&':
			return 5;
		case '|':
			return 5;
		case '^':
			return 5;
		default:
			return 0;
			
	}
	
}
