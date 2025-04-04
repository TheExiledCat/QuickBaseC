# Quickbase



_Open source backend in a single c binary_

## Introduction

QuickBase is shipped as a single file command-line program capable of generating a full backend including REST API, Database and Scheme for you. It is currently only supported for Linux but Mac and Windows support is on the roadmap.

Quickbase is segmented into 3 parts:

- The Command Line: used to run commands like starting the server, updating the scheme/migrations and modifying settings

- The TUI: a built in text user interface built in ncurses that can be used to more easily update the scheme and settings and makes overviewing the database entries much more user friendly (use `quickbase --gui <DIR>` to access)

- External files: even tho the quickbase binary is a single file, whenever its command line properties are used to initialize a new backend, it will generate some necessary files in the directory chosen:
  
  - data/ : data directory containing:
    
    - qb_database.sqlite (main database)
    
    - qb_database.backup.sqlite (backup database)
  
  - scheme/ : directory containing json files which store the backends schema into json files, these json files are timestamped and the newest one in the directory will be used for the database, although possible, it is not recommended to manually edit these files as this can cause desync between the database and the scheme. always use the command line tools or the TUI to modify the scheme, ensuring the database always matches. The only way to manually modify the scheme json and ensuring a synched database is by deleting the database after every modification (obviously not recommended).
    
    
    

# Installation

even though package manager support is coming in the future, the easiest way to get quickbase working is by downloading the binary for your architecture from the releases page and added it to you path.



## Usage

creating a new backend project:

`quickbase init -o myprojectdir` or in the current work dir: `quickbase init`



to serve the backend:

`quickbase serve <PORT>`  (port defaults to 3000 if not specified)

to open the tui:

`quickbase gui` (for the full tui guide see [Tui](./docs/tui.md)

a guide for using quickbase throughout the command line is work in progress.


