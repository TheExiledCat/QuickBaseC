#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
// base types
typedef struct tm dateTime;
typedef enum FieldType {
  FIELD_TEXT,
  FIELD_NUMBER,
  FIELD_DATE,
  FIELD_RELATION,
  FIELD_BOOL
} FieldType;
typedef enum EntityType {
  ENTITY_AUTH,
  ENTITY_DATA,
  ENTITY_COMPUTED
} EntityType;
// field parent
typedef struct EntityField {
  FieldType type;
  char *name;
  bool nullable;
  bool base;
} EntityField;
// field children
typedef struct TextField {
  EntityField field;
  unsigned int minLength;
  unsigned int maxLength;
  char *validationPattern;
  char *generationPattern;

} TextField;
typedef struct DateField {
  EntityField field;
  dateTime *minDate;
  dateTime *maxDate;

} DateField;
typedef struct NumberField {
  EntityField field;
  bool isFloat;
  union {
    unsigned int minInt;
    double minFloat;
  };
  union {
    unsigned int maxInt;
    double maxFloat;
  };
} NumberField;
typedef struct BoolField {
  EntityField field;

} BoolField;
// Entity itself
typedef struct Entity {
  char *name;
  EntityType type;
  int fieldCount;
  EntityField *fields[];
} Entity;

#define base_fields char *name, bool nullable, bool base
// constructors and extra functions
bool NewEntity(char *name, EntityType type, Entity **outEntity);
bool NewTextField(base_fields, unsigned int minLength, unsigned int maxLength,
                  char *validationPattern, char *generationPattern,
                  TextField **outField);

bool NewDateField(base_fields, dateTime *minDate, dateTime *maxDate,
                  DateField **outField);
bool NewNumberField(base_fields, double min, double max, bool isFloat,
                    NumberField **outField);
bool NewBoolField(base_fields, BoolField **outField);
void AddField(Entity **entity, EntityField *field);
