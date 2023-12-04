# README

This repository contains source code and binaries for four early, no-longer-actively-supported,
historical simulators:

- dos-madm (1989)
- windows-madm (1995)
- java-ssem (1998)
- dos-edsac (1990)

The first three are simulators are for the prototype machine built at Manchester, sometimes called the “Baby” Mark I, but now officially known as the “Small Scale Experimental Machine” (SSEM).  “MADM” stands for “Manchester Automatic Digital Machine.”  The last is a simulator for the Cambridge EDSAC.

## `dos-madm`

This simulator was written on an IBM XT clone using 320x200 color graphics mode. The machine-dependent parts are carefully marked as such, and is therefore intended to be somewhat portable.  The program was originally written without displays for the A and C lines.  That version took 58 minutes to run the Kilburn Highest Factor program (the SSEM ran this program in 52 minutes in 1948).

## `windows-madm`

This simulator was written to explore Borland's Pascal-based Delphi integrated development environment.  The simplicity of the SSEM (32 words of 32-bits each; 7 op codes) makes it ideal for getting up to speed with a new language or programming environment (particularly those involving graphical user interfaces).

The [Lazarus](https://www.lazarus-ide.org/) project provides a free, Delphi-compatible platform for modern operating systems.  Lazarus installations include tools for converting Delphi projects.

## `java-ssem`

The included `README` file describes this project in detail.  The [`noweb`](https://www.cs.tufts.edu/~nr/noweb/) system for literate programming is still supported, but the Pretzel system, used for typesetting the code chunks in an Algol-like style, is no longer available (but not absolutely necessary).  The enclosed `ssem.pdf` document documents and describes the Java source code.

The program was compiled using a Java v1.1 compiler.  Current versions of Java have changed significantly since then, and the code can no longer be compiled by current compilers.  However, the `.class` files still execute properly.  If you are interested in updating the code, but not interested in literate programming, you can modify the `ssem.java` file and ignore the `ssem.nw` file.  I would appreciate [hearing from](mailto:leew@kean.edu) anyone who succeeds in updating the Java source.

## `dos-edsac`

This simulator provides a text-only simulator for the EDSAC.  It was written on DOS, but designed as a Unix-style pipeline.  The three components work together to emulate the complete EDSAC system.  The first component (`punch`) converts ASCII input into EDSAC perforator codes.  The second (`edsac`) reads the resulting output as input and emulates its execution as an EDSAC program, producing EDSAC teleprinter codes as output.  The third (`tprint`) translates EDSAC teleprinter input into ASCII ouput.  The command line
```
    punch program.e | edsac | tprint
```
reads and executes an EDSAC program contained in the text file `program.e`.  The files `PUNCHMAN.TXT`, `EDSACMAN.TXT`, and `TPRINTMAN.TXT` describe these programs in Unix “manpage” sty

The code works on both DOS and Unix-like systems.  It is written in pre-ANSI/ISO style, using K&R-style function parameter declarations.
An updated version, supporting Unicode I/O, and conforming to the C89 standard, is available at the [Computer Conservation Society website](https://www.computerconservationsociety.org/emu/edsac/index.htm).

## Aztec C

The DOS versions were written using [Aztec C](https://www.aztecmuseum.ca/compilers.htm#msdos) v4.1.  The C code predates the ANSI standard somewhat, using K&R-style function parameter declarations.

The makefiles are  compatible with the “standard” Unix `make` utility, but do not work with the `MAKE.EXE` provided with the compilers available at [www.aztecmuseum.ca](https://www.aztecmuseum.ca).  The `proto` utility is not provided with v5.2a, but the `proto.h` file does not need to be rebuilt if no new functions are added.
The source code for the graphics routines used in the DOS SSEM simulator is included with the v5.2a download.
using K&R-style function parameter declarations.

