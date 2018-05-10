/*
58. rész - Automata öntözőrendszer

Magyar Arduino Labor, 2018.04.25.
*/

#include <ESP8266WiFi.h>

#define WLAN_SSID   "router nev"
#define WLAN_PASS   "jelszo"

const int szenzor = A0;
int szenzorertek = 0;
int szazalekertek = 0;

const int motor1 = 5;   //D1
const int motor2 = 4;   //D2

void setup()
{
  Serial.begin(115200);

  Serial.print("Csatlakozás ide: ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi sikeresen csatlakoztatva");
  Serial.println("IP cím: "); Serial.println(WiFi.localIP());

  pinMode(motor1, OUTPUT);
  digitalWrite(motor1, LOW);
  pinMode(motor2, OUTPUT);
  digitalWrite(motor2, LOW);
}

void loop()
{

  szenzorertek = analogRead(szenzor);
  szazalekertek = map(szenzorertek, 1023, 300, 0, 100);

  Serial.print("Szenzor erteke: ");
  Serial.println(szenzorertek);
  Serial.print("Szazalekban: ");
  Serial.print(szazalekertek);
  Serial.println("%");

  if (szazalekertek < 50)
  {
    motor_control();
  }

  delay(1000 * 60 * 60);

}


void motor_control()
{
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  delay(10000);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
}

