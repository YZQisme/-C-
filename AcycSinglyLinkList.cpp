#include "AcycSinglyLinkList.h"
#include <cstdlib>
#include <iostream>
#include <initializer_list>

ASL_List::ASLL_Iterator::ASLL_Iterator(ASL_List* ptr) {
	classptr = ptr;
	nodeptr = ptr->head->next;
}
ASL_List::ASLL_Iterator::ASLL_Iterator(ASL_List* ptr, int length) {
	classptr = ptr;
	nodeptr = ptr->tail;
}
//这些运算符是为了使链表操作像C++数组
ASLL_node* ASL_List::ASLL_Iterator::operator++(int) {
	if (ASLL_node* oldptr = this->nodeptr) {
		this->nodeptr = this->nodeptr->next;
		return oldptr;
	}
	else {
		return NULL;
	}
};
ASLL_node* ASL_List::ASLL_Iterator::operator++() {
	if (this->nodeptr = NULL) { 
		return NULL; 
	}else {
		this->nodeptr = this->nodeptr->next;
		return this->nodeptr;
	}
};
ElemType ASL_List::ASLL_Iterator::operator*() {
	return this->nodeptr->data;
};
ElemType ASL_List::ASLL_Iterator::operator[](int i) {
	ASLL_node* p=this->classptr->head;
	int times = 0;
	while (p&&times<i) {
		p = p->next;
		times++;
	}
	if (p == NULL|| times < i) { return NULL; }
	return p->data;
};
bool ASL_List::ASLL_Iterator::operator!=(ASLL_Iterator ptr) {
	if (this->nodeptr != ptr.nodeptr) {
		return 1;
	}
	return 0;
}

