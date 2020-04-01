#include "Config.h"

bool Config::setLimit(Limit limit) { return output->setLimit(limit); }
bool Config::softReset() { return output->softReset(); }