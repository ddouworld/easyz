#ifndef _VM_VM_H
#define _VM_VM_H
#include "common.h"

struct vm {
	uint32_t allocatedBytes;  //�ۼ��ѷ�����ڴ���
	Parser* curParser;  //��ǰ�ʷ�������
};

void initVM(VM* vm);
VM* newVM(void);
#endif
