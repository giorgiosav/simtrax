## In order to install (Mac OSX)

**NB: These instructions may be incomplete**

Pre-requisites:
* Boost - Make sure you have Homebrew installed and type `brew install boost` in the terminal.
* Clang++

1. Download the files in a folder called "simtrax"
2. Go to `simtrax/llvm-trax` in the terminal and run `./setup.sh`
(this will take 20-30 minutes and __will fail__).
3. Open `llvm-trax/llvm-3.5.0.src/include/llvm/ADT/IntrusiveRefCntPtr.h` and around
line 137 make sure you have the following:
`class IntrusiveRefCntPtr {
    public:
    T* Obj;`
4. In `llvm-trax/build` run `make` in the terminal. This will finish the build from step 2.
__Do not run `setup.sh` again__, as this will override the changes made to `IntrusiveRefCntPtr.h`.
5. Go to the `sim` directory (`../sim`) and run `make` in the terminal.

To set up the example files:
1. Go to `samples/src` and choose an example file (ex: gradient).
2. Enter the directory and run `make` in the terminal.
3. Run `./run_rt` in the terminal. This should create a TRaX assembly file
called `rt-llvm.s`.
