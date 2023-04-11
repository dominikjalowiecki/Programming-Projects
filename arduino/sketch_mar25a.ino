const uint8_t led_pin = PD3;
const uint16_t tl_load = 0;

void setup()
{
  DDRD |= _BV(led_pin);
  TCCR2B |= (1 << CS20);
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS22);
  
  TCNT2 = tl_load;

  TIMSK2 |= _BV(TOIE0);

  sei();
}

void loop()
{
  delay(1000);
}

ISR(TIMER2_OVF_vect)
{
  PORTD ^= _BV(led_pin);
}
