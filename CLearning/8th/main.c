#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include <stdbool.h>

/*
	规定文法大写字母为非终结符，小写字母为终结符
	文法格式：E->E+T|a
	用@代替ε
*/

typedef struct{
	char *base;
	char *top;
	int stacksize;
}Stack;
Stack analyzeStack;

typedef struct{
    char formula[200]; //产生式
	char right[100][100]; //产生式右部
	int rightLen;	//产生式右部个数
	char left;	//产生式左部
	int ifnull; //是否有ε产生式
}grammarElement;
grammarElement  gramOldSet[200];//原始文法的产生式集

int gramOldSetLen=0;

char terSymbol[200];//终结符号
char non_ter[200];//非终结符号
char allSymbol[400];//所有符号
char firstSet[100][100];//各产生式右部的FIRST集
char followSet[100][100];//各产生式左部的FOLLOW集
int M[200][200];//分析表
int N[200][200];//进一步预测分析表

char b[100];//待分析的字符串

void inputSource();
void precope();
void getFirstSet();
int isNon_ter(char c);
int isTerSymbol(char c);
char *addtoFirstSet(char *s,char *t);
void getFollowSet();
void createAnalyseTable();
int analyzeString();
void initStack();
int push(char c);
int pop();
void destroyStack();

int main(){
	printf("请输入文法（以#结束）:\n");
	inputSource();
	precope();

	printf("----------------------------------\n");
	printf("文法为:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("%s\n",gramOldSet[i].formula);
		printf("left %c\n",gramOldSet[i].left);
		for(int temp=0;temp<gramOldSet[i].rightLen;temp++){
			printf("right[%d] %s\n",temp+1,gramOldSet[i].right[temp]);
		}
	}
	printf("----------------------------------\n");
	printf("终结符为:\n");
	for(int i=0;i<strlen(terSymbol);i++){
		printf("%c\n",terSymbol[i]);
	}
	printf("----------------------------------\n");
	printf("非终结符为:\n");
	for(int i=0;i<strlen(non_ter);i++){
		printf("%c\n",non_ter[i]);
	}
	printf("----------------------------------\n");
	getFirstSet();
	printf("FIRST集:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("FIRST(%c)={%s}\n",gramOldSet[i].left,firstSet[i]);
	}
	printf("----------------------------------\n");
	getFollowSet();
	printf("FOLLOW集:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("FOLLOW(%c)={%s}\n",gramOldSet[i].left,followSet[i]);
	}
	printf("-----------------\n");
	createAnalyseTable();
	printf("----------------------------------\n");
	printf("请输入要分析的字符串:\n");
	gets(b);
	int bLen=strlen(b);
	b[bLen]='#';
	b[bLen+1]='\0';
	printf("----------------------------------\n");
	int mark=analyzeString();
	if(mark==0){
		printf("error!\n");
	}else{
		printf("correct!\n");
	}
	return 0;
}

//输入文法
void inputSource(){
	int i=0;
	char a[500];
	while(true){
		gets(a);
		if(a[0]=='#'){
			break;
		}
		strcpy(gramOldSet[i].formula,a);
		gramOldSetLen++;
		i++;
	}
}

