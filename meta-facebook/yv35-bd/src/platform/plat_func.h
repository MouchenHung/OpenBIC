#ifndef PLAT_FUNC_H
#define PLAT_FUNC_H
#include <stdbool.h>

void ISR_usbhub();
void ISR_pltrst();
void ISR_slp3();
void ISR_DC_on();
void ISR_post_complete();
void IRS_PWROK_SLOT1();
void IRS_PWROK_SLOT3();

bool get_DC_status();
bool get_post_status();
void set_BIC_slot_isolated(uint8_t gpio_num);
#endif
