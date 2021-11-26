#include <stdint.h>
#include "plat_func.h"
#include "plat_gpio.h"

static bool is_DC_on;
static bool is_post_complete;

void ISR_slp3(uint32_t tmp0, uint32_t tmp1) {
  printk("slp3\n");
}

void ISR_post_complete() {
  set_post_status();
}

void ISR_DC_on() {
  set_DC_status();
}

void IRS_PWROK_SLOT1() {
  set_BIC_slot_isolated(FM_BIC_SLOT1_ISOLATED_EN_R);
}

void IRS_PWROK_SLOT3() {
  set_BIC_slot_isolated(FM_BIC_SLOT3_ISOLATED_EN_R);
}

void set_DC_status() {
  //is_DC_on = gpio_get(PWRGD_SYS_PWROK);
  //printk("set dc status %d\n", is_DC_on);
}

bool get_DC_status() {
  return is_DC_on;
}

void set_post_status() {
  //is_post_complete = !(gpio_get(FM_BIOS_POST_CMPLT_BMC_N));
  //printk("set is_post_complete %d\n", is_post_complete);
}

bool get_post_status() {
  return is_post_complete;
}

void set_BIC_slot_isolated(uint8_t gpio_num) {
  int ret = 0;

  ret = gpio_set(gpio_num, GPIO_HIGH);
  if ( ret < 0 ) {
    printk("failed to set slot isolated due to set gpio %d is failed\n", gpio_num);
  }
}
