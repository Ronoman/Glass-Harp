byte step = 0;
bool wait = 0;
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
const unsigned int maxcurrent = 41;

void setup() {
  ADCSRA &= ~PS_128;
  ADCSRA |= (1 << ADPS1);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 31250;
  TCCR1B |= (1 << WGM12) | (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 100;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS21);
  TIMSK2 |= (1 << OCIE2A);
  DDRD = B11110000;
  DDRB = B00000011;
  PORTD = B00000000;
  PORTB = B00011100;
}

ISR(TIMER1_COMPA_vect) {
  OCR1A = map(analogRead(A7), 0, 1023, 5000, 120);
  step++;
  if (step == 6) {
    step = 0;
  }
}

ISR(TIMER2_COMPA_vect) {
  wait = 0;
}

void loop() {
  if (wait == 0) {
    switch (step) {
      case 0:
        if (analogRead(A6) < maxcurrent) {
          step0();
        }
        else {
          step01();
          wait = 1;
          TCNT2 = 0;
        }
        break;
      case 1:

        if (analogRead(A6) < maxcurrent) {
          step1();
        }
        else {
          step11();
          wait = 1;
          TCNT2 = 0;
        }
        break;
      case 2:

        if (analogRead(A6) < maxcurrent) {
          step2();
        }
        else {
          step21();
          wait = 1;
          TCNT2 = 0;
        }
        break;
      case 3:
        if (analogRead(A6) < maxcurrent) {
          step3();
        }
        else {
          step31();
          wait = 1;
          TCNT2 = 0;
        }
        break;
      case 4:

        if (analogRead(A6) < maxcurrent) {
          step4();
        }
        else {
          step41();
          wait = 1;
          TCNT2 = 0;
        }
        break;
      case 5:
        if (analogRead(A6) < maxcurrent) {

          step5();
        }
        else {
          step51();
          wait = 1;
          TCNT2 = 0;
        }
        break;
    }
  }
}

void step0() {
  PORTD = B00100000;
  PORTB = B00000011;
}

void step01() {
  PORTD = B00100000;
  PORTB = B00000001;
}

void step1() {
  PORTB = B00000000;
  PORTD = B11100000;
}

void step11() {
  PORTB = B00000000;
  PORTD = B01100000;
}
void step2() {
  PORTD = B11000000;
  PORTB = B00000001;
}

void step21() {
  PORTD = B01000000;
  PORTB = B00000001;
}

void step3() {
  PORTD = B00110000;
  PORTB = B00000001;
}

void step31() {
  PORTD = B00100000;
  PORTB = B00000001;
}

void step4() {
  PORTB = B00000000;
  PORTD = B01110000;
}

void step41() {
  PORTB = B00000000;
  PORTD = B01100000;
}

void step5() {
  PORTD = B01000000;
  PORTB = B00000011;
}

void step51() {
  PORTD = B01000000;
  PORTB = B00000001;
}
