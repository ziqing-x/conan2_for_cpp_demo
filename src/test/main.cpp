#include "doctest.h"

int main(int argc, char **argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.run();
    return context.shouldExit();
}