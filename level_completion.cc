#include <stdio.h>

#include <stdexcept>
#include <vector>

#include "level_completion.hh"

using namespace std;

vector<level_completion> load_level_completion_state(const char* filename) {
  FILE* f = fopen(filename, "rb");
  if (!f)
    return vector<level_completion>();
  fseek(f, 0, SEEK_END);
  uint64_t num = ftell(f) / sizeof(level_completion);
  fseek(f, 0, SEEK_SET);

  vector<level_completion> lc(num);
  fread(lc.data(), lc.size(), sizeof(level_completion), f);
  fclose(f);

  return lc;
}

void save_level_completion_state(const char* filename, const vector<level_completion>& lc) {
  FILE* f = fopen(filename, "wb");
  if (!f)
    throw runtime_error("can\'t open file");

  fwrite(lc.data(), lc.size(), sizeof(level_completion), f);
  fclose(f);
}
