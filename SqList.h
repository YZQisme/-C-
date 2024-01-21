#pragma once
#define TRUE 1
#define FALSE 0
#define DONE 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#include <stdlib.h>
#include <iostream>
static short increasetimes = 1;
class SqList {
protected:
	ElemType* FirstElem;//存储数据及其一些信息
	int listsize;
public:
	int length;
	//基本操作函数的声明
	SqList(void);
	~SqList(void);
	void ClearList();
	bool ListEmpty();
	int ListLength();
	Status GetElem(int i, ElemType* e);
	int LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType));
	Status PriorElem(ElemType cur_e, ElemType* pre_e);
	Status NextElem(ElemType cur_e, ElemType* next_e);
	Status ListInsert(int i, ElemType e);
	Status ListDelete(int i, ElemType* e);
	Status ListTraverse(Status(*visit)(ElemType));
	Status ListChange(int position,ElemType newelem);
};
