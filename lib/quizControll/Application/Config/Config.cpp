#include "Config.h"

Config::Config(IConfigOutput& output) : output(output) {}
bool Config::setLimit(Limit limit) {
  nowLimit = limit;
  return output.setLimit(limit);
}
Limit Config::getLimit() { return nowLimit; }