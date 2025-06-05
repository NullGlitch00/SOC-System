#include "system.h"
#include "io.h"
#include "unistd.h"
#include <stdint.h>
#include <stdio.h>

const uint8_t led7_table[16] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

int main() {
    uint32_t val, sum = 0, checking = 0;
    int i = 0;

    IOWR(RED_LEDS_0_BASE, 0, 0);
    IOWR(GREEN_LEDS_0_BASE, 0, 0);
    IOWR(HEX1_BASE, 0, 0xFF);
    IOWR(HEX2_BASE, 0, 0xFF);

    printf("Su dung SW[0:3] de nhap so, KEY[1] de xac nhan:\n");

    while (i < 8) {
        if ((IORD(KEY_BASE, 0) & 0x01) == 0) {
            val = IORD(SWITCHES_0_BASE, 0) & 0xF;
            if (val <= 9) {
                IOWR(MEMORY_0_BASE, i, val);
                printf("Gia tri [%d] = %d\n", i + 1, val);
                IOWR(HEX1_BASE, 0, led7_table[val]);
                while ((IORD(KEY_BASE, 0) & 0x01) == 0);
                i++;
            } else {
                printf("Chi nhap tu 0 – 9 thoi!\n");
            }
        }
    }

    for (i = 0; i < 8; i++)
    {
        val = IORD(MEMORY_0_BASE, i);
        IOWR(COMPUTE_0_BASE, i, val);
    }

    sum = IORD(COMPUTE_0_BASE, 8) & 0xFF;
    printf("Tong = %d\n", sum);

    uint8_t chuc = sum / 10;
    uint8_t donvi = sum % 10;
    IOWR(HEX2_BASE, 0, led7_table[chuc]);
    IOWR(HEX1_BASE, 0, led7_table[donvi]);

    checking = IORD(COMPUTE_0_BASE, 9) & 0xFF;
    if (checking % 2 == 0) {
        IOWR(RED_LEDS_0_BASE, 0, sum);
        printf("%d la so le\n", sum);
    } else {
        IOWR(GREEN_LEDS_0_BASE, 0, sum);
        printf("%d la so chan\n", sum);
    }

    printf("An KEY[0] de thu lai!\n");
    while (1);
    return 0;
}
