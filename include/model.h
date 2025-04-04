#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
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
typedef struct EntityField {
  FieldType type;
  char *name;
  bool nullable;
  bool base;
} EntityField;
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
typedef struct Entity {
  char *name;
  EntityType type;
  int fieldCount;
  EntityField *fields[];
} Entity;

bool NewEntity(char *name, EntityType type, Entity **outEntity);
bool NewTextField(char *name, bool nullable, unsigned int minLength,
                  unsigned int maxLength, char *validationPattern,
                  char *generationPattern, bool base, TextField **outField);

bool NewDateField(char *name, bool nullable, dateTime *minDate,
                  dateTime *maxDate, bool base, DateField **outField);
bool NewNumberField(char *name, bool nullable, double min, double max,
                    bool isFloat, bool base, NumberField **outField);
void AddField(Entity **entity, EntityField *field);
