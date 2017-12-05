#pragma once

// 단어 분석기가 반환하는 단어의 종류
#define LEX_ERROR      (-1)  // 오류
#define LEX_END        (0)   // 끝
#define LEX_VALUE      (1)   // 값(숫자)
#define LEX_ID         (2)   // 값(변수)
#define LEX_LEFTPAREN  (3)   // 왼쪽 소괄호 '('
#define LEX_RIGHTPAREN (4)   // 오른쪽 소괄호 ')'
#define LEX_PLUS       (5)   // 더하기 '+'
#define LEX_MINUS      (6)   // 빼기 '-'
#define LEX_MULTIPLY   (7)   // 곱하기 '*'
#define LEX_DIVIDE     (8)   // 나누기 '/'
#define LEX_POWER      (9)   // 제곱 '^'
#define LEX_ASSIGN     (10)  // 대입 '='

typedef struct {
	char*  Buffer;
	int    Type;
	char   Image[64];
	double Value;
} Lexer, *LexerRef;

LexerRef CreateLexer(char* string);
int Lex(LexerRef self);
void FreeLexer(LexerRef);