//处理文法产生式
void precope(){
	for(int i=0;i<gramOldSetLen;i++){
		int formulaLen=strlen(gramOldSet[i].formula);
		int mark1=0,mark2=-1;
		gramOldSet[i].rightLen=0;
		gramOldSet[i].ifnull=0;
		for(int j=0;j<formulaLen;j++){
			int flag=0;
			//扫描到->则跳过
			if(gramOldSet[i].formula[j]=='-'&&gramOldSet[i].formula[j+1]=='>'){
				gramOldSet[i].left=gramOldSet[i].formula[j-1];
				j++;
				mark1=j+1;
				mark2++;
				gramOldSet[i].rightLen++;
				flag=1;
				continue;
			}
			//扫描到或运算符 '|' 跳过
			if(gramOldSet[i].formula[j]=='|'){
				for(int temp=mark1;temp<j;temp++){
					gramOldSet[i].right[mark2][temp-mark1]=gramOldSet[i].formula[temp];
				}
				mark1=j+1;
				mark2++;
				gramOldSet[i].rightLen++;
				flag=2;
				continue;
			}
			//扫描到非终结符
			if(isupper(gramOldSet[i].formula[j])){
				flag=3;
				int non_terLen=strlen(non_ter);
				for(int count=0;count<non_terLen;count++){
					if(gramOldSet[i].formula[j]==non_ter[count]){
						flag=4;
						break;
					}
				}
				if(flag==3){
					non_ter[non_terLen]=gramOldSet[i].formula[j];
					non_ter[non_terLen+1]='\0';
					int allSymbolLen=strlen(allSymbol);
					allSymbol[allSymbolLen]=gramOldSet[i].formula[j];
					allSymbol[allSymbolLen+1]='\0';
				}
			}
			//扫描到终结符
			if(flag==0){
				if(gramOldSet[i].formula[j]=='@'){
					gramOldSet[i].ifnull=1;
					break;
				}
				flag=5;
				int terSymbolLen=strlen(terSymbol);
				for(int count=0;count<terSymbolLen;count++){
					if(gramOldSet[i].formula[j]==terSymbol[count]){
						flag=6;
						break;
					}
				}
				if(flag==5){
					terSymbol[terSymbolLen]=gramOldSet[i].formula[j];
					terSymbol[terSymbolLen+1]='\0';
					int allSymbolLen=strlen(allSymbol);
					allSymbol[allSymbolLen]=gramOldSet[i].formula[j];
					allSymbol[allSymbolLen+1]='\0';
				}
			}
		}
		for(int temp=mark1;temp<formulaLen;temp++){
			gramOldSet[i].right[mark2][temp-mark1]=gramOldSet[i].formula[temp];
		}
	}
	//将#加入终结符
	int terSymbolLen=strlen(terSymbol);
	terSymbol[terSymbolLen]='#';
	terSymbol[terSymbolLen+1]='\0';
	int allSymbolLen=strlen(allSymbol);
	allSymbol[allSymbolLen]='#';
	allSymbol[allSymbolLen+1]='\0';
}

//判断是否为终结符
int isTerSymbol(char c){
	int terSymbolLen=strlen(terSymbol);
	for(int i=0;i<terSymbolLen;i++){
		if(terSymbol[i]==c)
			return 1;
	}
	return 0;
}

//判断是否为非终结符
int isNon_ter(char c){
	int non_terLen=strlen(non_ter);
	for(int i=0;i<non_terLen;i++){
		if(non_ter[i]==c)
			return 1;
	}
	return 0;
}


//char *addtoFirstSet(char *s,char *t){
//	int slen=strlen(s);
//	int tlen=strlen(t);
//	for(int i=0;i<tlen;i++){
//		int flag=0;
//		for(int j=0;j<slen;j++){
//			if(t[i]==s[j]){
//				flag=1;
//			}
//		}
//		if(flag==0){
//			s[slen]=t[i];
//			slen++;
//			s[slen]='\0';
//		}
//	}
//	return s;
//}

