#include "unix.h"

namespace yage {
namespace audio {

gboolean UnixPlayer::bus_call(GstBus *bus, GstMessage *msg, void *user_data)
{
  return false;
}

UnixPlayer::~UnixPlayer() {
	gst_element_set_state(pipeline_, GST_STATE_NULL);
	gst_object_unref(GST_OBJECT(pipeline_));
}

bool UnixPlayer::play() {
  gst_element_set_state(pipeline_, GST_STATE_PLAYING);
  auto state = gst_element_get_state(pipeline_, nullptr, nullptr,
                                     GST_CLOCK_TIME_NONE);
  return state != GST_STATE_CHANGE_FAILURE;
}

void UnixPlayer::pause() {
  gst_element_set_state(pipeline_, GST_STATE_PAUSED);
}

void UnixPlayer::stop() {
  gst_element_seek(pipeline_, 1.0, GST_FORMAT_DEFAULT, GST_SEEK_FLAG_NONE,
                   GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_END, 0);
  gst_element_set_state(pipeline_, GST_STATE_PAUSED);
}

bool UnixPlayer::is_playing() {
  GstState state;
  auto ret = gst_element_get_state(pipeline_, &state, nullptr, 0);
  return state == GST_STATE_PLAYING;
}

UnixPlayer::UnixPlayer(const std::string &url) : Player() {
  url_ = url;

  gst_init(nullptr, nullptr);
  pipeline_ = gst_element_factory_make("playbin", "player");
  bus_ = gst_pipeline_get_bus(GST_PIPELINE(pipeline_));
  gst_bus_add_watch(bus_, bus_call, this);
  gst_object_unref(bus_);

  g_object_set(G_OBJECT(pipeline_), "uri", url_.c_str(), nullptr);
}

}
}
