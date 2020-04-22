#include "Config.h"

bool Config::setLimit(Limit limit) {
  nowLimit = limit;
  return output->setLimit(limit);
}
Limit Config::getLimit() { return nowLimit; }