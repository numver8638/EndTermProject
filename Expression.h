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

#include <stdbool.h>

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
