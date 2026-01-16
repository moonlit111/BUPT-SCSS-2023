#include "error.h"

#define PARSER_error_OUTPUT stdout

void error(ERROR_TYPE type) {
    static const std::unordered_map<ERROR_TYPE, std::string> yyerror_map = {
            {ERROR_TYPE::LACK_OF_RC, R"(closing curly braces  })"},
            {ERROR_TYPE::LACK_OF_RB, R"(closing bracket ])"},
            {ERROR_TYPE::LACK_OF_RP, R"(closing parenthesis ))"},
            {ERROR_TYPE::LACK_OF_LC, R"(left curly braces  {)"},
            {ERROR_TYPE::LACK_OF_LB, R"(left bracket [)"},
            {ERROR_TYPE::LACK_OF_LP, R"(left parenthesis ()"},
            {ERROR_TYPE::MISS_SPEC,  R"(specifier)"},
            {ERROR_TYPE::MISS_SEMI,  R"(semicolon ;)"},
            {ERROR_TYPE::MISS_COMMA, R"(COMMA ,)"},
    };
    fprintf(PARSER_error_OUTPUT, "Missing %s\n", yyerror_map.at(type).c_str());
}
