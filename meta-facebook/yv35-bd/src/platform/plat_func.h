#ifndef PLAT_FUNC_H
#define PLAT_FUNC_H
#include <stdbool.h>
#include <kernel.h>

#define MAX_PRESS_SLED_BTN_TIME_s 4

void ISR_usbhub();
void ISR_pltrst();
void ISR_slp3();
void ISR_DC_on();
void ISR_post_complete();
void ISR_sled_cycle();

void sled_cycle_work_handler(struct k_work *item);

bool get_DC_status();
bool get_post_status();
void set_sled_cycle();
#endif
