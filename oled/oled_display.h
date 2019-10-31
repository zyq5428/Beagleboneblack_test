#ifndef OLED_DISPLAY_H_
#define OLED_DISPLAY_H_

extern void oled_display_memu(void);

int oled_init(void);
int sht3x_display(int32_t temperature, int32_t humidity);

#endif /* OLED_DISPLAY_H_ */
