/*
 WiFi Web Server LED Blink
 J.J.B. adaptat 17-9-2024

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 12.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
  LED=12 
*/
#include <WiFi.h>

const int LED=12;
const int LED2=13;
const int LED3=14;

const char *ssid = "xxxxxx";
const char *password = "xxxxxxx";

int ambarLedState = 0;

NetworkServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  NetworkClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<H2>Quim:<br><br>");
            client.print("Click <a href=\"/H\">here</a> to turn the red LED on.<br><br>");
            client.print("Click <a href=\"/L\">here</a> to turn the red LED off.<br><br>");
            client.print("Click <a href=\"/M\">here</a> to switch the state of the ambar LED.<br><br>");
            client.print("Click <a href=\"/J\">here</a> to turn ON the green LED.<br><br>");
            client.print("Click <a href=\"/G\">here</a> to turn OFF the green LED.<br><br>");



            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED, LOW);  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /M")) {
          if (ambarLedState == 0) {
          digitalWrite(LED2, HIGH); 
          ambarLedState = 1;  }
          else{
            digitalWrite(LED2, LOW);
            ambarLedState = 0;
          } 
        }
         if (currentLine.endsWith("GET /N")) {
          digitalWrite(LED2, LOW);  // GET /N turns the LED off
        }
        if (currentLine.endsWith("GET /J")) {
          digitalWrite(LED3, HIGH);

          digitalWrite(LED, LOW);  // GET /J turns the LED on
        }
        if (currentLine.endsWith("GET /G")) {
          digitalWrite(LED3, LOW);  // GET /G turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
