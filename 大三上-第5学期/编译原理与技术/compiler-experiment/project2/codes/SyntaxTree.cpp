#include <iterator>
#include <stack>
#include <unordered_set>
#include "SyntaxTree.h"
#include "semantics.h"


static unordered_map<string, Node_TYPE> snt = {
        {string("int"),   Node_TYPE::INT},
        {string("float"), Node_TYPE::FLOAT},
        {string("char"),  Node_TYPE::CHAR},
};
static unordered_map<Node_TYPE, string> tns = {
        {Node_TYPE::INT,   string("INT")},
        {Node_TYPE::FLOAT, string("FLOAT")},
        {Node_TYPE::CHAR,  string("CHAR")},
};

// Scope management
// scopeStack: each scope maps identifier -> previous Type* for that name before this scope.
// This lets us correctly restore outer bindings (for shadowing) when exiting a scope.
static vector<unordered_map<string, Type*>> scopeStack;

// Track function names that have been redefined so we can skip
// return-type checking for their bodies (matches r04 expectation).
static std::unordered_set<std::string> redefinedFunctions;

void EnterScope() {
    scopeStack.push_back(unordered_map<string, Type*>());
}

void ExitScope() {
    if (!scopeStack.empty()) {
	    // Restore previous bindings for all symbols defined in this scope.
	    // For each name recorded in this scope, the stored Type* is the
	    // previous binding (from an outer scope) or nullptr if there was none.
	    for (const auto &pair : scopeStack.back()) {
	        const string &name = pair.first;
	        Type *previous = pair.second;
	        if (previous != nullptr) {
	            // Shadowed an outer-scope symbol: restore it.
	            symbolTable[name] = previous;
	        } else {
	            // Defined only in this scope: remove it completely.
	            symbolTable.erase(name);
	        }
	    }
	    scopeStack.pop_back();
    }
}

Type* LookupSymbol(const string& name) {
    if (symbolTable.count(name) > 0) {
        return symbolTable[name];
    }
    return nullptr;
}

void InsertSymbol(const string& name, Type* type, bool checkRedefinition) {
    if (checkRedefinition && !scopeStack.empty()) {
        // Check if already defined in current scope
        if (scopeStack.back().count(name) > 0) {
            // Already defined in current scope, this is an error
            return; // Error will be reported by caller
        }
    }

	// Record previous binding in current scope (for shadowing restoration).
	if (!scopeStack.empty()) {
	    auto &currentScope = scopeStack.back();
	    // Only save the previous binding the first time this name appears
	    // in the current scope.
	    if (currentScope.count(name) == 0) {
	        Type *previous = nullptr;
	        if (symbolTable.count(name) > 0) {
	            previous = symbolTable[name];
	        }
	        currentScope[name] = previous;
	    }
	}

	// Always update the global symbol table to the new binding.
	symbolTable[name] = type;
}

bool IsInCurrentScope(const string& name) {
    if (scopeStack.empty()) {
        return symbolTable.count(name) > 0;
    }
    return scopeStack.back().count(name) > 0;
}

auto GetArrayDemensionAndType(Type *_type) {
    vector<int> demensions;
    Type *tempField = _type;
    while (tempField != nullptr && tempField->type.index() == ARRAY_POINTER_VALUE) {
        auto tempArray = std::get<Array *>(tempField->type);
        tempField = tempArray->base;
        demensions.push_back(tempArray->size);
    }
    return std::tuple(demensions, tempField);
};

string CategoryAndTypeNameFromType(Type *type) {
    static const unordered_map<CATEGORY, string> ca_st = {
            {CATEGORY::PRIMITIVE, ""},
            {CATEGORY::ARRAY,     "array"},
            {CATEGORY::STRUCTURE, "struct"},
            {CATEGORY::FUNCTION,  "function"}
    };
    const string &categoryStr = ca_st.at(type->category);
    string typeName;
    switch (type->category) {
        case CATEGORY::PRIMITIVE: {
            typeName = tns[std::get<Node_TYPE>(type->type)];
            break;
        }
        case CATEGORY::ARRAY:
        case CATEGORY::STRUCTURE:
        case CATEGORY::FUNCTION: {
            typeName = symbolTable[type->name]->name;
            break;
        }
    }
    return string("").append(categoryStr).append(" ").append(typeName);
}

