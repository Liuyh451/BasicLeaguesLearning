#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include <stdbool.h>

/*
	�涨�ķ���д��ĸΪ���ս����Сд��ĸΪ�ս��
	�ķ���ʽ��E->E+T|a
	��@�����
*/

typedef struct{
	char *base;
	char *top;
	int stacksize;
}Stack;
Stack analyzeStack;

typedef struct{
    char formula[200]; //����ʽ
	char right[100][100]; //����ʽ�Ҳ�
	int rightLen;	//����ʽ�Ҳ�����
	char left;	//����ʽ��
	int ifnull; //�Ƿ��ЦŲ���ʽ
}grammarElement;
grammarElement  gramOldSet[200];//ԭʼ�ķ��Ĳ���ʽ��

int gramOldSetLen=0;

char terSymbol[200];//�ս����
char non_ter[200];//���ս����
char allSymbol[400];//���з���
char firstSet[100][100];//������ʽ�Ҳ���FIRST��
char followSet[100][100];//������ʽ�󲿵�FOLLOW��
int M[200][200];//������
int N[200][200];//��һ��Ԥ�������

char b[100];//���������ַ���

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
	printf("�������ķ�����#������:\n");
	inputSource();
	precope();

	printf("----------------------------------\n");
	printf("�ķ�Ϊ:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("%s\n",gramOldSet[i].formula);
		printf("left %c\n",gramOldSet[i].left);
		for(int temp=0;temp<gramOldSet[i].rightLen;temp++){
			printf("right[%d] %s\n",temp+1,gramOldSet[i].right[temp]);
		}
	}
	printf("----------------------------------\n");
	printf("�ս��Ϊ:\n");
	for(int i=0;i<strlen(terSymbol);i++){
		printf("%c\n",terSymbol[i]);
	}
	printf("----------------------------------\n");
	printf("���ս��Ϊ:\n");
	for(int i=0;i<strlen(non_ter);i++){
		printf("%c\n",non_ter[i]);
	}
	printf("----------------------------------\n");
	getFirstSet();
	printf("FIRST��:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("FIRST(%c)={%s}\n",gramOldSet[i].left,firstSet[i]);
	}
	printf("----------------------------------\n");
	getFollowSet();
	printf("FOLLOW��:\n");
	for(int i=0;i<gramOldSetLen;i++){
		printf("FOLLOW(%c)={%s}\n",gramOldSet[i].left,followSet[i]);
	}
	printf("-----------------\n");
	createAnalyseTable();
	printf("----------------------------------\n");
	printf("������Ҫ�������ַ���:\n");
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

//�����ķ�
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

