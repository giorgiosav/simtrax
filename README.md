## In order to install (Mac OSX)

**NB: These instructions may be incomplete**

Pre-requisites:
* Boost - Make sure you have Homebrew installed and type `brew install boost` in the terminal.
* Clang++

1. Download the files in a folder called "simtrax"
2. Go to `simtrax/llvm-trax` in the terminal and run `./setup.sh`
(this will take 20-30 minutes and will print lots of statements/warnings).
3. Go to the `sim` directory (`../sim`) and run `make` in the terminal. This
will also print lots of statements and warnings, but should take much less than the
previous step.
