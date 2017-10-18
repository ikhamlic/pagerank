# An Open Source PageRank Implementation in C

An open source PageRank implementation in C, implemented as described in David Austing’s How Google Finds Your Needle in the Web's Haystack. The algorithm handles large hyperlink graphs with millions of vertices and arcs.

# Building

The project is written in standard C and can be built by running:

    make

# Usage

pagerank is invoked by

    ./pagerank -I [number of iterations] -A [alpha] network_file.net

where options may be:

* -A: Alpha parameter (see Google formula).

* -I: Number of iterations.

where input file is in the following format (see example.net):

    Number of pages
    Link 1
    Link 2
    ...
    
    

# Testing

Unit tests are available in test_main.c
