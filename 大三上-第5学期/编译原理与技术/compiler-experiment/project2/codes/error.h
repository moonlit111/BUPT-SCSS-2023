#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <unordered_map>

enum class ERROR_TYPE {
    LACK_OF_RC, LACK_OF_RB, LACK_OF_RP,
    LACK_OF_LC, LACK_OF_LB, LACK_OF_LP,
    MISS_SPEC, MISS_SEMI, MISS_COMMA
};

void error(ERROR_TYPE type);

#endif 
