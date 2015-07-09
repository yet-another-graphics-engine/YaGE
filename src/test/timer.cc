#include "../../include/yage.h"
#include "../window/timer.h"

void test_timer(void) {
    yage_init(800, 600);
    struct yage_timer *timer = yage_timer_create(10.0);
    struct yage_message msg;
    while (yage_get_message(&msg, 0)) {
        if (msg.type != kYageTimer) continue;
        if (msg.timer.type == kYageTimerRunning) {
            yage_clear();
            if (msg.timer.seconds == 1) {
                yage_timer_pause(timer);
                yage_sleep(2);
                yage_timer_resume(timer);
            }
            yage_printf(0, 0, "%lf seconds survived", msg.timer.seconds);
            yage_printf(0, 20, "%lf seconds survived", yage_timer_get_time_elapsed(timer));
        } else {
            yage_timer_stop(timer);
            yage_dlg_message("Finished", "Time: 10 seconds");
        }
    }
}