#pragma once
#include "schema.h"
#include <json-c/json.h>
typedef enum ParseResult{
  PARSE_SUCCESS,
  PARSE_FAILURE,
  PARSE_SYNTAX_ERR
}ParseResult;

ParseResult ParseSchema(char* input, Schema* outSchema);

