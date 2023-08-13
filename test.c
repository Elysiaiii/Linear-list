#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char ElemType;

#define MAXSIZE 100
typedef struct
{
	ElemType* elem;
	int length;
}SqList; //˳�������

//���Ա�L�ĳ�ʼ��
Status InitList_Sq(SqList L)								//����һ���յ�˳���L
{
	L.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE); //Ϊ˳������ռ�
	if (!L.elem) exit(ERROR);								//�洢����ʧ��
	L.length = 0;											//�ձ���Ϊ0
	return OK;
}
//�������Ա�L
void DestroyList(SqList L)
{
	if (L.elem) free(L.elem); //�ͷŴ洢�ռ�
}
//������Ա�L
void ClearList1(SqList L)
{
	L.length = 0;			  //�����Ա�����Ϊ0
}

//˳���ȡֵ
int GetElem(SqList L, int i, ElemType* e)
{
	if (i<1 || i>L.length) return ERROR;			//iֵ���Ϸ�
	e = L.elem[i - 1];
	return OK;
}
//˳������
Status ListInsert_Sq(SqList L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) return ERROR;	    //iֵ���Ϸ�
	if (L.length == MAXSIZE) return ERROR;			//��ǰ�洢�ռ�����
	for (int j = L.length - 1; j >= i - 1; j--)
	{
		L.elem[j + 1] = L.elem[j];					//����λ�ü�֮���Ԫ�غ���
	}
	L.elem[i - 1] = e;								//����Ԫ��e�����i��λ��
	L.length++;										//��+1
	return OK;
}
//˳���ɾ��
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

//�������ʼ��
typedef struct Lnode
{
	ElemType data;
	struct Lnode* next;
}Lnode, * LinkList;
//�ж������Ƿ�Ϊ��
int ListEmpty(LinkList L)		//��LΪ�ձ��򷵻�1�����򷵻�0
{
	if (L->next)				//�ǿ�
		return 0;
	else
		return 1;
}
//���ٵ�����
Status DestroyList_L(LinkList L)//��ͷָ�뿪ʼ�������ͷ����н��
{
	Lnode* p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
}
//��յ�����
Status ClearList2(LinkList L)
{
	Lnode* p, * q;
	p = L->next;
	while (p)					//û����β
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;				//ͷ���ָ����Ϊ��
	return OK;
}
//�������
int ListLength_L(LinkList L)	//����L������Ԫ�ظ���
{
	Lnode* p;
	int i = 0;
	p = L->next;				//pָ���һ�����
	while (p)					//����������ͳ�ƽ����
	{
		i++;
		p = p->next;
	}
	return i;
}
//������ȡֵ
Status GetElem_L(LinkList L, int i, ElemType* e)//��ȡ���Ա�L��ĳ������Ԫ�ص����ݣ�ͨ������e����
{
	Lnode* p = L->next;							//��ʼ��
	int j = 1;
	while (p && j < i)							//���ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) return ERROR;				//��i��Ԫ�ز�����
	e = p->data;								//ȡ��i��Ԫ��
	return OK;
}
//���������(�˴�Ϊ��ֵ����,����λ�����)
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
//���������
Status ListLnsert_L(LinkList L, int i, ElemType e) //��L�е�i��Ԫ��֮ǰ��������Ԫ��e
{
	Lnode* p = L;
	int j = 0;
	while (p && j < i - 1)							//Ѱ�ҵ�i-1����㣬pָ��i-1���(ע�ⲻ��i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) return ERROR;				//i���ڱ�+1��С��1������λ�÷Ƿ�
	Lnode* s = (LinkList)malloc(sizeof(Lnode));		//�����½��s�������s����������Ϊe
	s->data = e;									//�����s����L��
	s->next = p->next;
	p->next = s;
	return OK;
}
//������ɾ��
Status ListDelete_L(LinkList L, int i, ElemType* e) //�����Ա�L�е�i������Ԫ��ɾ��
{
	Lnode* p = L;
	Lnode* q;
	int j = 0;
	while (p->next && j < i - 1)					//Ѱ�ҵ�i����㣬����pָ����ǰ��
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i - 1) return ERROR;		//ɾ��λ�ò�����
	q = p->next;									//��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
	p->next = p->next->next;						//�ı�ɾ�����ǰ������ָ����
	e = q->data;									//����ɾ������������(���Բ��ã�
	free(q);										//�ͷ�ɾ�����Ŀռ�
	return OK;
}
//������ͷ�巨
void CreateList_H(LinkList L, int n)
{
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;									//�Ƚ���һ����ͷ���ĵ�����
	for (int i = n; i > 0; i--)
	{
		Lnode* p = (LinkList)malloc(sizeof(Lnode));	//�����½��
		scanf(&p->data);							//��������Ԫ��ֵ
		p->next = L->next;							//���뵽��ͷ
		L->next = p;
	}
}
//������β�巨
Status CreateList_R(LinkList L, int n)
{
	L = (LinkList)malloc(sizeof(Lnode));
	L->next = NULL;
	Lnode* r = L;									//βָ��rָ��ͷ���
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (LinkList)malloc(sizeof(Lnode));	//�����½�㣬��������Ԫ��ֵ
		scanf(&p->data);
		p->next = NULL;
		r->next = p;								//���뵽��β
		r = p;										//rָ���µ�β���
	}
}
int main()
{
	
}