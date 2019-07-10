# TODO Banter_Visualizer_C

## Table of Contents
- [Goals](#goals)
- [Method to Achieve Goals](#method-to-achieve-goals)
- [Expected Use Cases](#expected-use-cases)
- [Flow Layout](#flow-layout)
  - [Core](#core)
  - [Command Line Interface](#command-line-interface)
  - [Reader](#reader)
  - [Mapper](#mapper)
  - [Outputter](#outputter)
  - [Renderer](#renderer)

## GOALS
  1. be portable (windows,mac,linux,etc.)
  2. be modifiable (well modularized codebase)
  3. be usable in it's components (renderer,mapper,reader on it's own)
  4. be FAST (minimal overhead in C)
  5. have a SMALL footprint (both in binary & in memory)
  6. Be accessible to general users
  7. Provide a graphical interface to show graphical component, and HEX component in
  8. Allow signature analysis based on mappings

## METHOD TO ACHIEVE GOALS
  1. Write it in C90 to squeeze for performance
  2. Capable of cross-compiling on other platforms from a single C90 code-base
  3. Write interface, renderer, mapper, reader together into CLI
  4. UI will be in a separate binary, built strictly for the UI aspect
  5. Signature analysis should be extensible for users to provide their own mapping and analysis functionality

## EXPECTED USE CASES
  1. Static analysis
  2. Dynamic analysis (memory scanning)
  3. Process profiling
  4. Data Agnostic determination
  5. In conjunction with other tools

## Flow Layout

/// prog1 ///<br>
[ CLI ]<br>
v<br>
[ CORE ] > [ READER ] > [ MAPPER ] > [ ?OUTPUTTER? ] > [ RENDERER ]<br>

The cli program will handle requests for render ready data for a given file, process or directory. Every request will be supplied with arguments to setup the environment of the cli to read, map, analyze and return data to the requesting process. Additionally it will generate an OpenGL view.
### Core
  - wraps the cli, reader, mapper, outputter, and renderer.
  - orchestrates the interaction between these 4 subcomponents
### Command Line Interface
  - command line args to start program in a given mode with given args (such as static, dynamic, refresh times, etc.)
  - Args can be passed at startup, and may be passed by ARG=VALUE during runtime
  - CLI will work by starting with args, reading it's first frame, and waiting for subsequent args
  - args (first is default)
    - reads from a file or process ID#
    - mode=[file/process/dir(to visualize folder structure, possibly all files inside)]
    - output=[stdout/file]
    - loadmaps=[comma separated list of mappings from files to load by hand (file format TBD)]
    - map=[one of the location mappings by keyword]
    - color=[one of the color mappings by keyword]
    - stride=[100bytes,w/e # of bytes for each full viewing pane]
    - offset=[byte offset to start reading from]
    - scale=[1, ratio of bytes shown per point, 2 would show 2 bytes per point for ex.]
### Reader
  - abstraction to an underlying reader
  - may be a physical file, process id, or directory structure
  - Returns a number of bytes from the reading target to the core
### Mapper
  - maps arbitarary data into render ready data (json with position & color)
    - may also return just a function pointer to expedite the process instead of 'double' copying data
  - this is preprocessing of the data for raw analysis
  - Should allow ANY mapping method that conforms to a given interface
  - Should be extended to allow scripts that define a user customizable rendering approach
  - Mapper should also include mechanisms to perform analysis on the data
    - This means looking for sub-signatures within what is being mapped, and properly mapping those too
### Outputter (~)
  - Conditionally takes render ready data, and file data, and write it out with a given output method
  - Method can be STDOUT, FILE, PIPE, will be abstracted (no server work here, can be a separate process if needed)
  - this output will be in a standard format (JSON)
  - Data can be parsed and displayed by a conforming RENDERER
### Inputter (~)
  - Takes prepped render data, decodes it, and renders it
  - Used to allow a CLI on one device to send data for rendering on another device
### Renderer
  - OpenGL in C, JUST the rendered output
  - Does NOT contain interface components to alter output
  - This takes render ready data and presents it visually
  - Utilizes the system available graphics api to render
  - Displays prepared data on the screen in a 3 dimensional visual, corresponds to the underlying structure of the source
  
### other things...
  - alt x,y render along z progression render
  - inspired by GL globe (google thing), but for a process instead
