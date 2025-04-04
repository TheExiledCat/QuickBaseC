#include "schema.h"
#include <json-c/json.h>
typedef enum ConvertResult { CONVERT_SUCCESS, CONVERT_FAILURE } ConvertResult;

ConvertResult ConvertSchema(Schema *schema, const char **output);
void WriteSchema(Schema *schema, char *dir);
