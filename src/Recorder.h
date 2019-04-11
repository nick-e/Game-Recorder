#ifndef GAMERECORDER_RECORDER_H
#define GAMERECORDER_RECORDER_H

#include <xcb/xcb.h>
#include <stdexcept>

namespace gamerecorder
{
class Recorder
{
 public:
   struct FailedConnectionException : public std::exception
   {
      const int error;

      const char *what(void) const noexcept;

      FailedConnectionException(int error);
   };

   Recorder();
   ~Recorder();

 private:
   xcb_connection_t *connection = nullptr;
};
} // namespace gamerecorder

#endif
