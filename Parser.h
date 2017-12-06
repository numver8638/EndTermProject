#pragma once

#include "Expression.h"
#include "Lexer.h"

ExpressionRef ParseExpression(LexerRef lexer);
void FreeExpression(ExpressionRef expr);