void IdToExp(Node *exp, Node *id) {
    if (exp->name != "Exp" || id->name != "ID") {
        return;
    }
    string idName = std::get<string>(id->value);
    if (symbolTable.count(idName) == 0) {
        // Variable not defined, already reported error in CheckIdExists
        exp->type = Type::GetPrimitiveERROR();
    } else {
        exp->type = symbolTable[idName];
    }
}


void DefVisit(Node *node) {
    if (node->get_nodes(0, 0)->nodes.empty()) {
        DefPureTypeVisit(node);
    } else {
        DefStructTypeVisit(node);
    }
}

string GetStrValueFromVarDec(Node *varDec) {
    while (varDec->name == "VarDec") {
        varDec = varDec->get_nodes(0);
    }
    return std::get<string>(varDec->value);
}


string GetStrValueFromDecList(Node * node) {
    if (node->name == "DecList") {
        Node *VarDec = node->get_nodes(0, 0);
        return GetStrValueFromVarDec(VarDec);
    } else {
        std::cerr << "Input Node Wrong\n";
        return "";
    }
}

string GetStrValueFromExtDecList(Node *node) {
    if (node->name == "ExtDecList") {
        Node *VarDec = node->get_nodes(0);
        return GetStrValueFromVarDec(VarDec);
    } else {
        std::cerr << "Input Node Wrong\n";
        return "";
    }
}

void DefPureTypeVisit(Node *node) {
    Node *decList = node->get_nodes(1);
    string name = GetStrValueFromDecList(decList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        // Check if already defined in current scope
        if (IsInCurrentScope(name)) {
            VariableRedefined(std::get<int>(node->value), name);
        }
        const auto &PrimitiveType = Type::GetPrimitiveType(_type);
        if (decList->get_nodes(0, 0)->nodes.size() == 1) {
            InsertSymbol(name, PrimitiveType, false);
            if (decList->get_nodes(0)->nodes.size() == 3) {
                CheckTypeMatchType(symbolTable[std::get<string>(decList->get_nodes(0, 0, 0)->value)],
                                   decList->get_nodes(0, 2)->type, std::get<int>(node->value), MisMatchTypeBothSide);
            }
        } else {
            InsertSymbol(name, new Type(name, CATEGORY::ARRAY,
                                         GetArrayFromVarDec(decList->get_nodes(0, 0), PrimitiveType)), false);
            if (decList->get_nodes(0)->nodes.size() == 3) {
                MisMatchTypeBothSide(std::get<int>(decList->value));
            }
        }
        if (decList->nodes.size() == 1) {
            break;
        }
        decList = decList->get_nodes(2);
        name = GetStrValueFromDecList(decList);
    } while (true);
}

void DefStructTypeVisit(Node *node) {
    Node *decList = node->get_nodes(1);
    string variableName = GetStrValueFromDecList(decList);
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    if (symbolTable.count(structName) == 0) {
        StructNoDefinition(std::get<int>(node->value),structName);
    } else {
        do {
            // Check if already defined in current scope
            if (IsInCurrentScope(variableName)) {
                VariableRedefined(std::get<int>(node->value), variableName);
            }
            if (decList->get_nodes(0, 0)->nodes.size() == 1) {
                InsertSymbol(variableName, symbolTable[structName], false);
            } else {
                InsertSymbol(variableName, new Type(variableName, CATEGORY::ARRAY,
                                                     GetArrayFromVarDec(decList->get_nodes(0, 0),
                                                                        symbolTable[structName])), false);
            }
            if (decList->get_nodes(0)->nodes.size() == 3) {
                CheckTypeMatchType(symbolTable[variableName], decList->get_nodes(0, 2)->type,
                                   std::get<int>(decList->value),
                                   MisMatchTypeBothSide);
            }
            if (decList->nodes.size() == 1) {
                return;
            }
            decList = decList->get_nodes(2);
            variableName = GetStrValueFromDecList(decList);
        } while (true);
    }
}

Array *GetArrayFromVarDec(Node *node, Type *type) {
    if (node == nullptr || node->name != "VarDec") {
        return nullptr;
    } else {
        int size = std::get<int>(node->get_nodes(2)->value);
#ifdef DEBUG
        node->print();
#endif
        if (node->get_nodes(0)->nodes.size() == 1) {
            return new Array(type, size);
        } else {
            return new Array(new Type("", CATEGORY::ARRAY,
                                      GetArrayFromVarDec(node->get_nodes(0),
                                                         type)), size);
        }
    }
}


