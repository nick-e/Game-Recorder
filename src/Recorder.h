#ifndef GAMERECORDER_RECORDER_H
#define GAMERECORDER_RECORDER_H

#include <xcb/xcb.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"

namespace gamerecorder
{
// Contains the codes for X11's atoms
enum class Atoms
{
   NET_WM_VISIBLE_NAME = 413,
   NET_CLIENT_LIST = 424
};

class Recorder
{
 public:
   struct FailedConnectionException : public std::exception
   {
      const int error;

      const char *what(void) const noexcept;

      FailedConnectionException(int error);
   };

   std::vector<std::string> get_all_window_titles();

   Recorder();
   ~Recorder();

 private:
   xcb_connection_t *connection = nullptr;
   xcb_screen_t *screen;
};
} // namespace gamerecorder

#endif
