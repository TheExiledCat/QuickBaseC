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

`quickbase gui` (for the full tui guide see [Tui](./docs/tui.md))

a guide for using quickbase throughout the command line is work in progress.



## Features

### Schema creation and enfocring

You simply create a schema using the TUI, this schema contains all your tables, constraints, api settings, and DTOs.

Whenever a request for a resource comes into the server, it will validate the request based on the schema, ensuring you can only grab data specified in the schema, according to the authentication settings in the schema



### Authentication

Quickbase automatically handles authentication for you. by defining authentication Entities, you define the different models of authentication your application can use. since these are just entities, they have their own data. This data can be used to make rules on your resources that can define which entity endpoints work for which roles, when a user makes a request using a token it will pass through all of your api rules, these rules specify the conditions the resource AND the requesting user have to pass before allowing the data to be sent back. this ensures safety on the backend side while also making it easy to manage validation.



### DTOs

This is what makes Quickbase truly Unique. 

In Quickbase you can define DTOs (Data transfer objects) for each of your entities that specify, what data is returned to the requesting user when a request is made. for example

lets say i have the following entity:

`Product` that has its base fields and a field `number: price` a field `text: barcode` a field `text:name` and a field `enum: type`.

for certain requests, you might only need certain parts of this entity, or for safety reasons need to encapsulate or hide data from the requesting user.

therefore, we can create a DTO to (for example) only give us the type and name of a product:

`DTO: ProductTypeDTO` with the fields type and name being the only thing they contain. this also makes database querying faster as the dto will also be used for the query.

#### Defining a DTO

dtos are defined in plain typescript using lambdas. inside of quickbase you can create a dto, which is just a list of lambda functions for each field of an entity.

in the previous example the dto might have the following lambdas:

name:

```ts
(value) => value
```

type:

```ts
(value)=> myEnum[value]
```

as you can see, this approach also makes it possible to provide modifications to the data before returning, lets say we have a field `date: birthday` in an entity and want to make a dto that returns the age of the entity:

```ts
value => (new Date() - value).year
```

This is incredibly powerful and easy to define.

These DTOS are internally convertable to Typescript definitions, making them instantly usable in the frontend without extra code:

`quickbase dtogenerate <path_to_frontend_folder>`



quickbase types map to the following javascript types:

`number => number` (with proper floating point handling)

`text => string`

`date => date`

`bool => bool`

`relation => string`

`enum => enum` (all enums are numbers by definition but can be user as their named variants using dtos)



## 

### Lightweight and portable

since quickbase is a single binary written in c, it is insanely fast and lightweight making it very suitable for environments with limited memory or storage. A user might place a quickbase instance on a rasberry pi or embedded hardware to host a server without too much overhead

## Open Source

quickbase is fully open source and currently maintained by `TheExiledCat`

for contributions and feature requests see [Contributions and Features](./docs/Contributions.md)


