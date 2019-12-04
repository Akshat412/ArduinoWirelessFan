#define relayPin 9
#define sensorPin A1
int appState = 0;
int fanState = 0;
int temp = 20; // degree Celsius
int currentTemp = 20;

void setup
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  
}

void values()
{
  if(Serial.available() > 0)
  {
    if(Serial.parseInt() == 0)
    {
      if(appState == 0) appState = 1; //Manual Mode
      else appState = 0; // Automatic Mode
    }
    
    else if(Serial.parseInt() == 1)
    {
      if(fanState == 0) fanState = 1; // Fan ON
      else fanState = 0; // Fan OFF
    }

    else if(Serial.parseInt() < 30 && Serial.parseInt() > 15)
    {
      temp = Serial.parseInt(); //Sets the temperature
    }
  }
}

void tempSense()
{
  CurrentTemp = analogRead(sensorPin); 
}

void loop
{
  values();
  tempSense();

  if(appState == 0) // Manual
  {
    if(temp > currentTemp) digitalWrite(relayPin, HIGH);      
    else digitalWrite(relayPin, LOW);
  }

  if(appState == 1) //Auto
  {
    if(fanState == 1) digitalWrite(relayPin, HIGH);
    else digitalWrite(relayPin, LOW);     
  }
}
