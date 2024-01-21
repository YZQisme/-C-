# include "MyStack.h"
template <typename DataType>
MyStack<DataType>::MyStack() {
	if ((base = (DataType*)malloc(STACK_INIT_SIZE * sizeof(DataType))) != NULL) {
		stacksize = STACK_INIT_SIZE;
		top = base;
		stacklength=0;
	}
	else {
		std::cout << "内存分配错误";
	}
};

template <typename DataType> 
MyStack<DataType>::MyStack(std::initializer_list<DataType> varlist) {
	if ((base = (DataType*)malloc(STACK_INIT_SIZE * sizeof(DataType))) == NULL) {
		std::cout << "内存分配错误";
	}
	else {
		stacksize = STACK_INIT_SIZE;
		top = base;
		stacklength=0;
		auto var_ptr_end = varlist.end();
		int i = 0;
		for (auto var_ptr = varlist.begin(); var_ptr <= var_ptr_end; var_ptr++,i++) {
			if (stacksize <= stacklength) {
				if (!StackIncrease()) { 
					std::cout << "对象生成中断";
					break;
				}
			}
			*(base + i) = *var_ptr;
			top++;
			stacklength++;
		}
	}
};

template <typename DataType> 
MyStack<DataType>::MyStack(MyStack<DataType>* parent_ptr) {
	if ((base = (DataType*)malloc(STACK_INIT_SIZE * sizeof(DataType))) == NULL) {
		std::cout << "内存分配错误";
	}
	else {
		stacksize = STACK_INIT_SIZE;
		top = base;
		stacklength=0;
		DataType* var_ptr_end = parent_ptr->top;
		int i = 0;
		for (DataType* var_ptr = parent_ptr->base; var_ptr < var_ptr_end; var_ptr++, i++) {
			if (stacksize >= stacklength) {
				if (!StackIncrease()) {
					std::cout << "对象生成中断";
					break;
				}
			}
			*(base + i) = *var_ptr;
			top++;
			stacklength++;
		}
	}
};

template <typename DataType> 
MyStack<DataType>::~MyStack() {
	free(base);
};

template <typename DataType>
bool MyStack<DataType>::StackIncrease() {
	if ((DataType*)realloc(base, stacksize + STACK_INCREMENT) == NULL) {
		return FALSE;
	}
	else {
		stacksize += STACK_INCREMENT;
		return TRUE;
	}
};

template <typename DataType>
void  MyStack<DataType>::ClearStack() {
	stacklength = 0;
	top = base;
};

template <typename DataType>
bool MyStack<DataType>::StackEmpty() {
	return (base==top);
};

template <typename DataType> 
int MyStack<DataType>::StackLength() {
	return (top-base)/sizeof(DataType);
};

template <typename DataType>
const DataType MyStack<DataType>::GetTop() {
	if (StackLength() == 0) { throw ERROR; }
	return *(top-1);
};

template <typename DataType>
void MyStack<DataType>::Push(DataType newdata) {
	if (stacklength >= stacksize) {
		if (StackIncrease() == FALSE) { throw ERROR; }
	}
	*top = newdata;
	top++;
	stacklength++;
};

template <typename DataType> 
DataType MyStack<DataType>::Pop() {
	if (base >= top) { throw ERROR; }
	DataType topdata;
	topdata = *(top-1);
	top--;
	stacklength--;
	return topdata;
};