void ExtDefVisit_SES(Node *node) {
    if (node->get_nodes(0, 0)->nodes.empty()) {
        ExtDefVisit_SES_PureType(node);
    } else {
        ExtDefVisit_SES_StructType(node);
    }
#ifdef DEBUG
    node->print(0);
#endif
}

void ExtDefVisit_SES_PureType(Node *node) {
    Node *extDecList = node->get_nodes(1);
    string name = GetStrValueFromExtDecList(extDecList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        if (symbolTable.count(name) != 0) {
            VariableRedefined(std::get<int>(node->value), name);
        }
        const auto &PrimitiveType = Type::GetPrimitiveType(_type);
        if (extDecList->get_nodes(0, 0)->nodes.empty()) {
            symbolTable[name] = PrimitiveType;
        } else {
            symbolTable[name] = new Type(name, CATEGORY::ARRAY,
                                         GetArrayFromVarDec(extDecList->get_nodes(0),
                                                            PrimitiveType));
        }
        if (extDecList->nodes.size() == 1) {
            break;
        }
        extDecList = extDecList->get_nodes(2);
        name = GetStrValueFromExtDecList(extDecList);
    } while (true);
}

void ExtDefVisit_SES_StructType(Node *node) {
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    Node *extDefList = node->get_nodes(1);
    string variableName = GetStrValueFromExtDecList(extDefList);
    ExtDefVisit_SS(node);
    if (symbolTable.count(structName) == 0) {
        StructNoDefinition(std::get<int>(node->value),structName);
    } else {
        do {
            if (symbolTable.count(variableName) != 0) {
                VariableRedefined(std::get<int>(node->value), variableName);
            }
            if (extDefList->get_nodes(0)->nodes.size() == 1) {
                symbolTable[variableName] = symbolTable[structName];
            } else {
                symbolTable[variableName] = new Type(variableName, CATEGORY::ARRAY,
                                                     GetArrayFromVarDec(extDefList->get_nodes(0),
                                                                        symbolTable[structName]));
            }
            if (extDefList->nodes.size() == 1) {
                return;
            }
            extDefList = extDefList->get_nodes(2);
            variableName = GetStrValueFromExtDecList(extDefList);
        } while (true);
    }
}

FieldList *GetFiledListFromNodesVector(const vector<Node *> &vec) {
    if (vec.empty()) {
        return nullptr;
    }
    vector<FieldList *> fieldVec;
    for (const auto &item : vec) {
        const auto name = GetStrValueFromDecList(item);
        fieldVec.push_back(new FieldList{name, symbolTable[name], nullptr});
        symbolTable.erase(name);
    }
    for (auto i = static_cast<size_t>(0); i < vec.size() - 1; ++i) {
        fieldVec[i]->next = fieldVec[i + 1];
    }
    return fieldVec.front();
}

void ExtDefVisit_SS(Node *node) {
    if (node->get_nodes(0, 0)->name == "TYPE") {
        return;
    }
    string name = std::get<string>(node->get_nodes(0, 0, 1)->value);
    vector<Node *> namesofFileds;
    GetNamesOfDefList(node, namesofFileds);
    auto fieldListOfType = GetFiledListFromNodesVector(namesofFileds);
    if (symbolTable.count(name) != 0) {
        StructRedefined(std::get<int>(node->value), name);
    } else {
        symbolTable[name] = new Type{name, CATEGORY::STRUCTURE, fieldListOfType};
    }
#ifdef DEBUG
    node->print(0);
#endif
}

void GetNamesOfDefList(Node *node, vector<Node *> &namesofFileds) {
    if (!node->get_nodes(0, 0, 3)->nodes.empty()) {
        auto nodeofField = node->get_nodes(0, 0, 3);
        while (nodeofField != nullptr && !nodeofField->nodes.empty() && nodeofField->name == "DefList") {
            auto declistNode = nodeofField->get_nodes(0, 1);
            while (declistNode != nullptr && declistNode->name == "DecList") {
                namesofFileds.push_back(declistNode);
                if (declistNode->nodes.size() == 3) {
                    declistNode = declistNode->get_nodes(2);
                } else {
                    break;
                }
            }
            nodeofField = nodeofField->get_nodes(1);
        };
        std::for_each(std::cbegin(namesofFileds), std::cend(namesofFileds), [](auto ) {
        });
    }
}

