#include <Arduino.h>

volatile bool overflow = false;

void delay_us(int t)
{
    const uint32_t maxDelayPerCycle = 32; // 65535 / (16000000 / 8)) * 1000
    uint16_t cycles = (t / maxDelayPerCycle)/1000;
    uint16_t remainder = t % maxDelayPerCycle;
    // Disable interrupts temporarily
    cli();
    // Reset Timer/Counter1 control registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B = 0b00000010;
    TIMSK1 = 0b00000001;
    TCNT1 = 65535 - ((2000000) / 1000) * remainder; 
    sei();
    if (cycles > 0)
    {
        for (int i = 0; i < cycles; i++)
        {
            while (!overflow)
            {
            }
            overflow = false;
        }
    }

    while (!overflow)
    {
    }
    overflow = false;
}

ISR(TIMER1_OVF_vect)
{
    overflow = true;
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println("A");
    delay_us(1000);
    Serial.println("B");
    delay_us(1000);
}
