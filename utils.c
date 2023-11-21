
#include "utils.h"
#include "vm.h"
#include "parser.h"
#include <stdlib.h>
#include <stdarg.h>

//�ڴ�������ֹ���:
//   1 �����ڴ�
//   2 �޸Ŀռ��С
//   3 �ͷ��ڴ�
void* memManager(VM* vm, void* ptr, uint32_t oldSize, uint32_t newSize) {
	//�ۼ�ϵͳ��������ڴ�
	vm->allocatedBytes += newSize - oldSize;

	//����realloc(NULL, 0)������µ�ַ,�˵�ַ���ܱ��ͷ�
	if (newSize == 0) {
		free(ptr);
		return NULL;
	}

	return realloc(ptr, newSize);
}

// �ҳ����ڵ���v�����2����
uint32_t ceilToPowerOf2(uint32_t v) {
	v += (v == 0);  //�޸���v����0ʱ���Ϊ0�ı߽����
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
DEFINE_BUFFER_METHOD(String)
DEFINE_BUFFER_METHOD(Int)
DEFINE_BUFFER_METHOD(Char)
DEFINE_BUFFER_METHOD(Byte)

void print_error(void* parser, ErrorType errortype, const char* fmt, ...) {
	char buffer[DEFAULT_BUfFER_SIZE] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buffer, DEFAULT_BUfFER_SIZE, fmt, ap);
	va_end(ap);
	switch (errortype) {
	case ERROR_IO:
	case ERROR_MEM:
		fprintf(stderr, "%s:%d In function %s():%s\n",
			__FILE__, __LINE__, __func__, buffer);
		break;
	case ERROR_LEX:
	case ERROR_COMPILE:
		ASSERT(parser != NULL, "parser is null");
		//fprintf(stderr, "%s:%d \"%s\"\n", ((Parser*)parser)->file, ((Parser*)parser)->preToken.lineNo, buffer);
		break;
	case ERROR_RUNTIME:
		fprintf(stderr, "%s\n", buffer);
		break;
	default:
		NOT_REACHED();
	}
	exit(1);
}
