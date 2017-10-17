# An Open Source PageRank Implementationin C

This project provides an open source PageRank implementation. The
implementation is a straightforward application of the algorithm
description given in the American Mathematical Society's Feature
Column [How Google Finds Your Needle in the Web's
Haystack](http://www.ams.org/samplings/feature-column/fcarc-pagerank),
by David Austing. It can handle very big hyperlink graphs with
millions of vertices and arcs.

# Building

The project is written in standard C and can be built by running:

    make

# Usage

pagerank is invoked by

    ./pagerank -I [number of iterations] -A [alpha] network_file.net

where options may be:

* -A: Alpha parameter (see Google formula).

* -I: Number of iterations.

where in put file is in the follow format (see example.net):

    Number of pages
    Link 1
    Link 2
    ...
    
    

# Testing

Unit tests are available in test_main.c
