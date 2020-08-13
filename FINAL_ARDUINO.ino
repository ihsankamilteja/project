#include "WiFiEsp.h"

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#include <dht.h>
SoftwareSerial Serial1(A3, A2); // RX, TX
#endif
#include <Servo.h>
// inialisasi variabel servo
Servo servoKu;


char ssid[] = "Smartroof";            // your network SSID (name)
char pass[] = "12345678";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "autoshelter.scienceontheweb.net";

// Initialize the Ethernet client object
WiFiEspClient client;


// inialisasi masing2 pin

const int pinHujan = A0;
const int pinLdr = A1;



dht DHT;
#define DHT11_PIN A5

// inialisasin sensor kan pengkondisian
int hujan, cahaya, kondisi;

// ----------------- program default awal ------------------- //

void setup()
{
    // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
 // dht.begin();
 // inialisasi pin servo
 servoKu.attach(3);
 // inialisasi derajat awal servo
 servoKu.write(0);
 
 // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're Connected to network");
   
//  Serial.begin(9600);

  // inialisasi status I/O pin
  pinMode(pinHujan, INPUT);
  pinMode(pinLdr, INPUT);

  

  // inialisasi kondisi awal
  kondisi = 0;
}

// -------------------- program utama --------------------- //
void loop()
{
  String statusAtap;
  

  // inialisasi pembacaan sensor
  hujan = analogRead(pinHujan);
  cahaya = analogRead(pinLdr);
 

 int chk = DHT.read11(DHT11_PIN);
 float suhu = DHT.temperature;
  
  delay(1000);
  //1
  if (kondisi == 0 && hujan >= 930 &&( cahaya >= 700 || cahaya <700 ) && suhu >=35.00)
  {
    Serial.println(" Tanpa Hujan  Gelap dan Suhu udara panas");
    servoKu.write(180);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Terbuka");
    statusAtap="Terbuka";
    
    kondisi = 0;
    delay(100);
  }   
 
//2
  else if (kondisi == 0 && hujan >= 930 && cahaya >= 700 && suhu < 35.00)
  {
    Serial.println("Tanpa Hujan Gelap  dan Suhu tidak panas");
    servoKu.write(180);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");;
    Serial.println("Atap Terbuka");
    statusAtap="Terbuka";
    kondisi = 0;
    delay(100);
  }

  
//3
  else if (kondisi == 0 && hujan >= 930 && cahaya <= 699 && suhu >=35.00)
  {
    Serial.println("  Tanpa Hujan Cerah dan Suhu panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
        
    
    delay(100);
  }
  
  //4
  else if (kondisi == 0 && hujan <= 929 && cahaya <= 699 && suhu >=35.00)
  {
    Serial.println("Kondisi Cerah Tapi Hujan dan Suhu udara panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
        
   
    delay(100);
  }
//5
  else if (kondisi == 0 && hujan <= 929 && cahaya >= 700 && suhu >=35.00)
  {
    Serial.println("Kondisi Gelap Tapi Hujan dan Suhu udara panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
   
    delay(100);
  }
//6
  else if (kondisi == 0 && hujan <= 929 && cahaya <= 699 && suhu <35.00)
  {
    Serial.println("Kondisi Cerah Tapi Hujan dan Suhu  tidak panas");
   servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
        
    delay(100);
  }
//7
  else if (kondisi == 0 && hujan <= 929 && cahaya >= 700 && suhu <35.00)
  {
    Serial.println("Kondisi Gelap Tapi Hujan dan Suhu udara tidak panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
    
    delay(100);
  }
//8
  else if(kondisi == 0 && hujan >=930 && cahaya <=699 && suhu <35.00)
  {
    Serial.println("Kondisi cerah tanpa Hujan dan Suhu udara tidak panas");
    servoKu.write(180);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");;
    Serial.println("Atap Terbuka");
    statusAtap="Terbuka";
    kondisi = 0;
    delay(100);
    }






  
//9
 else if (kondisi == 1 && hujan >= 930 && cahaya >= 700 && suhu <35.00)
  {
    Serial.println(" Gelap Tanpa Hujan dan Suhu udara tidak panas");
    servoKu.write(180);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Terbuka");
    statusAtap="Terbuka";
    kondisi = 0;
    delay(100);
  }
//10
 else if (kondisi == 1 && hujan >= 930 && cahaya >= 700 && suhu >=35.00)
  {
    Serial.println("Kondisi Gelap Tanpa Hujan dan Suhu  panas");
    servoKu.write(180);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  :");
    statusAtap="Terbuka";
    Serial.println("Atap Terbuka");
    kondisi = 0;
    delay(100);
  }

//11
  else if (kondisi == 1 && hujan >= 930 && cahaya <= 699 && suhu >=35.00)
  {
    Serial.println("Kondisi Cerah Tanpa Hujan dan Suhu udara panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
        
    delay(100);
  }
//12
  else if (kondisi == 1 && hujan <= 929 && cahaya <= 699 && suhu >=35.00)
  {
    Serial.println("Kondisi Cerah Tapi Hujan dan Suhu udara panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
        
    delay(100);
  }

//13 
  else if (kondisi == 1 && hujan <= 929 && cahaya >= 700 && suhu >=35.00) 
  {
    Serial.println("Kondisi Gelap Tapi Hujan dan Suhu udara panas");
   servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
    
    delay(100);
  }
//14
  else if (kondisi == 1 && hujan <= 929 && cahaya <= 699 && suhu <35.00)
  {
    Serial.println("Kondisi Cerah Tapi Hujan dan Suhu udara tidak panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
    
    delay(100);
  }
//15
  else if (kondisi == 1 && hujan <= 929 && cahaya >= 700 && suhu <35.00)
  {
    Serial.println("Kondisi Gelap Tapi Hujan dan Suhu udara tidak panas");
    servoKu.write(0);
    Serial.print("Temperature   : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    Serial.println("Atap Tertutup");
    statusAtap="Tertutup";
    kondisi = 1;
    
    delay(100);
  }
  //8

  else if (kondisi == 1 && hujan >= 930 && cahaya <= 699 && suhu <35.00)
  {
    Serial.println("Kondisi Cerah Tanpa Hujan dan suhu udara tidak panas");
    servoKu.write(180);
    Serial.print("Temperature    : ");
    Serial.println(suhu);
    Serial.print("Cahaya        : ");
    Serial.println(cahaya);
    Serial.print("Hujan         : ");
    Serial.println(hujan);
    Serial.print("Kondisi Atap  : ");
    statusAtap="Terbuka";
    Serial.println("Atap Terbuka");
    kondisi = 0;
    delay(100);
  }

    String resultcahaya = String(cahaya);
    String resulthujan = String(hujan);
    String resultsuhu = String(suhu);
    

    
      client.stop();
      delay(500);
      if (client.connect(server, 80)) {
        Serial.println("Connecting...");
        String url = "/api.php/insert/" + resultcahaya + "/" + resulthujan + "/" + resultsuhu + "/" + statusAtap;
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + server + "\r\n" +
                     "Connection: close\r\n\r\n");
        Serial.println("Sukses...."); 
      }
      else {
        // if you couldn't make a connection
        Serial.println("Connection failed");
 
      }
 
      boolean incomingData = false;
      while (client.available() && status == WL_CONNECTED) {
 
        if (incomingData == false)
        {
 
          incomingData = true;
        }
        char c = client.read();
        Serial.write(c);
 
      }
      
}
