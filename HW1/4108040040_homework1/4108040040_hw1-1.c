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
			/*將算式存到str裡*/
			str[top].symbol = ch;
			str[top].priority = judgeChar(ch);
			top++;
		}
		else if(ch == '\n'){
			if(top == 0){  //如果stack為空跳過 
				continue;
			}
			
			/*顯示初始算式*/ 
			for(i = 0;i < top;i++){
				printf("%c", str[i].symbol);
			}
			printf("\n");
			
			/*設定stack*/
			char prefix[200];
			int pretop = 0;
			struct block operate[100];
			int optop = 0;
			
			for(i = top-1;i >= 0;i--){
				if(str[i].priority == 0){  //數字、英文字 、小數點 
					prefix[pretop] = str[i].symbol;
					pretop++;
					
				}
				else if(str[i].symbol == '-'){  //判斷是不是負數 
					if(str[i-1].priority != 0){  //是負號 
						prefix[pretop] = str[i].symbol;  //直接加到prefix 
						pretop++;
					}
					else{  //是減 
						prefix[pretop] = '\0';  //加空格 
						pretop++;
						if(optop != 0){  //operate不為空
							//compare
							if(operate[optop-1].priority < str[i].priority){  //裡面的比較優先 
								for(j = optop-1;j >= 0;j--){  //把operate stack pop 到優先序比較低 
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
									
								optop = j+1;  //重設optop 
							} 
							
						}
						
						operate[optop].symbol = str[i].symbol;
						operate[optop].priority = str[i].priority;
						optop++;
						
					}
				}
				else{  //運算子 
					prefix[pretop] = '\0';  //加空格  
					pretop++;
					
					if(optop != 0){  //operate不為空
					
						//compare
						if(operate[optop-1].symbol != ')' && operate[optop-1].priority < str[i].priority){  //裡面的比較優先
							for(j = optop-1;j >= 0;j--){  //把operate stack pop 到優先序比較低
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
								
							optop = j+1;  //重設optop 
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
			
			//讀完之後把剩下的operate stack pop完
			if(optop != 0){
				prefix[pretop] = '\0';
				pretop++;
				for(i = optop-1;i >= 0;i--){  //把operate stack全部pop
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
			
			/*寫入*/
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
			
			
			//把stack清空為0 
			optop = 0;
			pretop = 0;
			top = 0;  
			
		}
	
	}
	
	fclose(fp);  //關檔 
	
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
		
		default :   //數字或英文字 
			return 0;
			
	} 
}





