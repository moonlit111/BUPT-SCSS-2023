
#include "semantics.h"


void VariableNoDefinition(int lineNum, const std::string &name) {
    printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", lineNum, name.c_str());
}

void FunctionNoDefinition(int lineNum, const std::string &name) {
    printf("Error type 2 at Line %d: Function \"%s\" is invoked without definition.\n", lineNum, name.c_str());
}

void VariableRedefined(int lineNum, const std::string &name) {
    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", lineNum, name.c_str());
}

void FunctionRedefined(int lineNum, const std::string &name) {
    printf("Error type 4 at Line %d: Redefined function \"%s\".\n", lineNum, name.c_str());
}

void MisMatchTypeBothSide(int lineNum) {
    printf("Error type 5 at Line %d: Type mismatched for assignment.\n", lineNum);
}

void RightValueLeftSetError(int lineNum) {
    printf("Error type 6 at Line %d: rvalue on the left side of assignment operator.\n", lineNum);
}

void BinaryOperatorNotNumber(int lineNum) {
    printf("Error type 7 at Line %d: Type mismatched for operands.\n", lineNum);
}

void ReturnMisMatchType(int lineNum) {
    printf("Error type 8 at Line %d: The return type mismatched.\n", lineNum);
}

void InvalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually) {
    (void)expect;
    (void)actually;
    printf("Error type 9 at Line %d: Unmatched argument type for Function \"%s\".\n", lineNum, name.c_str());
}


void InvalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually) {
    (void)expect;
    (void)actually;
    printf("Error type 9 at Line %d: Unmatched argument type for Function \"%s\".\n", lineNum, name.c_str());
}

void IndexOnNonArray(int lineNum) {
    printf("Error type 10 at Line %d: Indexing operator applied to non-array variable.\n", lineNum);
}

void InvokeNonFunctionVariable(int lineNum, const std::string &name) {
	    printf("Error type 11 at Line %d: \"%s\" is not a function name.\n", lineNum, name.c_str());
}

void NotIntegerTypeIndexing(int lineNum) {
	    printf("Error type 12 at Line %d: Array index is not an integer.\n", lineNum);
}

void NotStructFVariable(int lineNum) {
	    printf("Error type 13 at Line %d: Illegal member access on non-structure variable.\n", lineNum);
}

void NoSuchMember(int lineNum, const std::string &name) {
	    printf("Error type 14 at Line %d: Structure has no member named \"%s\".\n", lineNum, name.c_str());
}


void StructRedefined(int lineNum, const std::string &name) {
    printf("Error type 15 at Line %d: Redefined structure \"%s\".\n", lineNum, name.c_str());
}

void StructNoDefinition(int lineNum, const std::string &name) {
    printf("Error type 16 at Line %d: Undefined structure \"%s\".\n", lineNum, name.c_str());
}