Type *GetSpecifierType(Node *node) {
    if (node->name != "Specifier") {
        return nullptr;
    }
    if (node->get_nodes(0)->nodes.empty()) {
        const string &pureTypeName = std::get<string>(node->get_nodes(0)->value);
        return Type::GetPrimitiveType(snt[pureTypeName]);
    } else {
        return symbolTable[std::get<string>(node->get_nodes(0, 1)->value)];
    }
}

void Specifier_FunDec_Recv_SF(Node *node) {
    auto name = std::get<string>(node->get_nodes(1, 0)->value);
    Type *functionType = symbolTable[name];
    Node *specifier = node->get_nodes(0);
    auto specifierType = GetSpecifierType(specifier);

    // If function already has a return type, it's a redefinition
    // Don't modify the return type (keep the first definition)
    if (functionType->returnType == nullptr) {
        functionType->returnType = specifierType;
    }
}

void ExtDefVisit_SFC(Node *node) {
#ifdef DEBUG
    node->print(0);
#endif
	// If this function has been redefined, we follow the assignment requirement:
	// only report the redefinition error (type 4) and DO NOT perform return-type
	// checking on the redefined body (avoids extra type 8 errors in r04).
	string functionName = std::get<string>(node->get_nodes(1, 0)->value);
	if (redefinedFunctions.count(functionName) == 0) {
	    CheckReturnValueMatchDeclaredType(node);
	}
	// Exit scope for function parameters (CompSt already exited its own scope)
	ExitScope();
}

FieldList *GetFiledListFromDefList(Node *node) {
    if (node == nullptr || node->nodes.empty() || node->name != "DefList") {
        return nullptr;
    }
    string name = GetStrValueFromDecList(node->get_nodes(0, 1));
    return new FieldList(name, symbolTable[name], GetFiledListFromDefList(node->get_nodes(1)));
}


void CheckRvalueInLeftSide(Node *node) {
    if (node->name != "Exp") {
    }
    Node *leftExpNode = node->get_nodes(0);
    switch (leftExpNode->nodes.size()) {
        case 1: {
            if (leftExpNode->get_nodes(0)->name == "ID") { return; }
            break;
        }
        case 3: {
            if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "ID" &&
                leftExpNode->get_nodes(1)->name == "DOT") { return; }
            break;
        }
        case 4: {
            if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "Exp" &&
                leftExpNode->get_nodes(1)->name == "LB" && leftExpNode->get_nodes(3)->name == "RB") { return; }
            break;
        }
    }
    RightValueLeftSetError(std::get<int>(node->value));
}

void CheckIdExists(Node *node, int lineNum) {
    if (node->name != "ID") {
        return;
    }
    string idName = std::get<string>(node->value);
    if (symbolTable.count(idName) == 0) {
        VariableNoDefinition(lineNum, idName);
    }
}


void FunDecVisit(Node *funDec) {
    Type *functionType = new Type();
    functionType->category = CATEGORY::FUNCTION;
    functionType->name = std::get<string>(funDec->get_nodes(0)->value);
    bool isRedefined = false;
	    if (symbolTable.count(functionType->name) != 0) {
	        FunctionRedefined(std::get<int>(funDec->value), functionType->name);
	        isRedefined = true;
	        // Record this function name so we can skip return-type checking
	        // for its (redefined) body later.
	        redefinedFunctions.insert(functionType->name);
	        // Don't return, continue processing to avoid cascading errors
	    }

    // Enter scope for function parameters
    EnterScope();

    if (funDec->nodes.size() == 3) {
        functionType->type = static_cast<FieldList *>(nullptr);
    } else {
        Node *varList = funDec->get_nodes(2);
        do {
            Node *specifier = varList->get_nodes(0, 0);
            auto specifierType = GetSpecifierType(specifier);
            auto varDec = varList->get_nodes(0, 1);
            string paramName = GetStrValueFromVarDec(varDec);
            if (IsInCurrentScope(paramName)) {
                VariableRedefined(std::get<int>(varList->value), paramName);
            }
            if (varDec->nodes.size() == 1) {
                InsertSymbol(paramName, specifierType, false);
            } else {
                InsertSymbol(paramName, new Type(paramName, CATEGORY::ARRAY,
                                                  GetArrayFromVarDec(varDec, specifierType)), false);
            }
            if (varList->nodes.size() == 1) {
                break;
            }
            varList = varList->get_nodes(2);
        } while (true);
        varList = funDec->get_nodes(2);
        FieldList fieldList;
        fieldList.next = new FieldList();
        FieldList *fieldListPtr = fieldList.next;
        functionType->type = fieldList.next;
        do {
            string paramName = GetStrValueFromVarDec(varList->get_nodes(0, 1));
            fieldListPtr->name = paramName;
            fieldListPtr->type = symbolTable[paramName];
            if (varList->nodes.size() == 1) {
                break;
            }
            varList = varList->get_nodes(2);
            fieldListPtr->next = new FieldList();
            fieldListPtr = fieldListPtr->next;
        } while (true);
    }
    // Only update symbol table if not redefined
    if (!isRedefined) {
        symbolTable[functionType->name] = functionType;
    }
}

