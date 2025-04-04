#include "context.h"
#include "converter.h"
#include "mongoose.h"
#include "schema.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  Schema *schema = DefaultSchema();
  const char *json;
  ConvertSchema(schema, &json);
  Init(schema);
}
