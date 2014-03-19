#ifndef TRAX_TRAX_H
#define TRAX_TRAX_H


// Trax Intrinsics
extern "C"
{
  // Global Memory
  extern int loadi( int base, int offset = 0 ) asm("llvm.trax.loadi");
  extern float loadf( int base, int offset = 0 ) asm("llvm.trax.loadf");
  extern void storei( int value, int base, int offset = 0 ) asm("llvm.trax.storei");
  extern void storef( float value, int base, int offset = 0 ) asm("llvm.trax.storef");
  extern int trax_getid( int value ) asm("llvm.trax.getid");

  // Arithmetic
  extern int atomicinc( int location ) asm("llvm.trax.atominc");
  extern int global_reg_read( int location ) asm("llvm.trax.globalrrd");
  extern float min( float left, float right ) asm("llvm.trax.min");
  extern float max( float left, float right ) asm("llvm.trax.max");
  extern float invsqrt( float value ) asm("llvm.trax.invsqrt");
  // Random
  extern float trax_rand( ) asm("llvm.trax.rand");
  // Barrier
  extern int trax_inc_reset( int reg_num ) asm("llvm.trax.increset");
  extern void trax_barrier( int reg_num ) asm("llvm.trax.barrier");
  extern void trax_semacq( int reg_num ) asm("llvm.trax.semacq");
  extern void trax_semrel( int reg_num ) asm("llvm.trax.semrel");
  // Noise
  extern void trax_write_srf( float reg1, float reg2, float reg3 ) asm("llvm.trax.writesrf");
  extern void trax_write_sri( int reg1, int reg2, int reg3 ) asm("llvm.trax.writesri");
  extern float trax_callnoise( ) asm("llvm.trax.callnoise");
  
  // Streams
  // Stream writes
  extern void start_stream_write( int stream_id ) asm("llvm.trax.startsw");
  extern void stream_writei( int value ) asm("llvm.trax.streamwi");
  extern void stream_writef( float value ) asm("llvm.trax.streamwf");
  extern void end_stream_write() asm("llvm.trax.endsw");
  // Stream reads
  extern int start_stream_read() asm("llvm.trax.startsr");
  extern int stream_readi() asm("llvm.trax.streamri");
  extern float stream_readf() asm("llvm.trax.streamrf");
  extern void end_stream_read() asm("llvm.trax.endsr");
  // Stream scheduling
  extern int stream_size( int stream_id ) asm("llvm.trax.streamsize");
  extern int stream_schedule( int schedule_id ) asm("llvm.trax.streamschedule");
  extern void set_stream_read_id( int stream_id ) asm("llvm.trax.setstreamid");

  // Debug
  extern void profile( int prof_id ) asm("llvm.trax.profile");
  extern int loadl1( int base, int offset = 0 )asm("llvm.trax.loadl1");
  //extern int loadl2( int base, int offset = 0 )asm("llvm.trax.loadl2");
  extern void trax_printi(int value) asm("llvm.trax.printi");      // print integer
  extern void trax_printf( float value ) asm("llvm.trax.printf");  // print float (unfortunately this uses the "printf" name)
  extern void trax_printformat(int string_addr) asm("llvm.trax.printformat"); // 'equivalent' to stdio::printf

}

// simplified printf for trax
extern int printf ( const char * format, ... );


inline void barrier( int reg_num = 5 ) {
  trax_inc_reset( reg_num );
  trax_barrier( reg_num );
}

inline float trax_noise( float x, float y, float z ) {
  trax_write_srf(x,y,z);
  return trax_callnoise();
}

// main function the user must define instead of "main"
void trax_main()__attribute__((noinline));

// the main function (in trax_trax.cpp just calls trax_main())
int main();

#endif
