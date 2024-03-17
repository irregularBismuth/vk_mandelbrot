#include "utils.h"

namespace veng {

  bool streq(gsl::czstring left, gsl::czstring right) {
    return std::strcmp(left,right)==0;
  }

}