//求first集
void getFirstSet(){
//	int k=0; //测试使用
	while(1){
	int judge=0,temp1=-1,mark=0; 	//判断一次循环后first集是否改变
	for(int i=0;i<gramOldSetLen;i++){
//		printf("%d\n",++k);
		for(int j=0;j<gramOldSet[i].rightLen;j++){
			int rightContentLen=strlen(gramOldSet[i].right[j]);
			for(int m=0;m<rightContentLen;m++){

				if(isTerSymbol(gramOldSet[i].right[j][m])){
					mark=1;
					int firstSetLen=strlen(firstSet[i]);
					int flag=0;
					for(int n=0;n<firstSetLen;n++){
						if(firstSet[i][n]==gramOldSet[i].right[j][m]){
							flag=1;
							break;
						}
					}
					if(flag==0){
						firstSet[i][firstSetLen]=gramOldSet[i].right[j][m];
						firstSet[i][firstSetLen+1]='\0';
						judge=1;
					}
					break;
				}else if(gramOldSet[i].right[j][m]=='@'){
					mark=2;
					int firstSetLen=strlen(firstSet[i]);
					int flag=0;
					for(int n=0;n<firstSetLen;n++){
						if(firstSet[i][n]==gramOldSet[i].right[j][m]){
							flag=1;
							break;
						}
					}
					if(flag==0){
						firstSet[i][firstSetLen]=gramOldSet[i].right[j][m];
						firstSet[i][firstSetLen+1]='\0';
						judge=1;
					}

				}else{
					mark=3;
					for(int n=0;n<gramOldSetLen;n++){
						if(gramOldSet[n].left==gramOldSet[i].right[j][m]){
							int slen=strlen(firstSet[i]);
							int tlen=strlen(firstSet[n]);
							for(int p=0;p<tlen;p++){
								int flag=0;
								for(int q=0;q<slen;q++){
									if(firstSet[n][p]==firstSet[i][q]){
										flag=1;
									}
								}
								if(flag==0){
									firstSet[i][slen]=firstSet[n][p];
									slen++;
									firstSet[i][slen]='\0';
									judge=1;
								}
							}
							temp1=n;
						}
					}
				}
				if(mark==3){
					//如果当前扫描到的非终结符没有ε产生式，不会扫描到下一字符
					if(!gramOldSet[temp1].ifnull){
						break;
					}
				}

			}

		}
	}
	if(judge==0){
		break;
	}
	}
}

void getFollowSet(){
//	int k=0;
	while(1){
		//temp1,temp2分别表示当前扫描到的非终结符和前一次扫描到的非终结符
		int judge=0,mark=0,temp1=-1,temp2=-1; 	//judge判断一次循环后follow集是否改变
		for(int i=0;i<gramOldSetLen;i++){
//			printf("%d\n",++k);
			if(i==0){
				int followSetLen=strlen(followSet[i]);
				int flag=0;
				for(int n=0;n<followSetLen;n++){
					if(followSet[i][n]=='#'){
						flag=1;
						break;
					}
				}
				if(flag==0){
					followSet[i][followSetLen]='#';
					followSet[i][followSetLen+1]='\0';
					judge=1;
				}
			}
			for(int j=0;j<gramOldSet[i].rightLen;j++){
				int rightContentLen=strlen(gramOldSet[i].right[j]);
				for(int m=rightContentLen-1;m>=0;m--){
					if(isNon_ter(gramOldSet[i].right[j][m])){
						for(int n=0;n<gramOldSetLen;n++){
							if(gramOldSet[n].left==gramOldSet[i].right[j][m]){
								temp1=n;
							}
						}
						if(m<rightContentLen-1){
							//A->αBβ是一个产生式,β为终结符把β 加至FOLLOW(B)
							if(isTerSymbol(gramOldSet[i].right[j][m+1])){
								int followSetLen=strlen(followSet[temp1]);
								int flag=0;
								for(int t=0;t<followSetLen;t++){
									if(followSet[temp1][t]==gramOldSet[i].right[j][m+1]){
										flag=1;
										break;
									}
								}
								if(flag==0){
									followSet[temp1][followSetLen]=gramOldSet[i].right[j][m+1];
									followSet[temp1][followSetLen+1]='\0';
									judge=1;
								}
							}else{
								//A->αBβ是一个产生式,β为非终结符把FIRST(β) 加至FOLLOW(B)
//								printf("temp2=%d\n",temp2);
								int slen=strlen(firstSet[temp2]);
								int tlen=strlen(followSet[temp1]);
								for(int p=0;p<slen;p++){
									if(firstSet[temp2][p]=='@'){
										continue;
									}
									int flag=0;
									for(int q=0;q<tlen;q++){
										if(followSet[temp1][q]==firstSet[temp2][p]){
											flag=1;
										}
									}
									if(flag==0){
										followSet[temp1][tlen]=firstSet[temp2][p];
										tlen++;
										followSet[temp1][tlen]='\0';
										judge=1;
									}
								}
							}

						}
						//若A->αB是一个产生式，或者A->αBβ是一个产生式 而ε属于FIRST(β) 则把FOLLOW(A)加至FOLLOW(B)中
						int tflag=0;
						for(int t=m+1;t<rightContentLen;t++){
							if(isNon_ter(gramOldSet[i].right[j][t])){
								for(int n=0;n<gramOldSetLen;n++){
									if(gramOldSet[n].left==gramOldSet[i].right[j][t]){
										if(!gramOldSet[n].ifnull){
											tflag=1;
										}
									}
								}
							}else{
								tflag=1;
							}
						}
						if(tflag==0){
							int slen=strlen(followSet[i]);
							int tlen=strlen(followSet[temp1]);
							for(int p=0;p<slen;p++){
								int flag=0;
								for(int q=0;q<tlen;q++){
									if(followSet[temp1][q]==followSet[i][p]){
										flag=1;
									}
								}
								if(flag==0){
									followSet[temp1][tlen]=followSet[i][p];
									tlen++;
									followSet[temp1][tlen]='\0';
									judge=1;
								}
							}
						}
					}else if(gramOldSet[i].right[j][m]=='@'){
						break;
					}
					temp2=temp1;
				}

			}
		}
		if(judge==0){
			break;
		}
	}
}

