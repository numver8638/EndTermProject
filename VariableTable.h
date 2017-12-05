#pragma once

#include <stdbool.h>

void InitializeVariableTable();
bool HasVariable(const char* id);
double GetVariable(const char* id);
void SetVariable(const char* id, double value);
void FreeVariableTable();
void DumpVariableTable();