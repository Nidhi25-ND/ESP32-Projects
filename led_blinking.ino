int led=2;
int led1=5;
int led2=4;
int buzz=15;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(buzz,OUTPUT);
 for( int i=0;i<10;i++){
 digitalWrite(led,HIGH);
 digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 delay(1000);
 digitalWrite(led,LOW);
 digitalWrite(led1,LOW);
 digitalWrite(led2,LOW);
 delay(1000);
 }
 digitalWrite(buzz,HIGH);
 delay(1000);
 digitalWrite(buzz,LOW);
}
void loop(){ 
}
