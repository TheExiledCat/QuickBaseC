#pragma once
#include "schema.h"
#include <sqlite3.h>
bool Init(Schema *schema);
bool EnsureDatabaseCreation(Schema *schema);
bool CreateTables(Schema *schema);
bool StoreSchema(Schema *schema);
bool AddEntityToDatabase();
