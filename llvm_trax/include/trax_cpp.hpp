#ifndef TRAX_CPP_HPP
#define TRAX_CPP_HPP

#include <string>

// Memory ops
int loadi( int base, int offset = 0 );
float loadf( int base, int offset = 0 );
void storei( int value, int base, int offset = 0 );
void storef( float value, int base, int offset = 0 );
int trax_getid( int value );

// Arithmetic
int atomicinc( int location );
int global_reg_read( int location );
float min( float left, float right );
float max( float left, float right );
float invsqrt( float value );
float trax_rand();

// Stream writes
void start_stream_write( int stream_id );
void stream_writei( int value );
void stream_writef( float value );
void end_stream_write();

// Stream reads
int start_stream_read();
int stream_readi();
float stream_readf();
void end_stream_read();

int stream_size( int stream_id );
int stream_schedule( int schedule_id );
void set_stream_read_id( int stream_id );

// Debug
void profile( int prof_id );
int loadl1( int base, int offset = 0 );
void trax_printi(int value);
void trax_printf( float value );

typedef struct runrtParams_tt runrtParams_t;		// temp -> see below
void trax_setup( runrtParams_t &parsedParams );
void trax_cleanup( runrtParams_t &parsedParams );
void barrier( int reg_num = 5 );
float trax_noise( float x, float y, float z );


// some of the pre-processor defines
#ifndef WIDTH
#  define WIDTH 512
#endif
#ifndef HEIGHT
#  define HEIGHT 512
#endif
#ifndef VIEWFILE
#  define VIEWFILE "views/cornell_obj.view"
#endif
#ifndef MODELFILE
#  define MODELFILE "test_models/cornell/CornellBox.obj"
#endif
#ifndef LIGHTFILE
#  define LIGHTFILE "lights/cornell.light"
#endif
#ifndef MEMORYFILE
#  define MEMORYFILE "memory.mem"
#endif
#ifndef NUMSAMPLES
#  define NUMSAMPLES 1
#endif
#ifndef RAYDEPTH
#  define RAYDEPTH 1
#endif


// Main function (user defined)
void trax_main();

// playing with threads
// returns success of the operation ( if false, call render function directly )
bool trax_start_render_threads( void* (*renderFunc)(void*), const int &numThreads=1 );
void * trax_mainPThreads( void * dummyPtr = 0 );


// parameters worth parsing
typedef struct runrtParams_tt{
  bool read_from_mem_file;
  bool triangles_store_edges;
  unsigned int num_render_threads;
  unsigned int num_samples_per_pixel;
  unsigned int ray_depth;
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bvh_dot_depth;
  unsigned int num_global_registers;
  unsigned int subtree_size;
  int custom_mem_loader;
  std::string mem_file_name;
  std::string view_file_name;
  std::string model_file_name;
  std::string light_file_name;
  
  // defaults
  runrtParams_tt() : read_from_mem_file( false ), triangles_store_edges( false ),
		     num_render_threads( 4 ), num_samples_per_pixel( NUMSAMPLES ), ray_depth( RAYDEPTH ),
		     img_height( HEIGHT ), img_width( WIDTH ), bvh_dot_depth( 0 ), num_global_registers( 8 ),
		     subtree_size( 0 ), custom_mem_loader( 0 ), mem_file_name( MEMORYFILE ), view_file_name( VIEWFILE ), 
		     model_file_name( MODELFILE ), light_file_name( LIGHTFILE )
  {}
} runrtParams_t;


// options parser
void programOptParser( runrtParams_t &params, int argc, char* argv[] );

#endif