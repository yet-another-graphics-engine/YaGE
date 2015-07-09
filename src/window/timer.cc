#include "timer.h"
#include "window.h"
#include "message.h"
#include <algorithm>

namespace yage {
namespace window {

extern GAsyncQueue *msg_queue;
std::vector<Timer *> Timer::timers;
static const double kTimerInterval = 0.02;

Timer::Timer(double seconds) {
    iter_goal_ = static_cast<int>(seconds / kTimerInterval);
    paused_ = false;
    iter_count_ = 0;
    if (timers.size() == 0) {
        g_thread_new("YaGE timer",
                     reinterpret_cast<GThreadFunc>(timer_thread_func_),
                     this);
    } else {
        timers.push_back(this);
    }
}

Timer::~Timer() {
    timers.erase(std::remove(timers.begin(), timers.end(), this));
}

void Timer::pause(void) {
    paused_ = true;
}

void Timer::resume(void) {
    paused_ = false;
}

void Timer::stop(void) {
    paused_ = true;
    iter_count_ = 0;
}

double Timer::get_time_elapsed(void) {
    return iter_count_ * kTimerInterval;
}

gpointer Timer::timer_thread_func_(Timer *first_timer) {
    timers.push_back(first_timer);
    while (true) {
        g_usleep(static_cast<gulong>(kTimerInterval * G_USEC_PER_SEC));
        if (timers.size() > 0) {
            for (std::vector<Timer *>::const_iterator timer = timers.begin();
                 timer < timers.end();
                 timer++) {
                if (!((*timer)->paused_)) {
                    (*timer)->iter_count_++;

                    Message &msg = *(new Message);
                    msg.type = msg.type_timer;
                    msg.timer.seconds = (*timer)->iter_count_ * kTimerInterval;

                    if ((*timer)->iter_count_ == (*timer)->iter_goal_) {
                        msg.timer.type = msg.timer.type_finished;
                        (*timer)->paused_ = true;
                    } else {
                        msg.timer.type = msg.timer.type_running;
                    }
                    g_async_queue_push(msg_queue, &msg);
                }
            }
        } else {
            break;
        }
    }
    return NULL;
}

}
}