# banter
A software tool for applied visualization and structural analysis of data.

## What is banter?

Banter is a tool for visualizing data independent of underlying structure. This allow for visual identification, classificiation and comparison of known and unknown structures by their visual signature.

The following is a low quality gif, but it demonstrates a visual analysis approach to looking at a php 7.3.11 binary on macOS Catalina.
<br/>
<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b1.gif"></img>
<br/>
A brief demonstration of banter browsing through the initial part of the binary.
<br/>
<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b2.gif"></img>
<br/>
A rotation around a portion that is shown to have predominantly ascii characters, evidenced by the signature white blocks in one specific area of the cube.
<br/>
<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b3.gif"></img>
<br/>
Visualization of a structurally significant area within the later part of the PHP binary. Notice the change from ascii to a large block of data (possibly compressed), being followed by what appears to be a regular table structure of some sort.
<br/>
<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b4.gif"></img>
<br/>
Same portion being visualized using a spherical shell approach.

There are about 7 useful mappings (such as the cube mapping and the spherical shell one shown), with some additional other ones that need some additional work.

## Why use banter?

Banter can be used in conjunction with other tools to quickly assess the structure of a given file, process or directory. Visualization provides a broad understanding of structure to begin analysis with more granular tools. This is particularly helpful when an understanding of general layout for a file, process or folder is lacking.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/s1.jpg"></img>

## Building Banter

A simple make will build banter from source. Note that the current version has been tested on macOS Catalina.
```
make
```
This will produce a binary in the **build** folder called **banter**.

## Using banter.

Banter can be targeted onto a file to provide visual analysis of the underlying structure. I also have an interest in targetting processes to visualize instructions loaded in memory, the stack, the heap, and all additionally loaded components in their respective memory mappings.
```

```

### Getting started

First, build banter from source.

```bash
make
```

Upon successfully building, you'll find banter in build/. To run it from it's current location, you can simply type:

```bash
./build/banter --target ~/Downloads/FileOfInterest.exe --stride 100000
```

This will bring up a GUI where the mouse can be used to rotate the object, the option key can be held along with moving the mouse to zoom, and right clicking in the window will display various options for adjusting how you view the file. Step size will change how fast you can page through a file (via the ',' and '.' keys), which can be held down to browse quickly.

Location mappings can be changed to adjust how the physical positioning of the data is laid out on the screen. The color mapping can also be helpful to emphasize additional aspects of the data as well.

## When to use banter.

Whenever a general understanding of structure is needed. This is useful for identifying what kind of data you are looking at if format has not been determined in advance. Various aspects in data such as entropy, structure, compression, and uniformity can be seen and used to determine file formats and architectures that a program was built for.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/s3.png"></img>

Since analysis is performed without knowledge of what is actually being represented Banter can highlight unknown patterns. This can be used to identify and characterize data of unknown type.

## How to install banter.

Workable versions will be published as releases under this github repo. Standard distributions will likely be provided for most mac/linux systems. Windows systems will be supported as well, but the real-time process analysis component may be absent.

## Why the name?

[Merriam Webster](https://www.merriam-webster.com/dictionary/banter) defines Banter as "to speak to or address in a witty and teasing manner", but the definition has nothing to do with _this_ Banter. I originally thought of the name as a way of making sense of the daily chatter of changing files, folders and processes on our systems every day. Much of this is akin to social norms, like witty chatter, but receives little attention to itself. The hope here is that this software will better illuminate  software so that the technically savvy (and the not so savvy) can see and understand what's happening on a grand scale in software.
