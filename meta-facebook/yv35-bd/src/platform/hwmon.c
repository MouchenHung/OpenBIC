#include "plat_func.h"
#include "plat_gpio.h"
#include "plat_i2c.h"

static bool is_DC_on;
static bool is_post_complete;
struct k_delayed_work sled_cycle_work;

K_DELAYED_WORK_DEFINE(sled_cycle_work, sled_cycle_work_handler);

void ISR_slp3(uint32_t tmp0, uint32_t tmp1) {
  printk("slp3\n");
}

void ISR_post_complete() {
  set_post_status();
}

void ISR_DC_on() {
  set_DC_status();
}

void ISR_sled_cycle() {
  uint8_t bb_btn_status = GPIO_HIGH;

  bb_btn_status = gpio_get(BB_BUTTON_BMC_BIC_N_R);
  // press sled cycle button
  if ( bb_btn_status == GPIO_LOW ) {
    k_delayed_work_submit(&sled_cycle_work, K_SECONDS(MAX_PRESS_SLED_BTN_TIME_s));

  // release sled cycle button
  } else if ( bb_btn_status == GPIO_HIGH ) {
    k_delayed_work_cancel(&sled_cycle_work);
  }
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

void sled_cycle_work_handler(struct k_work *item) {
  set_sled_cycle();
}

void set_sled_cycle() {
  uint8_t retry = 5;
  I2C_MSG msg;

  msg.bus = I2C_BUS_CPLD;
  msg.slave_addr = I2C_ADDR_CPLD >> 1; // change to 7-bits addr
  msg.tx_len = 2;
  msg.data[0] = CPLD_REG_OFS_SLED_CYCLE; // offset
  msg.data[1] = 0x01; // value

  if (i2c_master_write(&msg, retry) < 0) {
    printk("sled cycle fail\n");
  }
}
