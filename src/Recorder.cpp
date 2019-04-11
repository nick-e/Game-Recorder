#include "Recorder.h"

gamerecorder::Recorder::Recorder() : connection(xcb_connect(nullptr, nullptr))
{
   int error = xcb_connection_has_error(connection);
   if (error != 0)
   {
      throw new FailedConnectionException(error);
   }
}

gamerecorder::Recorder::~Recorder()
{
   xcb_disconnect(this->connection);
}

const char *gamerecorder::Recorder::FailedConnectionException::what(void)
    const noexcept
{
   switch (error)
   {
   case XCB_CONN_ERROR:
      return "XCB_CONN_ERROR";
   case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
      return "XCB_CONN_CLOSED_EXT_NOTSUPPORTED";
   case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
      return "XCB_CONN_CLOSED_MEM_INSUFFICIENT";
   case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
      return "XCB_CONN_CLOSED_REQ_LEN_EXCEED";
   case XCB_CONN_CLOSED_PARSE_ERR:
      return "XCB_CONN_CLOSED_PARSE_ERR";
   case XCB_CONN_CLOSED_INVALID_SCREEN:
      return "XCB_CONN_CLOSED_INVALID_SCREEN";
   default:
      return "Unknown error";
   }
}

gamerecorder::Recorder::FailedConnectionException::FailedConnectionException(
    int error) : error(error)
{
}
