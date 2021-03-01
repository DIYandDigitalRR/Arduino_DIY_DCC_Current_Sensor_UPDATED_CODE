long result; //longer variable storage
int numSamples = 10;//number of readings
int clearcount;//clear test variable
int clearsample = 100;// number of clear samples needed from sensor
int threshold = 550;//ADJUST THIS FOR SENSITIVITY minimum thresold for tripping the sensor
int value;// final read result

void setup(){
  Serial.begin(9600);//starts serial monitor
  pinMode(7,OUTPUT);//indicator LED for occupancy
}

enum OCCUPANCY
{
  ST_OCCUPIED,
  ST_CLEAR,
};//Our occupancy states

OCCUPANCY Occupancy = ST_CLEAR;//default state

void loop(){
  int valA1;
  int result = 0;
  for (int i=0; i < numSamples; ++i){
    valA1 = analogRead(A0);//reads analog pin
    result +=valA1;//adds new reading to variable 'result'
    value=result/i;//averages readings
    Serial.println(value);//displays average reading
  }
  delay(10);//reading every .01 seconds

switch (Occupancy)
{
  case ST_OCCUPIED:
  occupied();
  break;//sets up occupied state
  case ST_CLEAR:
  clear1();
  break;//sets up clear state
}
}

void clear1(){
  clearcount=0;//resets the clearcount
  digitalWrite(7,LOW);//keeps LED off for indicator
  if (value < threshold){
    Serial.println("Block is occupied");//displays text
    Occupancy = ST_OCCUPIED;//switches to occupied
  }
}

void occupied(){
  digitalWrite(7,HIGH);//turns on LED indicator
if ((value >threshold) && (clearcount<clearsample)){
  clearcount++;//adds to clear count
}
if ((value < threshold) && (clearcount<clearsample)){
  clearcount=0;//resets the clearcount if a false reading was taken
}
if ((value>threshold) && (clearcount >(clearsample-1))){
  Serial.println("Block is Clear");//displays text
  Occupancy = ST_CLEAR;//changes to clear
}
}