ASL_List::ASL_List() {
	if (head = (ASLL_node*)malloc(sizeof(ASLL_node))) {
		head->data = DONE;
		head->next = NULL;
		tail = NULL;
		length = 0;
	}
	else {
		std::cout << "创建对象失败";
	}
};
ASL_List::ASL_List(std::initializer_list <int> varlist) {
	if (head = (ASLL_node*)malloc(sizeof(ASLL_node))) {
		head->data = DONE;
		head->next = NULL;
		tail = NULL;
		length = 0;
	}
	else {
		std::cout << "创建对象失败";
	}
	ASLL_node* newnode = NULL,*lastnode=head;
	for (auto ptr = varlist.begin();ptr <varlist.end();ptr++) {
		if ((newnode=(ASLL_node*)malloc(sizeof(ASLL_node)))==NULL) {
			std::cout << "创建对象异常中断";
			break;
		}
		else {
			newnode->data = *ptr;
			newnode->next = NULL;
			lastnode->next = newnode;
			tail = newnode;
			length++;
			lastnode = newnode;
		}
	}
};
ASL_List::ASL_List(const ASL_List* parentlist) {
	if (head = (ASLL_node*)malloc(sizeof(ASLL_node))) {
		head->data = DONE;
		head->next = NULL;
		tail = NULL;
		length = 0;
	}
	else {
		std::cout << "创建对象失败";
	}
	ASLL_node* newnode = NULL,
		*lastnode=head,
		*par_ptr=parentlist->head->next;
	while (par_ptr) {
		if ((newnode=(ASLL_node*)malloc(sizeof(ASLL_node)))==NULL) {
			std::cout << "创建对象异常中断";
			break;
		}else {
			newnode->data = par_ptr->data;
			newnode->next = NULL;
			lastnode->next = newnode;
			lastnode = newnode;
			length++;
			tail = newnode;
			par_ptr = par_ptr->next;
		}
	}
}
ASL_List::~ASL_List() {
	ClearList();
	free(head);
};
void ASL_List::ClearList() {
	ASLL_node* p = head->next,*q=NULL;
	while (p) {
		q = p->next; 
		free(p);
		p = q;
	}
	length = 0;
	tail = NULL;
};
Status ASL_List::CreateList(int length) {
	if (head->next != NULL|| length <= 0) { return ERROR; }
	ASLL_node* newnode = NULL;
	if ((newnode = (ASLL_node*)malloc(sizeof(ASLL_node)))==NULL) {
		std::cout << "链表创建中断";
		return INFEASIBLE;
	}
	else {
		std::cout << "请为新的元素赋一个整数：";
		std::cin >> newnode->data;
		newnode->next = head->next;
		head->next = newnode;
		length=1;
		tail = newnode;
	}
	for (int i = 2; i <= length;i++) {
		if ((newnode = (ASLL_node*)malloc(sizeof(ASLL_node)))==NULL) {
			std::cout << "链表创建中断";
			return INFEASIBLE; 
		}else {
			std::cout << "请为新的元素赋一个整数：";
			std::cin >> newnode->data;
			newnode->next = head->next;
			head->next = newnode;
			length++;
		}
	}
	return DONE;
};
bool ASL_List::ListEmpty() {
	return (length==0);
};
int ASL_List::ListLength() {
	return length;
};
Status ASL_List::GetElem(int i, ElemType* e) {
	if (i <= 0) { return ASLLOVERFLOW; }
	ASLL_node* p = head->next;
	int j = 1;
	while (p&&j<i) {
		p = p->next;
		j++;
	}
	if (p == NULL) { return ASLLOVERFLOW; }
	*e = p->data;
	return DONE;
};
int ASL_List::LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType)) {
	ASLL_node* p = head->next;
	int i = 1;
	while (p) {
		if (Compare(e, p->data) == TRUE) {
			return i;
		}
		p = p->next;
		i++;
	}
	return -1;
};
Status ASL_List::PriorElem(ElemType cur_e, ElemType* pre_e) {
	if (head->next->data == cur_e) { return ERROR; }
	ASLL_node* ptr_first = head->next, *ptr_second = NULL;
	while (ptr_first) {
		if (ptr_first->data == cur_e) {
			*pre_e = ptr_second->data;
			return DONE;
		}
		ptr_second = ptr_first;
		ptr_first = ptr_first->next;
	}
	return ERROR;
};
Status ASL_List::NextElem(ElemType cur_e, ElemType* next_e) {
	ASLL_node* ptr = head->next;
	while (ptr) {
		if (ptr->data==cur_e) {
			break;
		}
		ptr = ptr->next;
	}
	if (ptr == NULL || ptr->next == NULL) {
		return ERROR;
	}
	*next_e = ptr->next->data;
	return DONE;
};
Status ASL_List::ListInsert(int i, ElemType e) {
	ASLL_node* newnode = NULL;
	if ((newnode = (ASLL_node*)malloc(sizeof(ASLL_node))) == NULL) { return ERROR; }
	newnode->data = e;
	if (i <= 0||i>length) { 
		free(newnode);
		return ASLLOVERFLOW; 
	}
	ASLL_node* ptr_first = head->next,*ptr_second=head;
	int j = 1;
	while (j<i) {
		ptr_second = ptr_first;
		ptr_first = ptr_first->next;
		j++;
	}
	newnode->next = ptr_first;
	ptr_second->next = newnode;
	length++;
	return DONE;
};//在第i个元素之前插入
Status ASL_List::ListDelete(int i, ElemType* e) {
	if (i <= 0 || i > length) { return INFEASIBLE; }
	ASLL_node* ptr_first = head->next, * ptr_second = head;
	int j = 1;
	while (j<i) {
		ptr_second = ptr_first;
		ptr_first = ptr_first->next;
		j++;
	}
	ptr_second->next = ptr_first->next;
	if (ptr_first == tail) {
		tail = ptr_second;
	}
	*e = ptr_first->data;
	free(ptr_first);
	length--;
	return DONE;
};
Status ASL_List::ListTraverse(Status(*visit)(ElemType)) {
	ASLL_node* ptr = head->next;
	while (ptr) {
		if (visit(ptr->data) != DONE) { return ERROR; }
		ptr = ptr->next;
	}
};
void ASL_List::ListReversal() {
	if (length >= 2) {
		ASLL_node* ptr_first=head->next->next,
			* ptr_second=head->next,
			* ptr_third = head;
		ptr_second->next = NULL;
		tail = ptr_second;
		while (ptr_first) {
			ptr_third = ptr_second;
			ptr_second = ptr_first;
			ptr_first = ptr_first->next;
			ptr_second->next = ptr_third;
		}
		head->next = ptr_second;
	}
}
void ASL_List::ListShow() {
	ASLL_node* ptr = head->next;
	while (ptr) {
		std::cout << ptr->data <<",";
		ptr = ptr->next;
	}
}