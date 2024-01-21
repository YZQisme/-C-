#include "SqList.h"
#include <iostream>
SqList::SqList(void) {//����˳���
	if (FirstElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType))) {
		length = 0;
		listsize = LIST_INIT_SIZE;
	}
	else {
		std::cout << "�ڴ�����ʧ�ܣ��޷���������";
	}
}

SqList::~SqList(void) {//����˳���
	free(FirstElem);
}

void SqList::ClearList() {//����˳���
	length = 0;
}

bool SqList::ListEmpty() {//�ж�˳����Ƿ�Ϊ��
	return (length == 0);
}

int SqList::ListLength() {//��ȡ����
	return length;
}

Status SqList::GetElem(int i, ElemType* e) {//��ȡ��i��Ԫ��
	if (i<1 || i>length) {
		return ERROR;
	}
	else {
		*e = FirstElem[i - 1];
		return DONE;
	}
}

int SqList::LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType)) {
	if (SqList::ListEmpty()) {//Ѱ��Ԫ�أ����ص�һ����������Ԫ�ص�λ�ã���1��Ԫ�ص�λ��Ϊ1��
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

Status SqList::PriorElem(ElemType cur_e, ElemType* pre_e) {//�����ض�Ԫ��ǰһ����Ԫ��
	if (*FirstElem == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem + 1; p < FirstElem + length; p++) {
		if (*p == cur_e) {
			pre_e = p - 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}

Status SqList::NextElem(ElemType cur_e, ElemType* next_e) {//�����ض�Ԫ�غ�һ����Ԫ��
	if (*(FirstElem + length - 1) == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem; p < FirstElem + length - 1; p++) {
		if (*p == cur_e) {
			next_e = p + 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}

Status SqList::ListInsert(int i, ElemType e) {//�ڵ�i��Ԫ��ǰ�����Ԫ��
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

Status SqList::ListDelete(int i, ElemType* e) {//ɾ����i��Ԫ��
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

Status SqList::ListChange(int position, ElemType newelem) {//�޸ĵ�position��Ԫ��
	if (position<1||position > length) { return ERROR; }
	*(FirstElem + position - 1) = newelem;
	return DONE;
}