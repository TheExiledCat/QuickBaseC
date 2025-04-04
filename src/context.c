#include "context.h"
#include "model.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define DATABASE_DIR "data/"
#define DATABASE_NAME "qb_data.sqlite"
#define DATABASE_PATH DATABASE_DIR DATABASE_NAME

bool GetTableQuery(Entity *entity, sqlite3_stmt **stmt);
char *GetFieldQuery(EntityField *field);
sqlite3 *conn;

char *EntityTypeToSQLITE(EntityField *field);
bool EnsureDatabaseCreation(Schema *schema) {

  struct stat st = {0};
  if (stat(DATABASE_DIR, &st) == -1) {
    printf("Data dir not found, creating\n");
    mkdir(DATABASE_DIR, 0700);
  }
  if (!access(DATABASE_PATH, F_OK)) {
    printf("database already exists\n");
    return true;
  }
  sqlite3_open(DATABASE_PATH, &conn);
  // run scheme to database functionality?

  CreateTables(schema);
  sqlite3_close(conn);
  return conn == NULL ? false : true;
}
bool Init(Schema *schema) {
  EnsureDatabaseCreation(schema);
  if (sqlite3_open(DATABASE_PATH, &conn) != SQLITE_OK) {
    sqlite3_close(conn);
    return false;
  }
  return true;
}
bool CreateTables(Schema *schema) {
  printf("Creating tables\n");
  for (int i = 0; i < schema->entityCount; i++) {

    sqlite3_stmt *query;
    Entity *entity = schema->entities[i];
    printf("creating table %s\n", entity->name);
    GetTableQuery(entity, &query);
    int result = sqlite3_step(query);
    if (result != SQLITE_OK && result != SQLITE_DONE) {
      printf("%s", sqlite3_errmsg(conn));
    }
  }
  return true;
}
bool GetTableQuery(Entity *entity, sqlite3_stmt **stmt) {
  char *query = malloc(0xFFF);
  sprintf(query, "CREATE TABLE IF NOT EXISTS %s (", entity->name);
  for (int i = 0; i < entity->fieldCount; i++) {
    EntityField *field = entity->fields[i];
    sprintf(query, "%s %s %s%s", query, field->name, EntityTypeToSQLITE(field),
            i == entity->fieldCount - 1 ? "" : ",");
  }
  sprintf(query, "%s)", query);
  printf("query: %s\n", query);
  sqlite3_prepare(conn, query, -1, stmt, NULL);
  free(query);
  return true;
}
char *GetFieldQuery(EntityField *field) { return ""; }
char *EntityTypeToSQLITE(EntityField *field) {
  switch (field->type) {

  case FIELD_TEXT:
  case FIELD_DATE:
    return "TEXT";

  case FIELD_NUMBER: {
    NumberField *numField = (NumberField *)field;
    return numField->isFloat ? "REAL" : "INTEGER";
  }

  case FIELD_RELATION:
    return "INTEGER";
  case FIELD_BOOL:
    return "INTEGER";
  }
}
