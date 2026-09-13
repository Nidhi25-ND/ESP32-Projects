int IR_SENSOR=2;
int led=4;
int buzz=12;
void setup() {
  // put your setup code here, to run once:
  pinMode(IR_SENSOR, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue= digitalRead(IR_SENSOR);
  Serial.print("IR Value: ");
  Serial.println(sensorValue);
  delay(1000);
  if(sensorValue==LOW){
    digitalWrite(led,HIGH);
    digitalWrite(buzz,HIGH);
    delay(5000);
  }
}
