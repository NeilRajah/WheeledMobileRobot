
#define ENC_A 3
#define ENC_B 2
#define TICKS_PER_REV 297.0
#define DIA 30  //mm

//Encoder values
int pos = 0;

//Timing values
int curr;
int prev;
int INTERVAL = 20;

void setup() {
  Serial.begin(9600);
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  prev = millis();
  
  attachInterrupt(digitalPinToInterrupt(ENC_A), updateEncoder, RISING);
}

void loop() {
  curr = millis();
  if (curr - prev >= INTERVAL) {
    prev = curr;
    
    displayEncoder();
  }
}

void updateEncoder() {
  if (digitalRead(ENC_B) == HIGH) {
    pos++;
  } else {
    pos--;
  }
}

float ticksToInches(int ticks) {
  return (ticks / TICKS_PER_REV) * PI*DIA;
}

void displayEncoder() {
  Serial.print(pos);
  Serial.print("\t");  
  Serial.print(ticksToInches(pos));
  Serial.println();  
}
