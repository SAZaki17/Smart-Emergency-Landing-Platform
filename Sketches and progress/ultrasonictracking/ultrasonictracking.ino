#include <Servo.h> // подключаем библиотеку для работы с серводвигатели. 

//motor prep
Servo myservoyaw; 
Servo myservotangaj; 
Servo myservokrena; 
 int pos = 90; 

 //ultrasonice prep 
const int trigPin1 = 12; 
const int trigPin2 = 8; 
const int echoPin1 = 4; 
const int echoPin2 = 2; 


//distance to start tracking for ultrasonic 
int t_distance = 100; //in cm 
int distance1;int distance2; 
const int NUM_READ = 5;  

void setup(){ //
 Serial.begin(9600);
 //motor setup 
 myservoyaw.attach(11);
 myservoyaw.write(95);
 myservotangaj.attach(5);
 myservotangaj.write(pos);
 myservokrena.attach(6);
 myservokrena.write(pos);
 //ultrasonic setup
 pinMode(trigPin1, OUTPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(echoPin2, INPUT);
}


void loop(){
  //Left sensor
 	digitalWrite(trigPin2, LOW);  
	delayMicroseconds(2);  
  
	digitalWrite(trigPin2, HIGH);  
	delayMicroseconds(5);  
  
	digitalWrite(trigPin2, LOW);  
  
  	int duration = pulseIn(echoPin2, HIGH); 
    runMiddleArifmOptim(duration);
  
  //Right sensor
  	digitalWrite(trigPin1, LOW);  
	delay(10);  
  
	digitalWrite(trigPin1, HIGH);  
	delay(20);  
  
	digitalWrite(trigPin1, LOW);  
  
  	int duration2 = pulseIn(echoPin1, HIGH);
    runMiddleArifmOptim(duration2); 

    //calculate distance based on duration of each sensor 
  
  	distance1 = (duration2*.0343)/2; 
    distance1 = constrain(distance1, 5, 300); 
  	distance2 = (duration*.0343)/2;
    distance2 = constrain(distance2, 5, 300); 
    //int diff = distance1 - distance2;
    //int teleng = pos+diff; 

    follow(); 

    Serial.print("D_right ");Serial.print(distance1);
    Serial.print('\t');Serial.print("D_left ");Serial.println(distance2);
    /*Serial.print('\t');Serial.print("D_diff ");Serial.print(diff);
    Serial.print('\t');Serial.print("Teleng ");Serial.println(teleng);*/

} 


void follow()
{
  if (distance1 <= t_distance || distance2 <= t_distance)
  {
    if (distance1 + 5 < distance2){ pos = pos -1; }
    if (distance2 + 5 < distance1) { pos = pos +1; }
  }
  if (pos > 180)
  {
    pos = 180; 
  }
  if (pos < 0) 
  {
    pos = 0; 
  }
  myservoyaw.write(pos); 
}

//оптимальное бегущее среднее арифметическое 
float runMiddleArifmOptim(float newVal) {
  static int t = 0;
  static float vals[NUM_READ];
  static float average = 0;
  if (++t >= NUM_READ) t = 0; // перемотка t
  average -= vals[t];         // вычитаем старое
  average += newVal;          // прибавляем новое
  vals[t] = newVal;           // запоминаем в массив
  return ((float)average / NUM_READ);
}







