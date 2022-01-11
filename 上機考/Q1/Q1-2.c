#include<stdlib.h>
#include<stdio.h>

/*
	上機考1-2 中序轉前序
	想法 : 讀入初始字串，在由後向前開始判斷
		   遇到英文字就直接放入prefix[]中
		   遇到operators判斷優先序
		   如果小於原本在operator[]裡的，就pop到比他小的再加入自己 
		   如果大於原本裡面的就直接加到operator[]裡
		    
*/

struct oper{
	char symbol;
	int order;
};
int opjudge(char);

int main(){
	
	/*讀檔*/
	FILE *fp;
	fp = fopen("input_2.txt", "r");
	
	int Snum;	//總共有幾個字串
	fscanf(fp, "%d", &Snum);
	
	int i, j, k;
	char str[200];			//存初始string
	char prefix[200];		//用來存prefix
	struct oper operators[200];	//存運算子
	 
	char ch;		//讀字串用 
	int strTop = 0;	//初始字串存到哪
	int preTop = 0;	//prefix[]存到哪
	int opTop = 0;	//operators[]存到哪
	
	int judge;	//存order結果 
	
	fscanf(fp, "%c", &ch);	//讀掉第一個數字後面的'\n' 
	for(i = 0;i < Snum;i++){
		//初始array們存到哪 
		strTop = 0;
		preTop = 0;
		opTop = 0; 
		
		while(1){
			fscanf(fp, "%c", &ch);
			if(ch == ' ' || ch == '\n'){	//這條字串結束 
				break;
			}
			
			str[strTop] = ch;
			strTop++;
			
			
		}
		
		if(strTop == 0){	//沒讀到東西 
			continue;
		}
		
		for(j = strTop-1;j >= 0;j--){	//由後面讀回來 
			if((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z')){
				prefix[preTop] = str[j];	//字串直接加進去
				preTop++; 
			}
			else{	//operator要比較 
				if(opTop == 0){
					
					operators[opTop].symbol = str[j];
					operators[opTop].order = opjudge(str[j]);
					opTop++;
				}
				else{
					
					if(str[j] == ')'){	//直接加到operators
						operators[opTop].symbol = str[j];
						operators[opTop].order = opjudge(str[j]);
						opTop++;
					}
					else if(str[j] == '('){	//pop到 ')'
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
								if(judge >= operators[opTop-1].order){	//記得同優先權的要印出來 
									
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
								else{	//如果優先權比較高就直接擺進operators[]
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
		
		//讀完之後如果operators[]裡面還有東西 就全部pop
		if(opTop != 0){
			for(j = opTop-1;j >= 0;j--){
				prefix[preTop] = operators[j].symbol;
				preTop++;
			}
		}
		
		//答案從後面讀回來 
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
