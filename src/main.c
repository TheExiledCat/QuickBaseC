#include "context.h"
#include "converter.h"
#include "mongoose.h"
#include "schema.h"
#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "argparse.h"
typedef struct command {
  char *name;
  int (*action)(int, const char **);
} command;
int Serve(int argc, const char **argv);
int Tui(int argc, const char **argv);
int Initialize(int argc, const char **argv);

static const char *usages[] = {"command [options]", "init [-o <output>]",
                               "serve -p <PORT>", "tui", NULL};
static command commands[] = {
    {"init", Initialize}, {"serve", Serve}, {"tui", Tui}};
int main(int argc, const char *argv[]) {
  struct argparse argp;
  struct argparse_option basicOptions[] = {OPT_HELP(), OPT_END()};
  argparse_init(&argp, basicOptions, usages, ARGPARSE_STOP_AT_NON_OPTION);
  argc = argparse_parse(&argp, argc, argv);
  if (argc < 1) {
    argparse_usage(&argp);
    return -1;
  }
  command *cmd = NULL;
  for (int i = 0; i < sizeof(commands) / sizeof(command); i++) {

    if (!strcmp(commands[i].name, argv[0])) {
      cmd = &commands[i];
      if (cmd) {
        return cmd->action(argc, argv);
      }
    }
  }

  return 0;
}
int Tui(int argc, const char *argv[]) { return 0; }
int Serve(int argc, const char *argv[]) {
  printf("Hello World");
  return 0;
}
int Initialize(int argc, const char **argv) {

  char *path = strdup("schemes");
  DIR *dir = opendir(path);
  Schema *schema;
  if (dir == NULL) {
    printf("creating schemes directory\n");
    mkdir(path, 0700);
    schema = DefaultSchema();
    WriteSchema(schema, path);
  }
  printf("Ensuring database exists\n");
  Init(schema);
  return 0;
}
