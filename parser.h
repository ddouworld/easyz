#pragma once
#ifndef _PARSER_PARSER_H
#define _PARSER_PARSER_H
#include"common.h"
typedef enum {
	TOKEN_UNKNOWN,
	// ��������
	TOKEN_NUM,		   //����
	TOKEN_STRING,     	   //�ַ���
	TOKEN_ID,	     	   //������ 
	TOKEN_INTERPOLATION,     //��Ƕ���ʽ

	// �ؼ���(ϵͳ������)
	TOKEN_VAR,		   //'var'
	TOKEN_FUN,		   //'fun'
	TOKEN_IF,		   //'if'
	TOKEN_ELSE,	     	   //'else'	
	TOKEN_TRUE,	     	   //'true'
	TOKEN_FALSE,	     	   //'false'
	TOKEN_WHILE,	     	   //'while'
	TOKEN_FOR,	     	   //'for'
	TOKEN_BREAK,	     	   //'break'
	TOKEN_CONTINUE,         //'continue'
	TOKEN_RETURN,     	   //'return'
	TOKEN_NULL,	     	   //'null'

	//�����ǹ������ģ�鵼���token
	TOKEN_CLASS,	     	   //'class'
	TOKEN_THIS,	     	   //'this'
	TOKEN_STATIC,     	   //'static'
	TOKEN_IS,		   // 'is'
	TOKEN_SUPER,	     	   //'super'
	TOKEN_IMPORT,     	   //'import'
	TOKEN_FROM,         //from
	//�ָ���
	TOKEN_COMMA,		   //','
	TOKEN_COLON,		   //':'
	TOKEN_LEFT_PAREN,	   //'('
	TOKEN_RIGHT_PAREN,	   //')'
	TOKEN_LEFT_BRACKET,	   //'['
	TOKEN_RIGHT_BRACKET,	   //']'
	TOKEN_LEFT_BRACE,	   //'{'
	TOKEN_RIGHT_BRACE,	   //'}'
	TOKEN_DOT,		   //'.'
	TOKEN_DOT_DOT,	   //'..'

	//��˫Ŀ�����
	TOKEN_ADD,		   //'+'
	TOKEN_SUB,		   //'-'
	TOKEN_MUL,		   //'*' 
	TOKEN_DIV,		   //'/' 
	TOKEN_MOD,		   //'%'

	//��ֵ�����
	TOKEN_ASSIGN,	   //'='

	// λ�����
	TOKEN_BIT_AND,	   //'&'
	TOKEN_BIT_OR,	   //'|'
	TOKEN_BIT_NOT,	   //'~'
	TOKEN_BIT_SHIFT_RIGHT,  //'>>'
	TOKEN_BIT_SHIFT_LEFT,   //'<<'

	// �߼������
	TOKEN_LOGIC_AND,	   //'&&'
	TOKEN_LOGIC_OR,	   //'||'
	TOKEN_LOGIC_NOT,	   //'!'

	//��ϵ������
	TOKEN_EQUAL,		   //'=='
	TOKEN_NOT_EQUAL,	   //'!='
	TOKEN_GREATE,	   //'>'
	TOKEN_GREATE_EQUAL,	   //'>='
	TOKEN_LESS,		   //'<'
	TOKEN_LESS_EQUAL,	   //'<='
	
	TOKEN_QUESTION,	   //'?'

	//�ļ��������,���ʷ�����ʱʹ��
	TOKEN_EOF		   //'EOF'
}TokenType;
typedef struct {
	TokenType type;
	const char* start;
	uint32_t length;
	uint32_t lineNo;
}Token;
struct parser
{
	const char* file;
	const char* sourceCode;
	const char* nextCharPtr;
	char curChar;
	Token curToken;
	Token preToken;
	int interpolationExpectRightParenNum;
	struct parser* parent;  //ָ��parser
	VM* vm;
};
#define PEEK_TOKEN(parserPtr) parserPtr->curToken.type

char lookAheadChar(Parser* parser);
void getNextToken(Parser* parser);
bool matchToken(Parser* parser, TokenType expected);
void consumeCurToken(Parser* parser, TokenType expected, const char* errMsg);
void consumeNextToken(Parser* parser, TokenType expected, const char* errMsg);
uint32_t getByteNumOfEncodeUtf8(int value);
uint8_t encodeUtf8(uint8_t* buf, int value);
void initParser(VM* vm, Parser* parser, const char* file, const char* sourceCode);
#endif

