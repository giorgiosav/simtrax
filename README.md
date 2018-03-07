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
5. Go to `simtrax/sim` and run `make` in the terminal.

To set up the example files:
1. Go to `samples/src` and choose an example file (ex: gradient).
2. Enter the directory and run `make` in the terminal.
3. Run `./run_rt` in the terminal. This should create a TRaX assembly file
called `rt-llvm.s`.


The arguments you might eventually care about:

****These ones configure the resources on the chip****

--num-thread-procs  (threads per TM)

--num-cores (number of TMs)

--num-L2s (number of L2 caches. Each L2 has --num-cores TMs connected to it)

--config-file (specifies execution units and cache sizes)

--num-icaches (number of instruction caches per TM)

--num-icache-banks (number of banks per icache)

--dcache-params (specifies simulated area and energy for various data cache capacity/bank configurations. Probably best to use default here unless you are using weird caches. Leave this argument out for default)

--icache-params (similar to dcache-parame but for the icaches)

****These ones configure the memory****

--usimm-config (specify a usimm config file - best to leave this argument out unless you are changing the DRAM configuration)

--vi-file (specifies energy and latency parameters for DRAM - best to leave this argument out unless you are changing the DRAM configuration)

****These ones configure simtrax output and/or debugging****

--issue-verbosity (displays per-cycle information. very verbose, almost always want to leave this out unless debugging)

--print-instructions (prints the assembled form of the instructions to be run)

--print-symbols (prints the assembly symbol and register names and their values/addresses)


| Data | Location in Memory | Meaning |
|:---------|:-----------------------|:------------|
| eye point | camera_ptr + [0..2] | camera location |
| corner vector | camera_ptr + [3..5] | left, bottom corner of the image plane |
| across vector | camera_ptr + [6..8] | normalized horizontal camera vector (u, or right) scaled by film image plane width |
| up vector | camera_ptr + [9..11] | normalized vertical camera vector (v, or up) scaled by film image plane height |
| (unit) gaze vector | camera_ptr + [12..14] | normalized gaze direction (w, or lookat) |
| U | camera_ptr + [15..17] | u vector at the film plane distance |
| V | camera_ptr + [18..20] | v vector at the film plane distance |
| (unit) U | camera_ptr + [21..23] | | (unit) V | camera_ptr + [24..26] |
| aperture radius | camera_ptr + 27 | | left | camera_ptr + 28 |
| right | camera_ptr + 29 |
| bottom | camera_ptr + 30 |
| top | camera_ptr + 31 |
| near clip (rasterizer) | camera_ptr + 32 |
| far clip (rasterizer) | camera_ptr + 33 |
