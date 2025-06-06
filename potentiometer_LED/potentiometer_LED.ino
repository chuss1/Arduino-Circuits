const int potPin = A3;
const int LED = 3;
int inputVal = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  inputVal = analogRead(potPin);
  analogWrite(LED, inputVal / 4);
  delay(100);
}
