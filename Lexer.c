#include "Lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL(ch) ('0' <= ch && ch <= '9') // 문자가 숫자인가?
#define ALPHABET(ch) isalpha(ch)             // 문자가 알파벳인가?

/*
 * LexerRef CreateLexer(char* string)
 * - 단어 분석기 생성
 * - 입력값:
 *   - string: 문자열(수식)
 * - 반환값: 단어 분석기 상태값
 */
LexerRef CreateLexer(char* string) {
      LexerRef lexer = malloc(sizeof(Lexer));

      memset(lexer, 0, sizeof(Lexer));
      lexer->Buffer = string;

      return lexer;
}

/*
 * int Lex(LexerRef self)
 * - 단어 분석 함수
 * - 입력값:
 *   - self: 단어 분석기 상태 변수
 * - 출력값: 분석 완료된 단어의 타입
 */
int Lex(LexerRef self) {
    // 상태 초기화
    self->Type = LEX_ERROR;
    self->Value = 0;
    self->Image[0] = 0;

    // 공백 문자 스킵(스페이스바, 탭)
    while (*(self->Buffer) == ' ' || *(self->Buffer) == '\t') (self->Buffer)++;

    // 문자열의 끝(NULL)이면...
    if (*(self->Buffer) == 0) {
        // 분석 끝. 더이상 진행 안 함.
        self->Type = LEX_END;
        return LEX_END;   
    }

    // 현재 문자 저장
    char ch = *(self->Buffer);

    // 문자가 숫자이면...
    if (DECIMAL(ch)) {
        char* end = NULL;
        double d = strtod(self->Buffer, &end); // strtod: 문자열을 실수로 변환하는 함수.
                                               // end변수로 실수문자열의 끝을 가리키는 포인터가 저장됨

        self->Value = d;
        self->Buffer = end; // 숫자 다음 문자를 가리키도록 end변수 저장.

        self->Type = LEX_VALUE; // 숫자 타입
        return LEX_VALUE;
    }

    // 문자가 알파벳이면...
    if (ALPHABET(ch)) {
        char* start = self->Buffer; // 문자의 시작점 저장

        do {
            ++(self->Buffer); // 다음 문자...
        } while (ALPHABET(*(self->Buffer))); // 문자가 알파벳일동안...

        int length = (self->Buffer) - start; // 끝 - 시작 = 길이

        // 변수의 최대 길이: 63 + 1(NULL)
        if (length > 63) {
            printf("warning: variable name is too long. maximum length of variable is 63 characters.\n");
            length = 63;
        }

        // 문자열 길이만큼만 복사.
        strncpy(self->Image, start, length);
        self->Image[length] = '\0'; // 문자열 끝문자 지정.

        self->Type = LEX_ID; // 변수 타입
        return LEX_ID;
    }

    // 이도 저도 아니면 기호.
    // 다음 문자를 가리키도록 포인터 증가.
    (self->Buffer)++;
    
    switch (ch) {
        case '(':
            self->Type = LEX_LEFTPAREN;
            break;

        case ')':
            self->Type = LEX_RIGHTPAREN;
            break;

        case '+':
            self->Type = LEX_PLUS;
            break;

        case '-':
            self->Type = LEX_MINUS;
            break;

        case '*':
            self->Type = LEX_MULTIPLY;
            break;

        case '/':
            self->Type = LEX_DIVIDE;
            break;

        case '^':
            self->Type = LEX_POWER;
            break;

        case '=':
            self->Type = LEX_ASSIGN;
            break;

        default: // 정의 되지 않은 문자는 오류.
            self->Type = LEX_ERROR;
            break;
    }
    
    // 구조체 안 Type변수에 저장된 값을 반환함.
    return self->Type;
}

/*
 * void FreeLexer(LexerRef self)
 * - 단어 분석기 메모리 해제 함수
 * - 입력값:
 *   - self: 단어 분석기 상태 변수
 */
void FreeLexer(LexerRef self) {
    free(self);
}