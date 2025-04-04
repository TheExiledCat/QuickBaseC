#include "converter.h"
#include "schema.h"
#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
json_object *SetRoot(Schema *schema);
void SetEntities(json_object *root, Schema *schema);
void SetFields(json_object *fields, Entity *entity);

typedef bool (*FieldHandler)(json_object *fieldObject, EntityField *field);
bool HandleTextField(json_object *fieldObject, EntityField *field);
bool HandleDateField(json_object *fieldObject, EntityField *field);

const FieldHandler handlers[] = {HandleTextField, HandleDateField};
ConvertResult ConvertSchema(Schema *schema, const char **output) {
  json_object *root = SetRoot(schema);
  SetEntities(root, schema);
  *output = json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);
  return CONVERT_SUCCESS;
}
json_object *SetRoot(Schema *schema) {
  json_object *root = json_object_new_object();

  // version
  json_object_object_add(root, "version",
                         json_object_new_string(schema->version));

  // settings
  json_object *settings = json_object_new_object();
  json_object_object_add(root, "settings", settings);
  // entities
  json_object *entityCount = json_object_new_int(schema->entityCount);
  json_object_object_add(root, "entityCount", entityCount);
  json_object *entities = json_object_new_array();
  json_object_object_add(root, "entities", entities);
  return root;
}
void SetEntities(json_object *root, Schema *schema) {
  json_object *entities = json_object_object_get(root, "entities");
  for (int i = 0; i < schema->entityCount; i++) {
    Entity *entity = schema->entities[i];
    printf("Settings entity %s\n", entity->name);
    json_object *entityObject = json_object_new_object();
    json_object_object_add(entityObject, "name",
                           json_object_new_string(entity->name));
    json_object_object_add(entityObject, "type",
                           json_object_new_int(entity->type));
    json_object_object_add(entityObject, "fieldCount",
                           json_object_new_int(entity->fieldCount));
    json_object *fields = json_object_new_array();
    json_object_object_add(entityObject, "fields", fields);
    SetFields(fields, entity);
    json_object_array_add(entities, entityObject);
  }
}
void SetFields(json_object *fields, Entity *entity) {
  for (int i = 0; i < entity->fieldCount; i++) {
    EntityField *field = entity->fields[i];
    json_object *fieldObject = json_object_new_object();
    json_object_object_add(fieldObject, "type",
                           json_object_new_int(field->type));
    json_object_object_add(fieldObject, "name",
                           json_object_new_string(field->name));
    json_object_object_add(fieldObject, "nullable",
                           json_object_new_boolean(field->nullable));
    json_object_object_add(fieldObject, "base",
                           json_object_new_boolean(field->base));

    for (int i = 0; i < sizeof(handlers) / sizeof(FieldHandler *); i++) {
      FieldHandler handler = handlers[i];
      if (handler(fieldObject, field)) {
        break;
      }
    }
    json_object_array_add(fields, fieldObject);
  }
}
bool HandleTextField(json_object *fieldObject, EntityField *field) {
  if (field->type != FIELD_TEXT) {
    return false;
  }
  TextField *textField = (TextField *)field;
  json_object_object_add(fieldObject, "minLength",
                         json_object_new_int(textField->minLength));
  json_object_object_add(fieldObject, "maxLength",
                         json_object_new_int(textField->maxLength));
  json_object_object_add(fieldObject, "validationPattern",
                         json_object_new_string(textField->validationPattern));
  json_object_object_add(fieldObject, "generationPattern",
                         json_object_new_string(textField->generationPattern));
  return true;
}
bool HandleDateField(json_object *fieldObject, EntityField *field) {

  if (field->type != FIELD_DATE) {
    return false;
  }
  DateField *dateField = (DateField *)field;

  char minDateString[30];
  char maxDateString[30];
  json_object *minDateObject;
  json_object *maxDateObject;
  char *format = "%Y-%m-%dT%H:%M:%S";
  if (dateField->minDate) {

    strftime(minDateString, sizeof(minDateString), format, dateField->minDate);
    minDateObject = json_object_new_string(minDateString);
  } else {
    minDateObject = json_object_new_null();
  }
  if (dateField->maxDate) {

    strftime(maxDateString, sizeof(maxDateString), format, dateField->maxDate);
    maxDateObject = json_object_new_string(maxDateString);
  } else {

    maxDateObject = json_object_new_null();
  }
  json_object_object_add(fieldObject, "minDate", minDateObject);
  json_object_object_add(fieldObject, "maxDate", maxDateObject);
  return true;
}
