#define light D2
int data;
String d; 
#include <Wire.h>  

#include <ESP8266WiFi.h> 

#include <ESP8266HTTPClient.h>









String sendval, postData;

void setup() {

 pinMode(light,INPUT);
    

  Serial.begin(115200); 

  Serial.println("Communication Started \n\n");  

  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);     // initialize built in led on the board

 

  delay(2000);

  

  WiFi.mode(WIFI_AP);

  WiFi.softAP("light_sensor", "12345678"); 

  delay(200);

    while (WiFi.softAPgetStationNum() !=1)   {      //loop here while no AP is connected to this station

      Serial.print(".");

      delay(100);                            

      }

  delay(500);

}

void loop(){ 

  //read temperature and humidity

  data=analogRead(light);
  
  if(data == 0)
  {
    d="light";
  }
  else
  {
    d="dark";
  }
    
  
  HTTPClient http;    // http object of clas HTTPClient

  // Convert to float

  sendval = d;  

    

  postData = "sendval=" + sendval ;

  // We can post values to PHP files as  example.com/dbwrite.php?name1=val1&name2=val2

  // Hence created variable postData and stored our variables in it in desired format

  // Update Host URL here:-  

  http.begin("http://192.168.4.2/swe/save.php");                             // Connect to host where MySQL database is hosted

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");        //Specify content-type header

  int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode

  Serial.println("Values are, sendval = " + sendval );

  // if connection eatablished then do this

  if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 

    String webpage = http.getString();    // Get html webpage output and store it in a string

    Serial.println(webpage + "\n");

  } else { 

    // if failed to connect then return and restart

    Serial.println(httpCode); 

    Serial.println("Failed to upload values. \n"); 

    http.end(); 

    return; 

  }

  delay(200); 

  digitalWrite(LED_BUILTIN, LOW);

  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);

}