void CheckNoSuchMember(Node *node) {
    if (node->name != "Exp") {
        return;
    }
    if (node->get_nodes(0)->type == nullptr) {
        return;
    }
    // If already an error type, don't report cascading errors
    if (node->get_nodes(0)->type == Type::GetPrimitiveERROR()) {
        return;
    }
    if (node->get_nodes(0)->type->category != CATEGORY::STRUCTURE) {
        NotStructFVariable(std::get<int>(node->value));
    }
}

void SearchAndPutTypeOfDot(Node *expOut, Node *expIn, Node *ID) {
    if (expIn->type == nullptr) {
        NotStructFVariable(std::get<int>(expIn->value));
        expOut->type = Type::GetPrimitiveERROR();
        return;
    }
    if (expIn->type == Type::GetPrimitiveERROR()) {
        expOut->type = Type::GetPrimitiveERROR();
        return;
    }
    if (expIn->type->type.index() != FieldList_POINTER_VALUE) {
        expOut->type = Type::GetPrimitiveERROR();
        return;
    }
    FieldList *fieldList = std::get<FieldList *>(expIn->type->type);
    string idName = std::get<string>(ID->value);
    while (fieldList != nullptr) {
        if (fieldList->name == idName) {
            expOut->type = fieldList->type;
            return;
        }
        fieldList = fieldList->next;
    }
    NoSuchMember(std::get<int>(expOut->value), idName);
    expOut->type = Type::GetPrimitiveERROR();
}


void CheckInvokeExist(Node *node, int lineNum) {
    string functionName = std::get<string>(node->value);
    if (symbolTable.count(functionName) == 0) {
        FunctionNoDefinition(lineNum, functionName);
    } else if (symbolTable[functionName]->category != CATEGORY::FUNCTION) {
        InvokeNonFunctionVariable(lineNum, functionName);
    }
}

void GetReturnTypeOfFunction(Node *expOut, Node *ID) {
	    string functionName = std::get<string>(ID->value);
	    if (symbolTable.count(functionName) == 0) {
	        // Function not defined (type 2 already reported). Mark as no-type
	        // here so that we don't additionally trigger return-type
	        // mismatch purely because of this.
	        expOut->type = nullptr;
	        return;
	    }
	    Type *symbolType = symbolTable[functionName];
	    if (symbolType->category != CATEGORY::FUNCTION) {
	        // Invoking a non-function variable (type 11 already reported).
	        // Also mark as no-type to avoid cascading return-type mismatch
	        // errors (e.g., in r11 we only want the type 11 error).
	        expOut->type = nullptr;
	        return;
	    }
	    Type *returnType = symbolType->returnType;
	    expOut->type = returnType;
}

