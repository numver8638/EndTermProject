// MIT License

// Copyright (c) 2017 Jinhwan Shin(신진환)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
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