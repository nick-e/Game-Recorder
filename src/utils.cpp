#include "utils.h"

std::string gamerecorder::xcb_error_to_string(int error)
{
   switch (error)
   {
   default:
      return "Unknown error (" + std::to_string(error) + ")";
   }
}
