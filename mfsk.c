
int frequency1 = 1000;
int frequency2 = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(9, frequency1);
  delay(500);
  tone(9, frequency2);
  delay(500);
}
