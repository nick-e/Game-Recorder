#include "Recorder.h"

std::vector<std::string> gamerecorder::Recorder::get_all_window_titles()
{
   xcb_get_property_cookie_t cookie = xcb_get_property(this->connection,
                                                       false,
                                                       this->screen->root,
                                                       static_cast<xcb_atom_t>(
                                                           Atoms::NET_CLIENT_LIST),
                                                       XCB_GET_PROPERTY_TYPE_ANY,
                                                       0,
                                                       128);

   xcb_generic_error_t *error;
   xcb_get_property_reply_t *windowListReply = xcb_get_property_reply(connection,
                                                                      cookie,
                                                                      &error);
   if (error != nullptr)
   {
      std::string errorStr = xcb_error_to_string(error->error_code);
      free(error);
      throw new std::runtime_error(
          "Failed to handles to all windows: " + errorStr);
   }

   /* get_property_value() returns the number of elements multiplied by the
    * size of each element. Each element has a size of 4 bytes. This mean
    * dividing the returned value by 4 will result in the total number of
    * elements.
    */
   int windowCount = std::max(0, xcb_get_property_value_length(windowListReply) / 4);
   std::vector<std::string> titles(windowCount);
   xcb_window_t *windows = static_cast<xcb_window_t *>(
       xcb_get_property_value(windowListReply));
   for (int i = 0; i < windowCount; ++i)
   {
      cookie = xcb_get_property(this->connection,
                                false,
                                windows[i],
                                static_cast<xcb_atom_t>(
                                    Atoms::NET_WM_VISIBLE_NAME),
                                XCB_GET_PROPERTY_TYPE_ANY,
                                0,
                                1024);
      xcb_get_property_reply_t *windowTitleReply = xcb_get_property_reply(
          connection,
          cookie,
          &error);
      if (error != nullptr)
      {
         std::string errorStr = xcb_error_to_string(error->error_code);
         free(error);
         free(windowListReply);
         throw new std::runtime_error(
             "Failed to get the name of a window: " + errorStr);
      }
      int titleSize = xcb_get_property_value_length(windowTitleReply);
      const char *title = static_cast<const char*>(
         xcb_get_property_value(windowTitleReply));
      titles.emplace_back(title, titleSize);
      free(windowTitleReply);
   }

   free(windowListReply);

   return titles;
}

gamerecorder::Recorder::Recorder()
{
   // Establish connection to X server
   connection = xcb_connect(nullptr, nullptr);
   int error = xcb_connection_has_error(connection);
   if (error != 0)
   {
      throw new FailedConnectionException(error);
   }

   // Get the default screen of the connection
   screen = xcb_setup_roots_iterator(xcb_get_setup(this->connection)).data;
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
