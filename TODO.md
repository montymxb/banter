::TODO Bante_Visualizer_C::

1. GOALS
  1. be portable (windows,mac,linux,etc.)
  2. be modifiable (well modularized codebase)
  3. be usable in it's components (renderer,mapper,reader on it's own)
  4. be FAST (minimal overhead in C)
  5. have a SMALL footprint (both in binary & in memory)
  6. Be accessible to general users
  7. Provide a graphical interface to show graphical component, and HEX component in
  8. ~~ Provide signature analysis based on mappings

2. METHOD TO ACHIEVE GOALS
  1. Write it in C90, know how to make this xcompile fairly easily
  2. write interface, renderer, mapper, reader, UI separately
  3. Use direct open,read,close to speed up access
  5. Graphical interface will have to use native implmentation, which is platform dependent...
  6. Extended signature analysis will need to use some sort of an extensible component
    - User can provide their own signature analysis (maybe by using latria??)

3. EXPECTED USE CASES
  1. Static analysis
  2. Dynamic analysis (memory scanning)
  3. Process profiling
  4. Data Agnostic determination
  5. In conjunction with other tools

4. FINAL IMPACT
  1. Something everyone can use to profile their systems, programs, environments effectively & quickly

::Flow Layout::

/prog1/
[ CLI ] -> [ CORE ]-/> [ READER ] -\
                    |       v      |
                    -> [ MAPPER ]  |
                    |       v      |
                    \> [ OUT    ] </
                            v
  /prog2/                   |
[ RENDERER ]  <-------------/

* Command Line Interface [CLI]
  - command line args to start program in a given mode with given args (such as static, dynamic, refresh times, etc.)
  - Args can be passed at startup, and may be passed by ARG=VALUE during runtime
  - CLI will work by starting with args, reading it's first frame, and waiting for subsequent args
  - args (first is default)
    - reads from a file or process ID#
    - mode=[file/process/dir?(visualize all in a folder maybe?)]
    - output=[stdout/file]
    - loadmaps=[comma separated list of mappings from files to load by hand (method by which is unknown yet...)]
    - map=[one of the location mappings by keyword]
    - color=[one of the color mappings by keyword]
    - stride=[100bytes,w/e # of bytes for each full viewing pane]
    - jumpto=[# of bytes offset to jump to in a file]
    - scale=[1, ratio of bytes shown per point, 2:1 would show 2 bytes per point for ex.]
* Core [CORE]
* Reader [READER]
  - abstraction to an underlying reader
  - may be a physical file or an id to a process in memory
  - Anything PAST the reader shouldn't care where this data is coming from, it's abstracted at that point
* Mapper [MAPPER]
  - this takes data produced by the reader and maps it into render ready data (position & color)
    - may also return just a function pointer to expedite the process instead of 'double' copying data
  - this is preprocessing of the data for raw analysis
  - Isolated from renderer & reader
  - Should allow ANY mapping method that conforms to a given interface
  - Should be extended to allow use scripts (lua/latria??) that define a rendering approach
  - Mapper should also include mechanisms to ANALYZE SEGMENTS!
    - This means looking for sub-signatures within what is being mapped, and properly mapping those too
  - Maps RAW & SPECIFIC (raw is total, specific is signature based)
* Outputter [OUT]
  - Takes render ready data, and file data, and write it out with a given output method
  - Method can be STDOUT, FILE, or perhaps a STREAM, will be abstracted (no server work either, can be a separate process if needed)
  - Idea is this output will be in a standard format (JSON)
  - Data can be parsed and displayed by a RENDERER

:: Program 2 (Platform Dependent, Python?) ::
* Renderer [RENDERER]
  - This takes the render ready data from the output, and presents it visually
  - Utilizes the system available graphics api to render
  - Also takes data read & displays it on the screen, corresponding to what is visually present
  - Will vary based on the system
  - THIS DOES NOT HAVE TO BE IN C!
  - Can write this in Python where 3D graphics should be much easier to manage...

* Final question, should the program hold state, or be stateless?
  - With state
    - Holds it as it goes in mem
  - Without state
    - Returns arg data to the program, and would require that data on each call
  -- Probably want it to hold state, so that we don't keep reloading data into mem each time??
    - Think about it..
