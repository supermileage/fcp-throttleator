#define POT_MIN 370
#define POT_MAX 650
#define MAX_GRAD 1000

uint32_t normalized_in;
uint32_t throttle = 0;
uint16_t normalized_throttle = 0;

void setup() {
  // put your setup code here, to run once:
  TCCR0B = TCCR0B & B11111000 | B00000010; // for PWM frequency of 7812.50 Hz
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t pot_in = analogRead(A0);
  if (pot_in < POT_MIN)  pot_in = POT_MIN;
  else if (pot_in > POT_MAX) pot_in = POT_MAX;

  // Input from 0 - 1023
  normalized_in = (pot_in - POT_MIN) * 1023 / (POT_MAX - POT_MIN);

  if (normalized_in < throttle) {
    throttle = normalized_in;
  } else {
    throttle = (normalized_in - throttle) > MAX_GRAD ? throttle += MAX_GRAD : normalized_in;
  }

  normalized_throttle = throttle;

  analogWrite(5, normalized_throttle);

  Serial.print("Normalized_throttle:");
  Serial.print(normalized_throttle);
  Serial.print(",");

  Serial.print("pot_in:");
  Serial.println(pot_in);
  
}
