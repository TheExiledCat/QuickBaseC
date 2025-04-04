#include <json-c/json.h>
#include "schema.h"
typedef enum ConvertResult{
  CONVERT_SUCCESS,
  CONVERT_FAILURE
}ConvertResult;

ConvertResult ConvertSchema(Schema* schema, const char** output);
