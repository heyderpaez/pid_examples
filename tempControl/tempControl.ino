#include <PID_v1.h>
// Incluimos librería
#include <DHT.h>

 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,45,20,0, REVERSE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(9,OUTPUT);
 
  // Comenzamos el sensor DHT
  dht.begin();
  Setpoint = 31;
  myPID.SetOutputLimits(6, 130);
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature();
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  Input = t;
  myPID.Compute();
  analogWrite(9,Output);
  //Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(",");
  Serial.print(Setpoint);
  //Serial.print("       ");
  //Serial.print("PWM:");
  Serial.print(",");
  Serial.println(Output);
  delay(1000);
}
