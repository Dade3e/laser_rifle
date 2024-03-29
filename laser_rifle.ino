// LASER RIFLE Attiny shot
// Davide Barchetta 2024

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0   -> laser
//                  +----+

#define AnalogPin 3 //ATTINY 3, NANO A0
#define LaserPin 0 //ATTINY 0, NANO 2
#define LaserTime 30
#define debounce 250
#define theshold 0.20 // max * theshold; 0 < theshold < 1

#define bufferSize 6

#define debug false
#define info false

int buffer[bufferSize];
int index = 0;
int media = 10;

void setup() {

  pinMode(AnalogPin,INPUT);
  pinMode(LaserPin,OUTPUT);
  digitalWrite(LaserPin, LOW);

  if(info || debug)
    Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(AnalogPin);
  if(sensorValue > ( media * theshold)){
    shot();
    delay(debounce);
  }
  if(sensorValue > ( media * theshold)){
    buffer[index] = sensorValue;
    index += 1;
    if(index >= bufferSize) { index = 0; }
    int sum = 0;
    for (int i = 0; i<bufferSize; i++){
      sum += buffer[i];
    }
    media = (sum/bufferSize);
  }
  if(info){
    Serial.print(sensorValue);
    Serial.print(" | ");
    for (int i = 0; i<bufferSize; i++){
      Serial.print(buffer[i]);
      Serial.print(" ");
    }
    Serial.print("| ");
    Serial.println(media);
  }
  delay(1);
}

void shot(){
  digitalWrite(LaserPin, HIGH);
  delay(LaserTime);
  digitalWrite(LaserPin, LOW);
}
