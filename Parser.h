#pragma once

#include <stdbool.h>

#include "Lexer.h"

// 수식 타입
enum ExpressionType {
	Expr_Error, // 에러
	Expr_Op,    // 수식
	Expr_Value, // 숫자
    Expr_Var,   // 변수
    Expr_Assign // 대입식
};

typedef struct _Expr Expression, *ExpressionRef;

// 수식의 항을 저장하는 구조체.
struct _Expr {
    enum ExpressionType Type; // 수식 타입

    bool Negate; // 부호 반전
    
    union {
        struct {
            const char* ErrorMsg;
            ExpressionRef Left, Right;
        } Error; // 오류식 - 오류를 나타냄

        struct {
            const char* ID;
            ExpressionRef Expr;
        } Assign; // 대입식

        struct {
            const char* ID;
        } Variable; // 변수

        struct {
            double Value;
        } Value; // 값

		struct {
            ExpressionRef Left, Right; // 연산자 기준 좌항, 우항
            int Opcode; // 실행되어야될 연산
        } Operation; // 식
	} Value;
};

ExpressionRef ParseExpression(LexerRef lexer);
void FreeExpression(ExpressionRef expr);