void CheckFunctionParams(Node *ID, Node *args, int lineNum) {
    string functionName = std::get<string>(ID->value);
    if (symbolTable.count(functionName) == 0 || symbolTable[functionName]->category != CATEGORY::FUNCTION) {
        return;
    }
    Type *functionType = symbolTable[functionName];
    FieldList *fieldList =
            functionType->type.index() == Node_TYPE_VALUE ? nullptr : std::get<FieldList *>(functionType->type);
    auto fieldListFunc = [](FieldList *_field) {
        int number = 0;
        while (_field != nullptr) {
            _field = _field->next;
            number++;
        }
        return number;
    };
    auto argsFunc = [](Node *Args_) {
        int number = 1;
        while (Args_->nodes.size() != 1) {
            Args_ = Args_->get_nodes(2);
            number++;
        }
        return number;
    };
    if (args == nullptr) {
        if (fieldList == nullptr) {
            return;
        } else {
            int except = fieldListFunc(fieldList);
            InvalidArgumentNumber(lineNum, functionName, except, 0);
        }
    } else if (fieldList == nullptr) {
        int actually = argsFunc(args);
        InvalidArgumentNumber(lineNum, functionName, 0, actually);
        return;
    } else {
        int except = fieldListFunc(fieldList);
        int actually = argsFunc(args);
        if (except != actually) {
            InvalidArgumentNumber(lineNum, functionName, except, actually);
            // Don't check argument types if number doesn't match
            return;
        }
        int count = 0;
        while (count < std::min(except, actually)) {
            count++;
            Type *paramType = fieldList->type;
            string argsName;
            if (args->get_nodes(0, 0)->value.index() != Node_TYPE_VALUE) {
                if (paramType->category != CATEGORY::PRIMITIVE ||
                    paramType != args->get_nodes(0)->type
                        ) {
                    InvalidArgumentType(lineNum, functionName, CategoryAndTypeNameFromType(paramType),
                                        tns[args->get_nodes(0, 0)->TYPE]);
                }
            } else {
                argsName = std::get<string>(args->get_nodes(0, 0)->value);
            }
            if (symbolTable.count(argsName) == 0) {
                continue;
            } else {
                Type *argsType = symbolTable[argsName];
                if (argsType->category == CATEGORY::FUNCTION) {
                    argsType = argsType->returnType;
                }
                auto errorOfinvalidArgumentType = [lineNum, functionName, paramType, argsType] {
                    InvalidArgumentType(lineNum, functionName, CategoryAndTypeNameFromType(paramType),
                                        CategoryAndTypeNameFromType(argsType));
                };
                if (paramType == nullptr || argsType == nullptr) {
                    errorOfinvalidArgumentType();
                } else if (paramType->category != argsType->category) {
                    errorOfinvalidArgumentType();
                } else if (paramType->category == CATEGORY::PRIMITIVE && paramType != argsType) {
                    errorOfinvalidArgumentType();
                } else if (paramType->category == CATEGORY::STRUCTURE && paramType->name != argsType->name) {
                    errorOfinvalidArgumentType();
                } else if (paramType->category == CATEGORY::ARRAY) {
                    vector<int> levelField, levelArgs;
                    Type *baseTypeOfField, *baseTypeOfArgs;
                    std::tie(levelField, baseTypeOfField) = GetArrayDemensionAndType(paramType);
                    std::tie(levelArgs, baseTypeOfArgs) = GetArrayDemensionAndType(argsType);
                    if (baseTypeOfField == nullptr || baseTypeOfArgs == nullptr) {
                        errorOfinvalidArgumentType();
                    } else if (levelField.size() != levelArgs.size() ||
                               std::equal(levelField.cbegin(), levelField.cend(), levelArgs.cbegin()) ||
                               baseTypeOfField->category != baseTypeOfArgs->category) {
                        errorOfinvalidArgumentType();
                    } else if (baseTypeOfField->category == CATEGORY::PRIMITIVE && baseTypeOfField != baseTypeOfArgs) {
                        errorOfinvalidArgumentType();
                    } else if (baseTypeOfField->category == CATEGORY::STRUCTURE &&
                               baseTypeOfArgs->name != baseTypeOfField->name) {
                        errorOfinvalidArgumentType();
                    }
                }
            }
            fieldList = fieldList->next;
            args = args->get_nodes(2);
        }
    }

}

void CheckArrayExists(Node *Exp) {
    if (Exp->nodes.size() == 1) {
        string arrayName = std::get<string>(Exp->get_nodes(0)->value);
        if (symbolTable.count(arrayName) != 0) {
            Type *arrayType = symbolTable[arrayName];
            // If already an error type, don't report cascading errors
            if (arrayType == Type::GetPrimitiveERROR()) {
                return;
            }
            if (arrayType->category != CATEGORY::ARRAY) {
                IndexOnNonArray(std::get<int>(Exp->value));
            }
        } else {
            IndexOnNonArray(std::get<int>(Exp->value));
        }
    } else {
        //
        Type *arrayType = Exp->type;
        // If already an error type, don't report cascading errors
        if (arrayType == Type::GetPrimitiveERROR()) {
            return;
        }
        if (arrayType == nullptr || arrayType->category != CATEGORY::ARRAY) {
            IndexOnNonArray(std::get<int>(Exp->value));
        }
    }
}

