#ifndef YAGE_TIMER_H
#define YAGE_TIMER_H
#include "window.h"
#include <vector>

namespace yage {
namespace window {

class Timer {
public:
    Timer(double seconds);
    ~Timer();
    void pause(void);
    void resume(void);
    void stop(void);
    double get_time_elapsed(void);
private:
    int iter_goal_;
    int iter_count_;
    bool paused_;
    static gpointer timer_thread_func_(Timer *first_timer);
    static std::vector<Timer *> timers;
};

}
}

#endif //YAGE_TIMER_H