//构造预测分析表
void createAnalyseTable(){

	for(int i=0;i<gramOldSetLen;i++){
		int terSymbolLen=strlen(terSymbol);
		int flag=0;
		for(int j=0;j<terSymbolLen;j++){
			M[i][j]=0;
			N[i][j]=0;
			int firstSetLen=strlen(firstSet[i]);
			for(int k=0;k<firstSetLen;k++){
				if(firstSet[i][k]==terSymbol[j]){
					M[i][j]=1;
				}
				if(firstSet[i][k]=='@'){
					 flag=1;
				}
			}
		}
		if(flag==1){
			for(int j=0;j<terSymbolLen;j++){
				int followSetLen=strlen(followSet[i]);
				for(int k=0;k<followSetLen;k++){
					if(followSet[i][k]==terSymbol[j]){
						M[i][j]=2;
					}
				}
			}
		}
	}

	printf("预测分析表:\n");
	printf("|\t\t|");
	int terSymbolLen=strlen(terSymbol);
	for(int i=0;i<terSymbolLen;i++){
		printf("|\t%c\t|",terSymbol[i]);
	}
	printf("\n");
	for(int i=0;i<gramOldSetLen;i++){
		for(int j=-1;j<terSymbolLen;j++){

			if(j==-1){
				printf("|\t%c\t|",gramOldSet[i].left);
			}else{
				if(M[i][j]==0){
					printf("|\t\t|");
				}else if(M[i][j]==1){
					for(int m=0;m<gramOldSet[i].rightLen;m++){
						if(gramOldSet[i].right[m][0]!='@'){
							int rightContentLen=strlen(gramOldSet[i].right[m]);
							for(int k=0;k<rightContentLen;k++){
								if(isTerSymbol(gramOldSet[i].right[m][k])){
									if(gramOldSet[i].right[m][k]==terSymbol[j]){
										printf("|\t%c->%s\t|",gramOldSet[i].left,gramOldSet[i].right[m]);
										N[i][j]=m;		//N[i][j]记录预测表 文法对应右部
										break;
									}else{
										break;
									}
								}else{
									for(int n=0;n<gramOldSetLen;n++){
										if(gramOldSet[n].left==gramOldSet[i].right[m][k]){
											int flag=0;
											int firstSetLen=strlen(firstSet[n]);
											for(int p=0;p<firstSetLen;p++){
												if(firstSet[n][p]==terSymbol[j]){
													flag=1;
												}
											}
											if(flag==1){
												printf("|\t%c->%s\t|",gramOldSet[i].left,gramOldSet[i].right[m]);
												N[i][j]=m;
												break;
											}else if(!gramOldSet[i].ifnull){
												break;
											}
										}
									}
								}
							}
						}
					}
				}else if(M[i][j]==2){
					printf("|\t%c->ε\t|",gramOldSet[i].left);
				}
			}
		}
		printf("\n");
	}
}

