#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#define TIME 10000

static uint8_t segments[] = {
    //FGEDCBA
    0b1011111,  // 0
    0b0000110,  // 1
    0b0111011,  // 2
    0b0101111,  // 3
    0b1100110,  // 4
    0b1101101,  // 5
    0b1111101,  // 6
    0b0000111,  // 7
    0b1111111,  // 8
    0b1101111,  // 9
    0b1110111,  // A
    0b1111100,  // B
    0b1011001,  // C
    0b0111110,  // D
    0b1111001,  // E
    0b1110001,  // F
};

static void init()
{
    // inputs
    DDRA = 0;
    DDRD = 0;

    // display sink (PB1..7)
    DDRB = 0b11111111;
    DDRD = _BV(DDD6);
}

static uint8_t read_input()
{
    uint8_t d = PIND;
    uint8_t a = PINA;

    return (d & _BV(PD0))       // bit 0
         | (d & _BV(PD1))       // bit 1
         | (a & _BV(PA1)) << 1  // bit 2
         | (a & _BV(PA0)) << 3  // bit 3
         | (d & _BV(PD2)) << 2  // bit 4
         | (d & _BV(PD3)) << 2  // bit 5
         | (d & _BV(PD4)) << 2  // bit 6
         | (d & _BV(PD5)) << 2  // bit 7
         ;
}

static void set_output(int digit, uint8_t v)
{
    PORTB = ~(segments[v] << 1);
    if (digit == 1) {
        PORTB |= _BV(PB0);
        PORTD &= ~_BV(PD6);
    } else {
        PORTB &= ~_BV(PB0);
        PORTD |= _BV(PD6);
    }
}

int main()
{
    init();
    while (1) {
        uint8_t v = read_input();
        set_output(0, v & 0b1111);
        _delay_us(TIME);
        set_output(1, v >> 4);
        _delay_us(TIME);
    }
}

// vim:st=4:sts=4:sw=4:expandtab
