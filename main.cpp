#include <iostream>
#include "SqList.h"
int main() {
	SqList me;
	me.ListInsert(1, 520);
	std::cout << me.GetLength();
	return 0;
}