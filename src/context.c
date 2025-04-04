#include "context.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define DATABASE_DIR "data/"
#define DATABASE_NAME "qb_data.sqlite"
#define DATABASE_PATH DATABASE_DIR DATABASE_NAME
sqlite3 *conn;
bool EnsureDatabaseCreation(Schema *schema) {

  struct stat st = {0};
  if (stat(DATABASE_DIR, &st) == -1) {
    mkdir(DATABASE_DIR, 0700);
  }
  if (access(DATABASE_PATH, F_OK)) {
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
bool CreateTables(Schema *schema) { return true; }
