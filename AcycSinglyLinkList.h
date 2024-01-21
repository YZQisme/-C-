#pragma once
#include <iostream>
#include <initializer_list>
#define TRUE 1
#define FALSE 0
#define DONE 1
#define ERROR 0
#define INFEASIBLE -1
#define ASLLOVERFLOW -2
typedef int Status;
typedef int ElemType;
struct ASLL_node{
	ElemType data;
	ASLL_node* next;
};
class ASL_List {
protected:
	ASLL_node* head;
	ASLL_node* tail;
	int length;
	class ASLL_Iterator {//迭代器，简化链表访问和操作
	protected:
		ASL_List* classptr;
		ASLL_node* nodeptr;
	public:
		ASLL_Iterator(ASL_List* ptr);
		ASLL_Iterator(ASL_List* ptr,int length);
		ASLL_node* operator++(int);
		ASLL_node* operator++();
		ElemType operator*();
		ElemType operator[](int);
		bool operator!=(ASLL_Iterator ptr);
	};
public:
	ASLL_Iterator begin() {
		return ASLL_Iterator(this);
	};
	ASLL_Iterator end() {
		return ASLL_Iterator(this, length);
	};
	ASL_List();
	ASL_List(std::initializer_list <int> varlist);
	ASL_List(const ASL_List* parentlist);
	~ASL_List();
	void ClearList();
	Status CreateList(int length);
	bool ListEmpty();
	int ListLength();
	Status GetElem(int i, ElemType* e);
	int LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType));
	Status PriorElem(ElemType cur_e, ElemType* pre_e);
	Status NextElem(ElemType cur_e, ElemType* next_e);
	Status ListInsert(int i, ElemType e);
	Status ListDelete(int i, ElemType* e);
	Status ListTraverse(Status(*visit)(ElemType));
	void ListReversal();
	void ListShow();
};