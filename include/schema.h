#pragma once
#include "model.h"
typedef struct Settings {

} Settings;
typedef struct Schema {
  int entityCount;
  char* version;
  Settings settings;
  Entity* entities[];
} Schema;

Schema* DefaultSchema();
