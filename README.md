TRAMPOLINE ~~MATHS~~ EXAMPLES
=

A functional example of how to put executable code into "demand paged" banks,
letting you break up your application into discrete chunks and therefore have
much bigger overall binaries with z88dk.

Please note this is not the only way to do things, this example has been made to
serve two-and-abit purposes:

1. A __pure C__ method, not requiring users to know, or use, any assembler; *with*

2. enough flexibility to be able to call just about anything using pointers for larger data-stuctures; *and*

abit. Show how both NEX and DOT commands can use virtually identical methodologies to achieve the same thing.

This **CONTRIVED** example has its main logic in Bank #43, the code in Bank 43 then calls various other routines in banks 44, 45, 46, and 47 via the execfar* trampolines to produce a final value.  This isn't something that anyone sane would do in a real app, but it does show how one can use a few simple functions to freely move around the codebase executing functions from anywhere within the code.
