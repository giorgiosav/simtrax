#ifndef __SIMHWRT_READ_CONFIG_H__
#define __SIMHWRT_READ_CONFIG_H__

#include <vector>
#include <string>

class HardwareModule;
class FunctionalUnit;
class TraxCore;
class L2Cache;
class MainMemory;

class ReadConfig {
public:
  ReadConfig(const char* input_file, const char* _dcache_params_file,
	     L2Cache** L2s, size_t num_L2s, MainMemory*& mem, 
	     double& size_estimate, bool disable_usimm,
	     bool memory_trace, bool l1_off, bool l2_off,
	     bool l1_read_copy);
  
  void LoadConfig(L2Cache* L2, double &size_estimate);

  const char* input_file;
  const char* dcache_params_file;
  TraxCore* current_core;
  bool memory_trace;
  bool l1_off, l2_off, l1_read_copy;
};

int ReadCacheParams(const char* file, int capacityBytes, int numBanks, int lineSizeBytes, float& area, float& energy, bool is_data_cache);

#endif // __SIMHWRT_READ_CONFIG_H__
