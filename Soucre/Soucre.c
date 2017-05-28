#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char ExpressionEnter[60];

int max;

int DispatchExpression(void);							//将字符串数据填充到链表 
void Multiplication(void);							//乘除法运算 
void AdditionOperation(void);						//加减法运算
double Result(void);

void RandExpression(void);
char MarkRand(void);
 

typedef struct expression
{
	double Number;
	char Mark;
	struct expression *Last;
	struct expression *Next;
}Expression;					//表达式结构体定义 

Expression *Head = NULL;		//链表头指针 

int main(void)
{
	double Enter,RightResult;
	int Score = 0;
	int Num;
	int count = 0;
	srand((unsigned)time(NULL));
	printf("首先输入练习题目数量:\n");
	scanf("%d",&Num);
	system("cls");
	printf("请输入算式数字上限:");
	scanf("%d",&max); 
	while(Num > count)
	{
		RandExpression();
		RightResult = Result();
		system("cls");
		printf("*************************四则运算练习*************************\n");
		printf("                         已做:%d\n",count);
		printf(ExpressionEnter);
		printf("\n");
		scanf("%lf",&Enter);
		if(Enter == RightResult)
		{
			printf("正确!分数+10\n");
			Score += 10;
			Head = NULL;
			ExpressionEnter[0] = '\0';
		}
		count++;
	}
	return 0; 
}

void RandExpression(void)
{
	int a,b,c,d;
	char e,f,g;
	a = rand() % max;
	b = rand() % max;
	c = rand() % max;
	d = rand() % max;
	e = MarkRand();
	f = MarkRand();
	g = MarkRand();
	sprintf(ExpressionEnter,"%d%c%d%c%d%c%d=",a,e,b,f,c,g,d);
	return;
}

char MarkRand(void)
{
	int Mark = rand() % 4;
	switch(Mark)
	{
		case 0: return '+';
		case 1: return '-';
		case 2: return '*';
		case 3: return '/';
	}
}

void Multiplication(void)
{
	struct expression *pTmp = Head;
	struct expression *Next;
	double Tmp;
	while(pTmp)
	{
		if(pTmp->Mark == '*')
		{
			Tmp = pTmp->Last->Number * pTmp->Next->Number;
			((pTmp->Last)->Number) = Tmp;
			pTmp = pTmp->Last;
			Next = pTmp->Next;
			pTmp->Next = ((pTmp->Next)->Next)->Next;
			free(Next); 
			pTmp->Next->Last = pTmp;
		}
		else if(pTmp->Mark == '/')
		{
			(pTmp->Last)->Number = (pTmp->Last)->Number / (pTmp->Next)->Number;
			pTmp = pTmp->Last;
			Next = pTmp->Next;
			pTmp->Next = ((pTmp->Next)->Next)->Next;
			free(Next);
			pTmp->Next->Last = pTmp;
		}
		pTmp = pTmp->Next;
	}
	return;
}

void AdditionOperation(void)
{
	struct expression *pTmp = Head;
	struct expression *Next;
	double Tmp;
	while(pTmp)
	{
		if(pTmp->Mark == '+')
		{
			Tmp = pTmp->Last->Number + pTmp->Next->Number;
			((pTmp->Last)->Number) = Tmp;
			pTmp = pTmp->Last;
			Next = pTmp->Next;
			pTmp->Next = ((pTmp->Next)->Next)->Next;
			free(Next); 
			pTmp->Next->Last = pTmp;
		}
		else if(pTmp->Mark == '-')
		{
			(pTmp->Last)->Number = (pTmp->Last)->Number - (pTmp->Next)->Number;
			pTmp = pTmp->Last;
			Next = pTmp->Next;
			pTmp->Next = ((pTmp->Next)->Next)->Next;
			free(Next);
			pTmp->Next->Last = pTmp;
		}
		pTmp = pTmp->Next;
	}
	return;
}

int DispatchExpression(void)
{
	char Tmp[60];
	int ImmortalA,ImmortalT;
	Expression* pTmp;
	for(ImmortalA = ImmortalT = 0;ExpressionEnter[ImmortalA] != '\0';ImmortalA++,ImmortalT++)
	{
		if(ExpressionEnter[ImmortalA] == '+'||ExpressionEnter[ImmortalA] == '='||ExpressionEnter[ImmortalA] == '-'||ExpressionEnter[ImmortalA] == '*'||ExpressionEnter[ImmortalA] == '/')
		{
			Tmp[ImmortalT] = '\0';
			if(Head == NULL)
			{
				Head = (Expression*)malloc(sizeof(Expression));
				Head->Last = Head;
				Head->Next = NULL;
				Head->Number = atof(Tmp);
				Head->Mark = 0;
				pTmp = Head;
			}
			else
			{
				pTmp->Next = (Expression*)malloc(sizeof(Expression));
				(pTmp->Next)->Last = pTmp;
				(pTmp->Next)->Next = NULL;
				pTmp->Next->Number = atof(Tmp);
				pTmp->Next->Mark = 0;
				pTmp = pTmp->Next;
			}
			pTmp->Next = (Expression*)malloc(sizeof(Expression));
			(pTmp->Next)->Last = pTmp;
			(pTmp->Next)->Next = NULL;
			pTmp->Next->Mark =  ExpressionEnter[ImmortalA];
			pTmp = pTmp->Next;
			ImmortalT = -1;
		}
		Tmp[ImmortalT] = ExpressionEnter[ImmortalA];
	}
	return 0;
}

double Result(void)
{
	int b;
	double c;
	DispatchExpression();
	Multiplication();						
	AdditionOperation();
	b = (int)(Head->Number*100);
	c = b/100.0;
	return c;	
}
