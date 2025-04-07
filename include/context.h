#pragma once
#include "schema.h"
#include <sqlite3.h>
typedef enum MigrationType {
  MIGRATE_ADD_FIELD,
  MIGRATE_UPDATE_FIELD,
  MIGRATE_REMOVE_FIELD,
  MIGRATE_ADD_ENTITY,
  MIGRATE_REMOVE_ENTITY,

} MigrationType;

int MigrateField(MigrationType type, Schema *newSchema);
bool Init(Schema *schema);
bool EnsureDatabaseCreation(Schema *schema);
bool CreateTables(Schema *schema);
bool StoreSchema(Schema *schema);
bool AddEntityToDatabase();
