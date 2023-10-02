#include "SqList.h"
#include <iostream>

SqList::SqList(void) {
	if (FirstElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType))) {
		length = 0;
		listsize = LIST_INIT_SIZE;
	}
	else {
		std::cout << "内存申请失败，无法创建对象";
	}
}
SqList::~SqList(void) {
	free(FirstElem);
}
void SqList::Clear() {
	length = 0;
}
bool SqList::IsEmpty() {
	return (length == 0);
}
int SqList::GetLength() {
	return length;
}
Status SqList::GetElem(int i, ElemType* e) {
	if (i<1 || i>length) {
		return ERROR;
	}
	else {
		*e = FirstElem[i - 1];
		return DONE;
	}
}
int SqList::LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType)) {
	if (SqList::IsEmpty()) {
		return ERROR;
	}
	else {
		for (int i = 0; i < length; i++) {
			if (Compare(e, FirstElem[i])) {
				return (i + 1);
			}
		}
		return INFEASIBLE;
	}
}
Status SqList::PriorElem(ElemType cur_e, ElemType* pre_e) {
	if (*FirstElem == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem + 1; p < FirstElem + length; p++) {
		if (*p == cur_e) {
			pre_e = p - 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}
Status SqList::NextElem(ElemType cur_e, ElemType* next_e) {
	if (*(FirstElem + length - 1) == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem; p < FirstElem + length - 1; p++) {
		if (*p == cur_e) {
			next_e = p + 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}
Status SqList::ListInsert(int i, ElemType e) {
	if (i<1 || i>length + 1) { return ERROR; }
	if (length == listsize) {
		if ((ElemType*)realloc(FirstElem, (LISTINCREMENT * (increasetimes++) + LIST_INIT_SIZE) * sizeof(ElemType)) == NULL) {
			return ERROR;
		}
		else {
			listsize += LISTINCREMENT;
		}
	}
	for (ElemType* p = FirstElem + length - 1; p >= FirstElem + i - 1; p--) {
		*(p + 1) = *p;
	}
	*(FirstElem + i - 1) = e;
	length++;
	return DONE;
}
Status SqList::ListDelete(int i, ElemType* e) {
	*e = *(FirstElem + i - 1);
	for (ElemType* p = FirstElem + i; p <= FirstElem + length - 1; p++) {
		*(p - 1) = *p;
	}
	length--;
	return DONE;
}
Status SqList::ListTraverse(Status(*visit)(ElemType)) {
	for (int i = 1; i <= length; i++) {
		if (visit(*(FirstElem + i - 1)) == ERROR) {
			return ERROR;
		}
	}
	return DONE;
}