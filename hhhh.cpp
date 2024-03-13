#include <Arduino.h>

volatile bool overflow = false;

void delay_ms(int t)
{
    const uint32_t maxDelayPerCycle = 4194; // 65535 / (16000000 / 1024)) * 1000
    uint16_t cycles = t / maxDelayPerCycle;
    uint16_t remainder = t % maxDelayPerCycle;
    // Disable interrupts temporarily
    cli();
    // Reset Timer/Counter1 control registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B = 0b00000101;
    TIMSK1 = 0b00000001;
    TCNT1 = 65535 - ((15625) / 1000) * remainder; // 65535-15625
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
    delay_ms(1000);
    Serial.println("B");
    delay_ms(1000);
}
