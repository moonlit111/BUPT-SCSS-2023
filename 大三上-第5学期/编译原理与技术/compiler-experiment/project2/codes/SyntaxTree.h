#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H


#include <string>
#include <unordered_map>
#include <vector>
#include "type.h"
#include "node.h"

using std::string;
using std::unordered_map;
using std::vector;
extern unordered_map<string, Type *> symbolTable;

// Scope management
void EnterScope();
void ExitScope();
Type* LookupSymbol(const string& name);
void InsertSymbol(const string& name, Type* type, bool checkRedefinition = true);
bool IsInCurrentScope(const string& name);

void IdToExp(Node *exp, Node *id);

void DefVisit(Node *node);

void ExtDefVisit_SES(Node *node);

void ExtDefVisit_SS(Node *node);

void ExtDefVisit_SFC(Node *node);

void Specifier_FunDec_Recv_SF(Node *node);

void ExpVisit(Node *node);

void GetBoolOperatorType(Node *expOut, Node *expIn1, Node *expIn2);

void GetAlrthOperatorType(Node *expOut, Node *expIn1, Node *expIn2);

void CheckTypeMatch(Node *left, Node *right, int lineNum);

void CheckReturnValueMatchDeclaredType(Node *extDefSfc);

void DefStructTypeVisit(Node *node);

void DefPureTypeVisit(Node *node);

string GetStrValueFromDecList(Node *node);

void DefStructDefinition(Node *node);

void DefStructObjectDefinition(Node *node);

FieldList *GetFiledListFromDefList(Node *node);

void CheckRvalueInLeftSide(Node *node);

void CheckIdExists(Node *node, int lineNum);

void FunDecVisit(Node *funDec);

void CheckNoSuchMember(Node *node);

void SearchAndPutTypeOfDot(Node *expOut, Node *expIn, Node *ID);

void CheckInvokeExist(Node *node, int lineNum);

void GetReturnTypeOfFunction(Node *expOut, Node *ID);

void CheckFunctionParams(Node *ID, Node *args, int lineNum);

void CheckArrayExists(Node *Exp);

void GetArrayType(Node *expOut, Node *expIn, Node *Integer);

Node_TYPE CheckAlrthOperatorType(Node *exp);

void ExtDefVisit_SES_PureType(Node *node);

void ExtDefVisit_SES_StructType(Node *node);

Array *GetArrayFromVarDec(Node *node, Type *type);

void CheckTypeMatchType(Type *leftType, Type *rightType, int lineNum, const std::function<void(int)> &func);

void CheckReturnValueFromStmtList(Type *type, Node *stmtList);

void CheckReturnValueFromStmt(Type *type, Node *stmt);

void CheckReturnValueFromCompStmt(Type *type, Node *compStmt);

void GetNamesOfDefList(Node *node, vector<Node *> &namesofFileds);

#endif
