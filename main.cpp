#include <iostream>
#include "AcycSinglyLinkList.h"
//int main() {
//	ASL_List testli({3,5,1,9,6,8,10,4,2,7,6,5,5,8,9});
//	std::cout << "��ʼ������Ϊ��\n";
//	testli.ListShow();
//	int x = 5;
//	std::cout << "x=" << x<<"\n";
//	ASL_List ansli(&testli);
//	int i=1;
//	int deleem = 0;
//	for (auto ptr_test = testli.begin(); ptr_test != testli.end();ptr_test++,i++) {
//		if (*ptr_test < x) {
//			ansli.ListDelete(i, &deleem);
//			ansli.ListInsert(1, deleem);
//		}
//	}
//	if (*testli.end()<x) {
//		ansli.ListDelete(i, &deleem);
//		ansli.ListInsert(1, deleem);
//	}
//	std::cout << "������Ϊ��\n";
//	ansli.ListShow();
//	return 0;
//}


int main() {
	ASL_List testlist({1,2,3,2,1});
	std::cout << "�Ƿ�Ϊ��������\n";
	std::cout << "������Ե������ǣ�\n";
	testlist.ListShow();
	std::cout << "\n���Խ��Ϊ��";
	int listlen=testlist.ListLength(),step,i=0;
	step = listlen / 2;
	auto ptr_1 = testlist.begin();
	auto ptr_2 = testlist.begin();
	while (step--) {
		if (*ptr_1 != ptr_2[listlen - i]) {
			std::cout << "false";
			return 0;;
		}
			ptr_1++; i++;
	}
	std::cout << "true";
	return 0;
}