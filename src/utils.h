#ifndef GAMERECORDER_UTILS_H
#define GAMERECORDER_UTILS_H

#include <xcb/xcb.h>
#include <string>

namespace gamerecorder
{
std::string xcb_error_to_string(int error);
}

#endif
