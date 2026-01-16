#ifndef SEMANTICERROR_H
#define SEMANTICERROR_H
#include <string>
#include <unordered_map>

void VariableNoDefinition(int lineNum, const std::string &name);// error 1
void FunctionNoDefinition(int lineNum, const std::string &name);// error 2
void VariableRedefined(int lineNum, const std::string &name);// error 3
void FunctionRedefined(int lineNum, const std::string &name);// error 4
void MisMatchTypeBothSide(int lineNum);// error 5
void RightValueLeftSetError(int lineNum);// error 6
void BinaryOperatorNotNumber(int lineNum);// error 7
void ReturnMisMatchType(int lineNum);// error 8
// error 9
void InvalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually);
void InvalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually);
void IndexOnNonArray(int lineNum);// error 10
void InvokeNonFunctionVariable(int lineNum, const std::string &name);//error 11
void NotIntegerTypeIndexing(int lineNum);// error 12
void NotStructFVariable(int lineNum);// error 13
void NoSuchMember(int lineNum, const std::string &name);// error 14
void StructRedefined(int lineNum, const std::string &name);// error 15
void StructNoDefinition(int lineNum, const std::string &name);// error 16
#endif 
