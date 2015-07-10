#include "../main.h"
#include "unix.h"

namespace yage {
namespace audio {

gboolean UnixPlayer::bus_callback(GstBus *bus,
                                  GstMessage *msg,
                                  UnixPlayer *this_)
{
  switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug_info;

      gst_message_parse_error(msg, &err, &debug_info);
      g_printerr("Failed to play %s:[%s] %s\n",
                 this_->url_.c_str(), GST_OBJECT_NAME(msg->src), err->message);
      g_printerr("Debug info: %s\n", debug_info ? debug_info : "none");
      g_clear_error(&err);
      g_free(debug_info);
      break;
    }

    case GST_MESSAGE_EOS:
      this_->is_playing_ = false;
      break;

    default:
      break;
  }

  return TRUE; // keep receiving message
}

UnixPlayer::~UnixPlayer() {
  gst_object_unref(bus_);
  gst_element_set_state(pipeline_, GST_STATE_NULL);
  gst_object_unref(GST_OBJECT(pipeline_));
}

bool UnixPlayer::play() {
  GstStateChangeReturn state = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
  is_playing_ = (state != GST_STATE_CHANGE_FAILURE);
  return is_playing_;
}

void UnixPlayer::pause() {
  gst_element_set_state(pipeline_, GST_STATE_PAUSED);
}

void UnixPlayer::stop() {
  gst_element_seek(pipeline_, 1.0, GST_FORMAT_DEFAULT, GST_SEEK_FLAG_NONE,
                   GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_END, 0);
  gst_element_set_state(pipeline_, GST_STATE_READY);
  is_playing_ = false;
}

bool UnixPlayer::is_playing() {
  return is_playing_;
}

UnixPlayer::UnixPlayer(const std::string &url) : Player() {
  url_ = url;
  is_playing_ = false;

  gst_init(&yage::argc, &yage::argv);
  pipeline_ = gst_element_factory_make("playbin2", "player");

  enum {
    GST_PLAY_FLAG_VIDEO         = (1 << 0),
    GST_PLAY_FLAG_AUDIO         = (1 << 1),
    GST_PLAY_FLAG_TEXT          = (1 << 2)
  };
  g_object_set (pipeline_, "flags", GST_PLAY_FLAG_AUDIO, NULL);

  bus_ = gst_pipeline_get_bus(GST_PIPELINE(pipeline_));
  gst_bus_add_watch(bus_, reinterpret_cast<GstBusFunc>(bus_callback), this);

  g_object_set(G_OBJECT(pipeline_), "uri", url_.c_str(), NULL);
}

void UnixPlayer::seek(double seconds) {
}

}
}