//初始化栈
void initStack(){
	analyzeStack.base=(char*)malloc(50*sizeof(char));
	analyzeStack.stacksize=50;
	analyzeStack.top=analyzeStack.base;
}

//入栈操作
int push(char c){
	if(analyzeStack.top-analyzeStack.base>analyzeStack.stacksize){
		return 0;
	}
	*analyzeStack.top++=c;
	return 1;
}

//出栈操作
int pop(){
	if(analyzeStack.top==analyzeStack.base){
		return 0;
	}
	*--analyzeStack.top;
	return 1;
}

//遍历栈
void stackTraverse(){
	char *temp=analyzeStack.base;
	printf("|\t");
	while(temp!=analyzeStack.top){
		printf("%c",*temp);
		temp++;
	}
	printf("\t|");
}

//销毁栈操作
void destroyStack(){
	free(analyzeStack.base);
	analyzeStack.base=NULL;
	analyzeStack.top=NULL;
	analyzeStack.stacksize=0;
}

int analyzeString(){
	printf("错误分析表:\n");
	printf("|\t分析栈\t||\t输入串\t||\t附注\t|\n");
	initStack();
	char *stringPoint=b;//扫描字符串的指针
	push('#');
//	printf("%c\n",*(analyzeStack.top-1));
	push(gramOldSet[0].left);
	stackTraverse();
	printf("|\t%s\t|",stringPoint);
	printf("|\t\t|\n");
	int temp1=-1,temp2=-1,t=0;
	int blen=strlen(b);
	while(1){
		//栈顶指针和输入串指针都指向#，宣布分析成功
		if(*(analyzeStack.top-1)=='#'&&*stringPoint=='#'){
			stackTraverse();
			printf("|\t%s\t|",stringPoint);
			printf("|\tcorrect\t|\n");
			return 1;
		}
		//当前扫描字符不在非终结符内，则分析出错
		if(!isTerSymbol(*stringPoint)){
			stackTraverse();
			printf("|\t%s\t|",stringPoint);
			printf("|\terror\t|\n");
			return 0;
		}
		//扫描字符与当前栈顶字符匹配，则出栈，扫描下一字符
		if(*(analyzeStack.top-1)==*stringPoint){//*(analyzeStack.top-1)表示当前栈顶元素
			pop();
			stringPoint++;
			t++;
			stackTraverse();
			printf("|\t%s\t|",stringPoint);
			printf("|\t\t|\n");
		}else{
			for(int i=0;i<gramOldSetLen;i++){
				if(gramOldSet[i].left==*(analyzeStack.top-1)){
					temp1=i;
				}
			}
			int terSymbolLen=strlen(terSymbol);
			for(int i=0;i<terSymbolLen;i++){
				if(terSymbol[i]==*stringPoint){
					temp2=i;
				}
			}
			if(M[temp1][temp2]==0){
				stackTraverse();
				printf("|\t%s\t|",stringPoint);
				printf("|\terror\t|\n");
				return 0;
			}else if(M[temp1][temp2]==1){
				pop();
				int k=N[temp1][temp2];
				int rightContentLen=strlen(gramOldSet[temp1].right[k]);
				for(int i=rightContentLen-1;i>=0;i--){
					push(gramOldSet[temp1].right[k][i]);
				}
				stackTraverse();
				printf("|\t%s\t|",stringPoint);
				printf("|\t\t|\n");
			}else if(M[temp1][temp2]==2){
				pop();
				stackTraverse();
				printf("|\t%s\t|",stringPoint);
				printf("|\t\t|\n");
			}
		}
	}
	destroyStack();
}
