#include "graphics.h"


Graphics::Graphics(gsl::not_null<Window*> window) : window_(window) {
   VkApplicationInfo app_info{}; 
}

