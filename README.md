# Baby-C

A toy compiler for a toy language

---

### Building

To build in release mode, type

    make

or

    make release

To build in debug mode (does not work on Athena because of the `-fsanitize=address` flag)

    make debug

The debug build will print the contents of the abstract syntax tree, and check for memory leaks.

### Testing

To load the test scripts:

    . ./setup.sh

You can then use

    t 1
    t 2
    t 3
    # etc.

to check against the various test cases, or

    ta

to run all of the tests (note that it errors on test 7, so test 8 must be run manually).