bool CheckIntegerType(Node *exp, const std::function<void(int)> &func) {
    // If already an error type, don't report cascading errors
    if (exp->type == Type::GetPrimitiveERROR()) {
        return false;
    }
    if (exp->type != Type::GetPrimitiveINT()) {
        func(std::get<int>(exp->value));
        return false;
    }
    return true;
}

bool CheckIntegerExp(Node *exp) {
    return CheckIntegerType(exp, NotIntegerTypeIndexing);
}

void GetArrayType(Node *expOut, Node *expIn, Node *Integer) {
    bool integerOk = CheckIntegerExp(Integer);
    if (!integerOk) {
        expOut->type = Type::GetPrimitiveERROR();
        return;
    }
    if (expOut->nodes.size() == 1) {
        string arrayName = std::get<string>(expOut->get_nodes(0)->value);
        if (symbolTable.count(arrayName) != 0) {
            Type *arrayType = symbolTable[arrayName];
            if (arrayType->category == CATEGORY::ARRAY) {
                expOut->type = arrayType;
            } else if (arrayType == Type::GetPrimitiveERROR()) {
                expOut->type = Type::GetPrimitiveERROR();
            }
        } else {
            // Variable not found, already reported error
            expOut->type = Type::GetPrimitiveERROR();
        }
    } else {
        Type *arrayType = expIn->type;
        if (arrayType == nullptr) {
            expOut->type = Type::GetPrimitiveERROR();
            return;
        }
        if (arrayType == Type::GetPrimitiveERROR()) {
            expOut->type = Type::GetPrimitiveERROR();
            return;
        }
        if (arrayType->category == CATEGORY::ARRAY) {
            expOut->type = std::get<Array *>(arrayType->type)->base;
        }
    }
}

bool CheckBoolOperatorType(Node *exp) {
    return CheckIntegerType(exp, BinaryOperatorNotNumber);
}

void GetBoolOperatorType(Node *expOut, Node *expIn1, Node *expIn2) {
    bool check1 = CheckBoolOperatorType(expIn1);
    bool check2 = CheckBoolOperatorType(expIn2);
    if (check1 && check2) {
        expOut->type = Type::GetPrimitiveINT();
    } else {
        // Error occurred, mark as error type to avoid cascading errors
        expOut->type = Type::GetPrimitiveERROR();
    }
}

