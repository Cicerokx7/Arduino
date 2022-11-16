int bunnies = A0;
int money = 0;

void setup() {
  Serial.begin(9600);
 Serial.print("please:  ");
 pinMode(bunnies, INPUT);
}

void loop() {
  money = analogRead(bunnies);
  Serial.print(money);
  Serial.print(":  ");
  delay(100);

}
