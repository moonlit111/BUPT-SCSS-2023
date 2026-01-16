#include "type.h"


Type::Type(string _name, CATEGORY _category, Type::PRIMI _type) :
        name(std::move(_name)),
        category(_category),
        type(std::move(_type)) {
}

#define GetPrimitive(TYPE) \
Type *Type::GetPrimitive##TYPE() {\
    static auto will_return = new Type{#TYPE, CATEGORY::PRIMITIVE, Node_TYPE::TYPE};\
    return will_return;\
}

GetPrimitive(INT);

GetPrimitive(CHAR);

GetPrimitive(FLOAT);

GetPrimitive(ERROR);

#undef getPrimitive

Type *Type::GetPrimitiveType(Node_TYPE type) {
    switch (type) {
        case Node_TYPE::INT : {
            return Type::GetPrimitiveINT();
        }
        case Node_TYPE::FLOAT : {
            return Type::GetPrimitiveFLOAT();
        }
        case Node_TYPE::CHAR : {
            return Type::GetPrimitiveCHAR();
        }
        default: {
            throw std::invalid_argument("Unknown Node_TYPE");
        }
    }
}

Array::Array(Type *base, int size) : base(base), size(size) {}

FieldList::FieldList(string name, Type *type, FieldList *next) : name(std::move(name)), type(type), next(next) {}
