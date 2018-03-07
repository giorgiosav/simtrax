This program was developed by Josef Spjut and Daniel Kopta. I am only
forking it for personal reference.

Documentation from the authors: https://code.google.com/archive/p/simtrax/wikis

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


## Simulation

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

## Programming
### Camera

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


### Accessing Pre-Loaded Global Constants

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| int GetXRes() | Returns image width|Set by simulator argument: --width|
| float GetInvXRes() | Returns inverse image width|Affected by simulator argument: --width|
| int GetYRes() | Returns image height|Set by simulator argument: --height|
| float GetInvYRes() | Returns inverse image height|Affected by simulator argument: --height|
| int GetFrameBuffer() | Returns the global address of the frame buffer| |Ray Tracer Specific Global Constants

Depending on simulator arguments, the system may pre-load portions of global memory with ray tracing data structures. The locations of these structures are accessed with the following:

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| int GetBVH() | Returns the global address of the root node of the BVH|Affected by simulator parameter: --model|
| int GetMaterials() | Returns the global address of the materials array|Affected by simulator parameter: --model|
| int GetCamera() | Returns the global address of the camera data|Affected by simulator parameter: --view-file (see Viewfiles)|
| int GetLight() | Returns the global address of the light data|Affected by simulator parameter: --light-file|
| int GetStartTriangles() | Returns the global address of the triangles array|Affected by simulator parameter: --model|
| int GetNumTriangles() | Returns the number of triangles in the model|Affected by simulator parameter: --model|
Thread Information

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| int GetThreadID() | Returns the thread's ID within its TM|Affected by simulator parameters: --num-thread-procs, --num-TMs, --num-l2s|
| int GetCoreID() | Returns the thread's TM ID|Affected by simulator parameters: --num-thread-procs, --num-TMs, --num-l2s|
| int GetL2ID() | Returns the thread's L2 ID|Affected by simulator parameters: --num-thread-procs, --num-TMs, --num-l2s|

### Accessing Global Memory

TRaX has two memory spaces: thread-local, and global (see Programming#TRaX_memory_system). All global memory access is done explicitly with the below base functions. It is recommended to build on these with your own helper functions for loading/storing data structures.

Note: in the functions below, offset must be an integer literal (can not be a variable name)

| Function | Description |
|:-------------|:----------------|
| int loadi( int base, int offset = 0 ) | Loads the word in global memory at address base + offset|
| float loadf( int base, int offset = 0 ) | Loads the word in global memory at address base + offset|
| void storei( int value, int base, int offset = 0 ) | Stores value to global memory at address base + offset|
| void storef( float value, int base, int offset = 0 ) | Stores value to global memory at address base + offset|

### Arithmetic

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| float min( float left, float right ) | Returns the smaller of the two arguments | Implemented as a machine instruction |
| float max( float left, float right ) | Returns the larger of the two arguments | Implemented as a machine instruction |
| float invsqrt( float value ) | Returns 1/sqrt(value) | Implemented as a machine instruction |
| float trax_rand( ) | Returns a random number between 0 and 1 | Implemented as a machine instruction |


### Thread Synchronization

These functions all use global registers, accessed atomically, to implement thread synchronization. Functions that modify global registers must be carefully used in a way that they do not interfere with each other. For example, using the same global register as a counter (atomicinc) and a semaphore at the same time will have undesired results.

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| int atomicinc( int glbID ) | Atomically increments global register glbID |Returns previous value (post increment)|
| int barrier( int glbID ) | Uses global register glbID to implement a system-wide barrier (block until all threads have reached it). Return value is unused. | Global register glbID should not be used by any other functions (including other barriers)|
| void trax_semacq( int glbID ) | Acquires semaphore on global register glbID. Blocks until successful | Global register glbID should not be used by any other non-semaphore functions|
| void trax_semrel( int glbID ) | Releases semaphore on global register glbID. | Global register glbID should not be used by any other non-semaphore functions|


### Debug

| Function | Description | Notes |
|:-------------|:----------------|:----------|
| void trax_printi( int value ) | Print an integer value to the terminal | Will print the full contents of the register containing the value |
| void trax_printf( float value ) | Print a floating point value to the terminal | Will print the full contents of the register containing the value |
| int printf ( const char * format, ... ) | Similar to stdio's printf | Supports %d, %c, %f, %u only. Implemented as a syscall instruction. Full processing required to parse the format string is not simulated (happens with a single instruction) |
