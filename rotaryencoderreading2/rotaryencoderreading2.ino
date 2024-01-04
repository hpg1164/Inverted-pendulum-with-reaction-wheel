int encoderpin1 = 2;
int encoderpin2 = 3;
int ENA = 6;
int In1 = 5;
int In2 = 4;

//angle/pulse=360/20=18 degree per pulse
volatile int anglePerPulses = 18;
//total pulse starting from program
volatile unsigned long totalPulses = 0;
//total angle calculated from totalpulse
volatile long totalAngle = 0;
//variable measuring from time
volatile unsigned long lastTime = 0;
volatile unsigned long currentTime = 0;
volatile double deltaT = 0;

//compute angular velocity
volatile double angularVelocity = 0;
//total time untile sumpulse reaches averagesaple
volatile unsigned long timeAverageAngularVelocity = 0;
volatile int sumPulses = 0;
//calulate angular velocity
volatile int averageSample = 50;
void setup() {
  // put your setup code here, to run once:
  pinMode(ENA,OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(encoderpin1,INPUT);
   pinMode(encoderpin2,INPUT);


  attachInterrupt(digitalPinToInterrupt(encoderpin1),interruptFunction,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderpin2),interruptFunction,RISING);

  Serial.begin(9600);
  lastTime = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ENA,150);
  //direction
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);

}
void interruptFunction(){
  currentTime = millis();

  deltaT = currentTime-lastTime;
  lastTime = currentTime;

  //increment the total number of pulses
  totalPulses = totalPulses+1;
  totalAngle = totalPulses*anglePerPulses;
  sumPulses = sumPulses+1;
  //track the total time between computing the average
  timeAverageAngularVelocity = timeAverageAngularVelocity+deltaT;


  //calculate the average angular velocity
  if(sumPulses>=averageSample)
  {
    angularVelocity = 1000*((double) (sumPulses*anglePerPulses))/((double)timeAverageAngularVelocity);
    Serial.println((String) "Total angle:"+totalAngle+"  Angular velocity:"+angularVelocity);
    sumPulses = 0;
    timeAverageAngularVelocity = 0;

  }


}
