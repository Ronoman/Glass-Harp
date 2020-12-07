byte step = 0;
bool wait = 0;
bool doonce = 0;
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


void setup() {
  ADCSRA &= ~PS_128;
  ADCSRA |= (1 << ADPS1);
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
  EICRA = 0;
  EICRA |= (1 << ISC11) | (1 << ISC10);
  EIMSK = 0;
  EIMSK |= (1 << INT1);
  sei();
  DDRD = B11110000;
  DDRB = B00000011;
  PORTD = B00001000;
  PORTB = B00011100;
}

ISR(TIMER1_COMPA_vect) {
  OCR1A = map(analogRead(A7), 0, 1023, 5000, 100);
  step++;
  doonce = 0;
  if (step == 6) {
    step = 0;
  }
}

ISR(TIMER2_COMPA_vect) {
  if (wait == 1) {
    wait = 0;
    doonce = 0;
  }
}

ISR (INT1_vect) {
  wait = 1;
  doonce = 0;
}

void loop() {
  if (doonce == 0) {
    switch (step) {
      case 0:
        if (wait == 0) {
          step0();
        }
        else {
          step01();
        }
        break;
      case 1:
        if (wait == 0) {
          step1();
        }
        else {
          step11();
        }
        break;
      case 2:
        if (wait == 0) {
          step2();
        }
        else {
          step21();
        }
        break;
      case 3:
        if (wait == 0) {
          step3();
        }
        else {
          step31();
        }
        break;
      case 4:
        if (wait == 0) {
          step4();
        }
        else {
          step41();
        }
        break;
      case 5:
        if (wait == 0) {
          step5();
        }
        else {
          step51();
        }
        break;
    }
  }
}

void step0() {
  PORTD = B00101000;
  PORTB = B00000011;
  doonce = 1;
}

void step01() {
  PORTD = B00101000;
  PORTB = B00000001;
  doonce = 1;
  TCNT2 = 0;
}

void step1() {
  PORTD = B11101000;
  PORTB = B00000000;
  doonce = 1;
}

void step11() {
  PORTB = B00000000;
  PORTD = B01101000;
  doonce = 1;
  TCNT2 = 0;
}
void step2() {
  PORTB = B00000001;
  PORTD = B11001000;
  doonce = 1;
}

void step21() {
  PORTD = B01001000;
  PORTB = B00000001;
  doonce = 1;
  TCNT2 = 0;
}

void step3() {
  PORTD = B00111000;
  PORTB = B00000001;
  doonce = 1;
}

void step31() {
  PORTD = B00101000;
  PORTB = B00000001;
  doonce = 1;
  TCNT2 = 0;
}

void step4() {
  PORTD = B01111000;
  PORTB = B00000000;
  doonce = 1;
}

void step41() {
  PORTB = B00000000;
  PORTD = B01101000;
  doonce = 1;
  TCNT2 = 0;
}

void step5() {
  PORTB = B00000011;
  PORTD = B01001000;
  doonce = 1;
}

void step51() {
  PORTD = B01001000;
  PORTB = B00000001;
  doonce = 1;
  TCNT2 = 0;
}