//�����ķ�����ʽ
void precope(){
	for(int i=0;i<gramOldSetLen;i++){
		int formulaLen=strlen(gramOldSet[i].formula);
		int mark1=0,mark2=-1;
		gramOldSet[i].rightLen=0;
		gramOldSet[i].ifnull=0;
		for(int j=0;j<formulaLen;j++){
			int flag=0;
			//ɨ�赽->������
			if(gramOldSet[i].formula[j]=='-'&&gramOldSet[i].formula[j+1]=='>'){
				gramOldSet[i].left=gramOldSet[i].formula[j-1];
				j++;
				mark1=j+1;
				mark2++;
				gramOldSet[i].rightLen++;
				flag=1;
				continue;
			}
			//ɨ�赽������� '|' ����
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
			//ɨ�赽���ս��
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
			//ɨ�赽�ս��
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
	//��#�����ս��
	int terSymbolLen=strlen(terSymbol);
	terSymbol[terSymbolLen]='#';
	terSymbol[terSymbolLen+1]='\0';
	int allSymbolLen=strlen(allSymbol);
	allSymbol[allSymbolLen]='#';
	allSymbol[allSymbolLen+1]='\0';
}

//�ж��Ƿ�Ϊ�ս��
int isTerSymbol(char c){
	int terSymbolLen=strlen(terSymbol);
	for(int i=0;i<terSymbolLen;i++){
		if(terSymbol[i]==c)
			return 1;
	}
	return 0;
}

//�ж��Ƿ�Ϊ���ս��
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

//��first��
void getFirstSet(){
//	int k=0; //����ʹ��
	while(1){
	int judge=0,temp1=-1,mark=0; 	//�ж�һ��ѭ����first���Ƿ�ı�
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
					//�����ǰɨ�赽�ķ��ս��û�ЦŲ���ʽ������ɨ�赽��һ�ַ�
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
		//temp1,temp2�ֱ��ʾ��ǰɨ�赽�ķ��ս����ǰһ��ɨ�赽�ķ��ս��
		int judge=0,mark=0,temp1=-1,temp2=-1; 	//judge�ж�һ��ѭ����follow���Ƿ�ı�
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
							//A->��B����һ������ʽ,��Ϊ�ս���Ѧ� ����FOLLOW(B)
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
								//A->��B����һ������ʽ,��Ϊ���ս����FIRST(��) ����FOLLOW(B)
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
						//��A->��B��һ������ʽ������A->��B����һ������ʽ ��������FIRST(��) ���FOLLOW(A)����FOLLOW(B)��
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

//����Ԥ�������
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

	printf("Ԥ�������:\n");
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
										N[i][j]=m;		//N[i][j]��¼Ԥ��� �ķ���Ӧ�Ҳ�
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
					printf("|\t%c->��\t|",gramOldSet[i].left);
				}
			}
		}
		printf("\n");
	}
}

//��ʼ��ջ
void initStack(){
	analyzeStack.base=(char*)malloc(50*sizeof(char));
	analyzeStack.stacksize=50;
	analyzeStack.top=analyzeStack.base;
}

//��ջ����
int push(char c){
	if(analyzeStack.top-analyzeStack.base>analyzeStack.stacksize){
		return 0;
	}
	*analyzeStack.top++=c;
	return 1;
}

//��ջ����
int pop(){
	if(analyzeStack.top==analyzeStack.base){
		return 0;
	}
	*--analyzeStack.top;
	return 1;
}

//����ջ
void stackTraverse(){
	char *temp=analyzeStack.base;
	printf("|\t");
	while(temp!=analyzeStack.top){
		printf("%c",*temp);
		temp++;
	}
	printf("\t|");
}

//����ջ����
void destroyStack(){
	free(analyzeStack.base);
	analyzeStack.base=NULL;
	analyzeStack.top=NULL;
	analyzeStack.stacksize=0;
}

int analyzeString(){
	printf("���������:\n");
	printf("|\t����ջ\t||\t���봮\t||\t��ע\t|\n");
	initStack();
	char *stringPoint=b;//ɨ���ַ�����ָ��
	push('#');
//	printf("%c\n",*(analyzeStack.top-1));
	push(gramOldSet[0].left);
	stackTraverse();
	printf("|\t%s\t|",stringPoint);
	printf("|\t\t|\n");
	int temp1=-1,temp2=-1,t=0;
	int blen=strlen(b);
	while(1){
		//ջ��ָ������봮ָ�붼ָ��#�����������ɹ�
		if(*(analyzeStack.top-1)=='#'&&*stringPoint=='#'){
			stackTraverse();
			printf("|\t%s\t|",stringPoint);
			printf("|\tcorrect\t|\n");
			return 1;
		}
		//��ǰɨ���ַ����ڷ��ս���ڣ����������
		if(!isTerSymbol(*stringPoint)){
			stackTraverse();
			printf("|\t%s\t|",stringPoint);
			printf("|\terror\t|\n");
			return 0;
		}
		//ɨ���ַ��뵱ǰջ���ַ�ƥ�䣬���ջ��ɨ����һ�ַ�
		if(*(analyzeStack.top-1)==*stringPoint){//*(analyzeStack.top-1)��ʾ��ǰջ��Ԫ��
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
