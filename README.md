# banter
A software tool for applied visualization and structural analysis of data.

_** This version of banter is an in progress C rework of an existing program that is written in Obj-C. Images and other details are pulled from the existing program (until this variant is complete)._

## What is banter?

Banter is a tool for visualizing data independent of underlying structure. This allow for visual identification, classificiation and comparison of known and unknown structures by their visual signature.

The following is a low quality gif, but it demonstrates a visual analysis approach to looking at a php 7.3.11 binary on OSX.
<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b1.gif"></img>
A brief demonstration of banter browsing through the initial part of the binary.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b2.gif"></img>
A rotation around a portion that is shown to have predominantly ascii characters, evidenced by the signature white blocks in one specific area of the cube.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b3.gif"></img>
Visualization of a structurally significant area within the later part of the PHP binary. Notice the change from ascii to a large block of data (possibly compressed), being followed by what appears to be a regular table structure of some sort.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/b4.gif"></img>
Same portion being visualized using a spherical shell approach.

There are about 7 useful mappings (such as the cube mapping and the spherical shell one shown), with some additional other ones that need some additional work.

## Why use banter?

Banter can be used in conjunction with other tools to quickly assess the structure of a given file, process or directory. Visualization provides a broad understanding of structure to begin analysis with more granular tools. This is particularly helpful when an understanding of general layout for a file, process or folder is lacking.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/s1.jpg"></img>

## How to use banter.

Banter can be targeted onto a file, process or folder to provide visual analysis of the underlying structure. For this variant the UI is still pending.

### Getting started

First, build banter from source.

```bash
make
```

Upon successfully building, you'll find banter in build/. To run it, you can simply type:

```bash
./banter
```

To get started, here's an example of reading from a file (this file in the example).

```bash
./banter README.md
```

## When to use banter.

Whenever a general understanding of structure is needed. This is useful for identifying what kind of data you are looking at if format has not been determined in advance. Various aspects in data such as entropy, structure, compression, and uniformity can be seen and used to determine file formats and architectures that a program was built for.

<img width="500" src="https://github.com/montymxb/banter/blob/master/images/s3.png"></img>

Since analysis is performed without knowledge of what is actually being represented Banter can highlight unknown patterns. This can be used to identify and characterize data of unknown type.

## How to install banter.

Workable versions will be published as releases under this github repo. Standard distributions will likely be provided for most mac/linux systems. Windows systems will be supported as well, but the real-time process analysis component may be absent.

## Why the name?

[Merriam Webster](https://www.merriam-webster.com/dictionary/banter) defines Banter as "to speak to or address in a witty and teasing manner", but the definition has nothing to do with _this_ Banter. I originally thought of the name as a way of making sense of the daily chatter of changing files, folders and processes on our systems every day. Much of this is akin to social norms, like witty chatter, but receives little attention to itself. The hope here is that this software will better illuminate  software so that the technically savvy (and the not so savvy) can see and understand what's happening on a grand scale in software.
