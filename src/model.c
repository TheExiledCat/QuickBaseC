#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 255
bool NewEntity(char *name, EntityType type, Entity **outEntity) {
  if (strlen(name) > MAX_NAME_LEN) {
    return false;
  }
  Entity *entity = NULL;
  entity = malloc(sizeof(Entity));
  entity->name = name;
  TextField *idField = NULL;
  DateField *createdField = NULL;
  DateField *updatedField = NULL;
  NewTextField("id", false, 15, 15, "^[a-z0-9]+$", "[a-z0-9]{15}", true,
               &idField);
  NewDateField("created", false, NULL, NULL, true, &createdField);
  NewDateField("updated", false, NULL, NULL, true, &updatedField);
  entity->fieldCount = 0;
  AddField(&entity, (EntityField *)idField);
  AddField(&entity, (EntityField *)createdField);
  AddField(&entity, (EntityField *)updatedField);
  entity->type = type;
  switch (type) {

  case ENTITY_DATA:
  case ENTITY_AUTH:
  case ENTITY_COMPUTED:;

    break;
  }
  if (entity == NULL) {
    return false;
  }

  *outEntity = entity;
  return true;
}
bool NewTextField(char *name, bool nullable, unsigned int minLength,
                  unsigned int maxLength, char *validationPattern,
                  char *generationPattern, bool base, TextField **outField) {
  TextField *field = malloc(sizeof(TextField));
  field->field.base = base;
  field->field.name = name;
  field->field.nullable = nullable;
  field->field.type = FIELD_TEXT;
  field->minLength = minLength;
  field->maxLength = maxLength < minLength ? minLength : maxLength;
  field->generationPattern = generationPattern;
  field->validationPattern = validationPattern;
  *outField = field;
  return true;
}
void AddField(Entity **entity, EntityField *field) {
  if (entity == NULL || field == NULL) {
    printf("entity or field is null\n");
    return;
  }
  // create new entity and copy over values, but with 1 more field
  Entity *old = *entity;
  int newCount = old->fieldCount + 1;
  Entity *new = malloc(sizeof(Entity) + sizeof(EntityField *) * newCount);
  new->fieldCount = newCount;
  new->name = old->name;
  new->type = old->type;
  printf("new field count: %d\n", new->fieldCount);
  for (int i = 0; i < old->fieldCount; i++) {
    // copy values
    new->fields[i] = old->fields[i];
  }
  // set new value
  new->fields[new->fieldCount - 1] = field;
  printf("added field %s\n", new->fields[new->fieldCount - 1]->name);
  *entity = new;
  free(old);
}

bool NewDateField(char *name, bool nullable, dateTime *minDate,
                  dateTime *maxDate, bool base, DateField **outField) {

  DateField *field = malloc(sizeof(DateField));
  field->field.base = base;
  field->field.name = name;
  field->field.nullable = nullable;
  field->field.type = FIELD_DATE;
  field->minDate = minDate;
  if (minDate == NULL || maxDate == NULL) {
    field->maxDate = maxDate;
  } else {
    time_t minTime = mktime(minDate);
    time_t maxTime = mktime(maxDate);
    field->minDate = minDate;
    field->maxDate = maxTime < minTime ? minDate : maxDate;
  }

  *outField = field;
  return true;
}

bool NewNumberField(char *name, bool nullable, double min, double max,
                    bool isFloat, bool base, NumberField **outField) {

  NumberField *field = malloc(sizeof(NumberField));
  field->field.base = base;
  field->field.name = name;
  field->field.nullable = nullable;
  field->field.type = FIELD_NUMBER;
  field->isFloat = isFloat;
  if (isFloat) {
    field->minFloat = min;
    field->maxFloat = max;
  } else {
    field->minInt = min;
    field->maxInt = max;
  }
  *outField = field;
  return true;
}
