#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;

#define MAXSIZE 100
typedef struct
{
	ElemType* elem;
	int length;
}SqList; //顺序表类型

//线性表L的初始化
Status InitList_Sq(SqList L)								//构建一个空的顺序表L
{
	L.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE); //为顺序表分配空间
	if (!L.elem) exit(ERROR);								//存储分配失败
	L.length = 0;											//空表长度为0
	return OK;
}
//销毁线性表L
void DestroyList(SqList L)
{
	if (L.elem) free(L.elem); //释放存储空间
}
//清空线性表L
void ClearList1(SqList L)
{
	L.length = 0;			  //将线性表长度置为0
}

//顺序表取值
int GetElem(SqList L, int i, ElemType* e)
{
	if (i<1 || i>L.length) return ERROR;			//i值不合法
	e = L.elem[i - 1];
	return OK;
}
//顺序表插入
Status ListInsert_Sq(SqList L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) return ERROR;	    //i值不合法
	if (L.length == MAXSIZE) return ERROR;			//当前存储空间已满
	for (int j = L.length - 1; j >= i - 1; j--)
	{
		L.elem[j + 1] = L.elem[j];					//插入位置及之后的元素后移
	}
	L.elem[i - 1] = e;								//将新元素e放入第i个位置
	L.length++;										//表长+1
	return OK;
}
//顺序表删除
Status ListDelete_Sq(SqList L, int i)
{
	if (i<1 || i>L.length) return ERROR;
	for (int j = i; j < L.length; j++)
	{
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;
	return OK;
}

//单链表初始化
typedef struct Lnode
{
	ElemType data;
	struct Lnode* next;
}Lnode, * LinkList;
//判断链表是否为空
int ListEmpty(LinkList L)		//若L为空表，则返回1，否则返回0
{
	if (L->next)				//非空
		return 0;
	else
		return 1;
}
//销毁单链表
Status DestroyList_L(LinkList L)//从头指针开始，依次释放所有结点
{
	Lnode* p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
}
//清空单链表
Status ClearList2(LinkList L)
{
	Lnode* p, * q;
	p = L->next;
	while (p)					//没到表尾
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;				//头结点指针域为空
	return OK;
}
//求单链表表长
int ListLength_L(LinkList L)	//返回L中数据元素个数
{
	Lnode* p;
	int i = 0;
	p = L->next;				//p指向第一个结点
	while (p)					//遍历单链表，统计结点数
	{
		i++;
		p = p->next;
	}
	return i;
}
//单链表取值
Status GetElem_L(LinkList L, int i, ElemType* e)//获取线性表L中某个数据元素的内容，通过变量e返回
{
	Lnode* p = L->next;							//初始化
	int j = 1;
	while (p && j < i)							//向后扫描，直到p指向第i个元素或p为空
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) return ERROR;				//第i个元素不存在
	e = p->data;								//取第i个元素
	return OK;
}
//单链表查找(此处为按值查找,返回位置序号)
Status LocateElem_L(LinkList L, ElemType e)
{
	Lnode* p = L->next;
	int j = 1;
	while (p || p->data != e)
	{
		p = p->next;
		j++;
	}
	if (p)
		return j;
	else
		return 0;
}
//单链表插入
Status ListLnsert_L(LinkList L, int i, ElemType e) //在L中第i个元素之前插入数据元素e
{
	Lnode* p = L;
	int j = 0;
	while (p && j < i - 1)							//寻找第i-1个结点，p指向i-1结点(注意不是i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) return ERROR;				//i大于表长+1或小于1，插入位置非法
	Lnode* s = (LinkList)malloc(sizeof(Lnode));		//生成新结点s，将结点s的数据域置为e
	s->data = e;									//将结点s插入L中
	s->next = p->next;
	p->next = s;
	return OK;
}
//单链表删除
Status ListDelete_L(LinkList L, int i, ElemType* e) //将线性表L中第i个数据元素删除
{
	Lnode* p = L;
	Lnode* q;
	int j = 0;
	while (p->next && j < i - 1)					//寻找第i个结点，并令p指向其前驱
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i - 1) return ERROR;		//删除位置不合理
	q = p->next;									//临时保存被删结点的地址以备释放
	p->next = p->next->next;						//改变删除结点前驱结点的指针域
	e = q->data;									//保存删除结点的数据域(可以不用）
	free(q);										//释放删除结点的空间
	return OK;
}
//单链表头插法
void CreateList_H(LinkList L, int n)
{
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;									//先建立一个带头结点的单链表
	for (int i = n; i > 0; i--)
	{
		Lnode* p = (LinkList)malloc(sizeof(Lnode));	//生成新结点
		scanf(&p->data);							//输入数据元素值
		p->next = L->next;							//插入到表头
		L->next = p;
	}
}
//单链表尾插法
Status CreateList_R(LinkList L, int n)
{
	L = (LinkList)malloc(sizeof(Lnode));
	L->next = NULL;
	Lnode* r = L;									//尾指针r指向头结点
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (LinkList)malloc(sizeof(Lnode));	//生成新结点，输入数据元素值
		scanf(&p->data);
		p->next = NULL;
		r->next = p;								//插入到表尾
		r = p;										//r指向新的尾结点
	}
}
int main()
{
	
}