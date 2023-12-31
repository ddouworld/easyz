#pragma once
#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H
#include <stdarg.h>
#include<stdio.h>
#include<stdint.h>
typedef struct parser Parser;
typedef struct vm VM;
#define bool char
#define true 1
#define false 0
#define NOT_REACHED()\
   do {\
      fprintf(stderr, "NOT_REACHED: %s:%d In function %s()\n", \
	 __FILE__, __LINE__, __func__);\
      while (1);\
   } while (0);

#ifdef DEBUG
#define ASSERT(condition, errMsg) \
      do {\
	 if (!(condition)) {\
	    fprintf(stderr, "ASSERT failed! %s:%d In function %s(): %s\n", \
	       __FILE__, __LINE__, __func__, errMsg); \
	    abort();\
	 }\
      } while (0);
#else
#define ASSERT(condition, errMsg) ((void)0)
#endif
#endif
