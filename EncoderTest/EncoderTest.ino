/**
   EncoderTest
   Author: Neil Balaskandarajah
   Created on: 23/07/2020
   Testing the Encoders out
*/

class Encoder {
  String tag;
  byte pinA;
  static byte pinB;
  float TICKS_PER_REV;
  float DIA;
  static int ticks;

  public:
    Encoder(String label, byte A, byte B, float TICKS, float D) {
      tag = label;
      pinA = A;
      pinB = B;
      TICKS_PER_REV = TICKS;
      DIA = D;
    }

    void setup() {
      pinMode(pinA, INPUT_PULLUP);
      pinMode(pinB, INPUT_PULLUP);
      ticks = 0;

      attachInterrupt(digitalPinToInterrupt(pinA), Encoder::updateEncoder, RISING);
    }

    void loop() {
      displayEncoder();
    }

    void displayEncoder() {
      Serial.print(ticks);
      Serial.print("\t");
      Serial.print(getPos());
      Serial.println();
    }

    static void updateEncoder() {
      if (digitalRead(pinB) == HIGH) {
        ticks++;
      } else {
        ticks--;
      }
    }

    int getPos() {
      return (ticks / TICKS_PER_REV) * PI * DIA;
    }

    //TO-DO: getVel()
};

//Timing values
int curr;
int prev;
int INTERVAL = 20;

Encoder leftEnc("Left", 3, 2, 297.0, 30);

void setup() {
  //  Serial.begin(9600);
  prev = millis();
  leftEnc.setup();
}

void loop() {
  curr = millis();
  if (curr - prev >= INTERVAL) {
    prev = curr;

    leftEnc.loop();
  }
}
