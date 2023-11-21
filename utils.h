#pragma once
#ifndef _INCLUDE_UTILS_H
#define _INCLUDE_UTILS_H
#include "common.h"
typedef struct {
    char* str;
    uint32_t length;
} String;

typedef struct {
    uint32_t length; //������'\0'֮����ַ�����
    char start[0];  //����c99�е���������
} CharValue;  //�ַ���������

//����buffer����
#define DECLARE_BUFFER_TYPE(type)\
   typedef struct {\
      /* ���ݻ����� */    \
      type* datas;\
      /*����������ʹ�õ�Ԫ�ظ���*/\
      uint32_t count;\
      /*������������*/\
      uint32_t capacity;\
   } type##Buffer;\
   void type##BufferInit(type##Buffer* buf);\
   void type##BufferFillWrite(VM* vm, \
	 type##Buffer* buf, type data, uint32_t fillCount);\
   void type##BufferAdd(VM* vm, type##Buffer* buf, type data);\
   void type##BufferClear(VM* vm, type##Buffer* buf);

//����buffer����
#define DEFINE_BUFFER_METHOD(type)\
   void type##BufferInit(type##Buffer* buf) {\
      buf->datas = NULL;\
      buf->count = buf->capacity = 0;\
   }\
\
   void type##BufferFillWrite(VM* vm, \
	 type##Buffer* buf, type data, uint32_t fillCount) {\
      uint32_t newCounts = buf->count + fillCount;\
      if (newCounts > buf->capacity) {\
	 size_t oldSize = buf->capacity * sizeof(type);\
	 buf->capacity = ceilToPowerOf2(newCounts);\
	 size_t newSize = buf->capacity * sizeof(type);\
	 ASSERT(newSize > oldSize, "faint...memory allocate!");\
	 buf->datas = (type*)memManager(vm, buf->datas, oldSize, newSize);\
      }\
      uint32_t cnt = 0;\
      while (cnt < fillCount) {\
	 buf->datas[buf->count++] = data;\
	 cnt++;\
      }\
   }\
\
   void type##BufferAdd(VM* vm, type##Buffer* buf, type data) {\
      type##BufferFillWrite(vm, buf, data, 1);\
   }\
\
   void type##BufferClear(VM* vm, type##Buffer* buf) {\
      size_t oldSize = buf->capacity * sizeof(buf->datas[0]);\
      memManager(vm, buf->datas, oldSize, 0);\
      type##BufferInit(buf);\
   }

typedef struct {
    String* datas; uint32_t count; uint32_t capacity;
} StringBuffer; void StringBufferInit(StringBuffer* buf); void StringBufferFillWrite(VM* vm, StringBuffer* buf, String data, uint32_t fillCount); void StringBufferAdd(VM* vm, StringBuffer* buf, String data); void StringBufferClear(VM* vm, StringBuffer* buf);
#define SymbolTable StringBuffer
typedef uint8_t Byte;
typedef char Char;
typedef int Int;
DECLARE_BUFFER_TYPE(Int)
DECLARE_BUFFER_TYPE(Char)
DECLARE_BUFFER_TYPE(Byte)
typedef enum {
	ERROR_IO,
	ERROR_MEM,
	ERROR_LEX,
	ERROR_COMPILE,
	ERROR_RUNTIME
}ErrorType;
void print_error(void* parser,
    ErrorType errorType, const char* fmt, ...);
#define IO_ERROR(...)\
   print_error(NULL, ERROR_IO, __VA_ARGS__)

#define MEM_ERROR(...)\
   print_error(NULL, ERROR_MEM, __VA_ARGS__)

#define LEX_ERROR(parser, ...)\
   print_error(parser, ERROR_LEX, __VA_ARGS__)

#define COMPILE_ERROR(parser, ...)\
   print_error(parser, ERROR_COMPILE, __VA_ARGS__)

#define RUN_ERROR(...)\
  print_error(NULL, ERROR_RUNTIME, __VA_ARGS__)

#define DEFAULT_BUfFER_SIZE 512

#endif