Node_TYPE CheckAlrthOperatorType(Node *exp) {
    if (exp->type == nullptr) {
        BinaryOperatorNotNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    // If already an error type, don't report cascading errors
    if (exp->type == Type::GetPrimitiveERROR()) {
        return Node_TYPE::LINE;
    }
    if (exp->type->category != CATEGORY::PRIMITIVE ||
        (exp->type != Type::GetPrimitiveINT() && exp->type != Type::GetPrimitiveFLOAT())) {
        BinaryOperatorNotNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    return std::get<Node_TYPE>(exp->type->type);
}

void GetAlrthOperatorType(Node *expOut, Node *expIn1, Node *expIn2) {
    auto check1 = CheckAlrthOperatorType(expIn1);
    auto check2 = CheckAlrthOperatorType(expIn2);
    if (check1 == Node_TYPE::LINE || check2 == Node_TYPE::LINE) {
        // Error occurred, mark as error type to avoid cascading errors
        expOut->type = Type::GetPrimitiveERROR();
    } else if (check1 == Node_TYPE::FLOAT || check2 == Node_TYPE::FLOAT) {
        expOut->type = Type::GetPrimitiveFLOAT();
    } else {
        expOut->type = Type::GetPrimitiveINT();
    }
}

void CheckTypeMatchType(Type *leftType, Type *rightType, int lineNum, const std::function<void(int)> &func) {
    // If either side is error type, don't report cascading errors
    if (leftType == Type::GetPrimitiveERROR() || rightType == Type::GetPrimitiveERROR()) {
        return;
    }
	    // If any side is nullptr, it usually means the type couldn't be
	    // determined due to a previous error (e.g., undefined function).
	    // In such cases we do NOT emit an extra mismatch error here to
	    // avoid cascading reports (e.g., r02 should only have type 2).
	    if (leftType == nullptr || rightType == nullptr) {
	        return;
	    } else if (leftType == rightType) {
        return;
    } else if (leftType->category != rightType->category) {
        func(lineNum);
    } else if (leftType->category == CATEGORY::STRUCTURE &&
               symbolTable[leftType->name]->name != symbolTable[rightType->name]->name) {
        func(lineNum);
    } else if (leftType->category == CATEGORY::ARRAY) {
        vector<int> demensionLeftArray, demensionRightArray;
        Type *insideLeftType, *insideRightType;
        std::tie(demensionLeftArray, insideLeftType) = GetArrayDemensionAndType(leftType);
        std::tie(demensionRightArray, insideRightType) = GetArrayDemensionAndType(rightType);
        if (demensionLeftArray.size() != demensionRightArray.size() ||
            std::equal(demensionLeftArray.cbegin(), demensionLeftArray.cend(), demensionRightArray.cbegin())) {
            func(lineNum);
        } else if (insideLeftType == nullptr || insideRightType == nullptr) {
            func(lineNum);
        } else if (insideRightType->category != insideLeftType->category) {
            func(lineNum);
        } else if (insideRightType->category == CATEGORY::PRIMITIVE && insideLeftType != insideRightType) {
            func(lineNum);
        } else if (insideRightType->category == CATEGORY::STRUCTURE) {
            if (insideLeftType->name != insideRightType->name) {
                func(lineNum);
            }
        }
    } else {
        func(lineNum);
    }
}

void CheckTypeMatch(Node *left, Node *right, int lineNum) {
    Type *leftType = left->type;
    Type *rightType = right->type;

    // For assignment, we want to report type mismatch even if one side is ERROR
    // This allows reporting both the original error and assignment error
    if (leftType == nullptr || rightType == nullptr) {
        return;
    }

    // If both sides are ERROR, don't report assignment error (both already have errors)
    if (leftType == Type::GetPrimitiveERROR() && rightType == Type::GetPrimitiveERROR()) {
        return;
    }

    // If only one side is ERROR, report assignment error
    if (leftType == Type::GetPrimitiveERROR() || rightType == Type::GetPrimitiveERROR()) {
        MisMatchTypeBothSide(lineNum);
        return;
    }

    // Normal type checking
    CheckTypeMatchType(leftType, rightType, lineNum, MisMatchTypeBothSide);
}


void CheckReturnValueMatchDeclaredType(Node *extDefSfc) {
    Type *returnType = symbolTable[std::get<string>(extDefSfc->get_nodes(1, 0)->value)]->returnType;
    Node *compSt = extDefSfc->get_nodes(2);
    CheckReturnValueFromCompStmt(returnType, compSt);
}


void CheckReturnValueFromStmtList(Type *type, Node *stmtList) {
    if (stmtList->nodes.empty()) {
        return;
    } else {
        CheckReturnValueFromStmt(type, stmtList->get_nodes(0));
        CheckReturnValueFromStmtList(type, stmtList->get_nodes(1));
    }
}

void CheckReturnValueFromCompStmt(Type *type, Node *compStmt) {
    CheckReturnValueFromStmtList(type, compStmt->get_nodes(2));
}

void CheckReturnValueFromStmt(Type *type, Node *stmt) {
    if (stmt->get_nodes(0)->name == "RETURN") {
        Type *returnType = stmt->get_nodes(1)->type;

        // For return type checking, report error even if return expression is ERROR type
        if (returnType == nullptr) {
            return;
        }

        // If return type is ERROR, still report return type mismatch
        if (returnType == Type::GetPrimitiveERROR()) {
            ReturnMisMatchType(std::get<int>(stmt->value));
            return;
        }

        // Normal type checking
        CheckTypeMatchType(type, returnType, std::get<int>(stmt->value), ReturnMisMatchType);
    } else if (stmt->nodes.size() == 1 && stmt->get_nodes(0)->name == "CompSt") {
        CheckReturnValueFromCompStmt(type, stmt->get_nodes(0));
    } else if (stmt->get_nodes(0)->name == "IF") {
        switch (stmt->nodes.size()) {
            case 5:
            case 6: {
                CheckReturnValueFromStmt(type, stmt->get_nodes(4));
                break;
            }
            case 7: {
                CheckReturnValueFromStmt(type, stmt->get_nodes(4));
                CheckReturnValueFromStmt(type, stmt->get_nodes(6));
                break;
            }
        }
    } else if (stmt->get_nodes(0)->name == "WHILE") {
        CheckReturnValueFromStmt(type, stmt->get_nodes(4));
    }
}
