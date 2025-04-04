#include "schema.h"
#include "version.h"
Schema *DefaultSchema() {
  Schema *schema = malloc(sizeof(Schema) + sizeof(Entity *)); // only auth
  schema->version = QUICKBASE_VERSION;
  schema->entityCount = 1;
  Entity *entity;
  NewEntity("Users", ENTITY_AUTH, &entity);
  schema->entities[0] = entity;

  return schema;
}
