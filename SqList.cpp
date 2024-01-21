#include "SqList.h"
#include <iostream>
SqList::SqList(void) {//建立顺序表
	if (FirstElem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType))) {
		length = 0;
		listsize = LIST_INIT_SIZE;
	}
	else {
		std::cout << "内存申请失败，无法创建对象";
	}
}

SqList::~SqList(void) {//销毁顺序表
	free(FirstElem);
}

void SqList::ClearList() {//清理顺序表
	length = 0;
}

bool SqList::ListEmpty() {//判断顺序表是否为空
	return (length == 0);
}

int SqList::ListLength() {//获取长度
	return length;
}

Status SqList::GetElem(int i, ElemType* e) {//获取第i个元素
	if (i<1 || i>length) {
		return ERROR;
	}
	else {
		*e = FirstElem[i - 1];
		return DONE;
	}
}

int SqList::LocateElem(ElemType e, bool (*Compare)(ElemType, ElemType)) {
	if (SqList::ListEmpty()) {//寻找元素，返回第一个符合条件元素的位置（第1个元素的位置为1）
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

Status SqList::PriorElem(ElemType cur_e, ElemType* pre_e) {//返回特定元素前一个的元素
	if (*FirstElem == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem + 1; p < FirstElem + length; p++) {
		if (*p == cur_e) {
			pre_e = p - 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}

Status SqList::NextElem(ElemType cur_e, ElemType* next_e) {//返回特定元素后一个的元素
	if (*(FirstElem + length - 1) == cur_e) { return ERROR; }
	for (ElemType* p = FirstElem; p < FirstElem + length - 1; p++) {
		if (*p == cur_e) {
			next_e = p + 1;
			return DONE;
		}
	}
	return INFEASIBLE;
}

Status SqList::ListInsert(int i, ElemType e) {//在第i个元素前面插入元素
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

Status SqList::ListDelete(int i, ElemType* e) {//删除第i个元素
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

Status SqList::ListChange(int position, ElemType newelem) {//修改第position个元素
	if (position<1||position > length) { return ERROR; }
	*(FirstElem + position - 1) = newelem;
	return DONE;
}