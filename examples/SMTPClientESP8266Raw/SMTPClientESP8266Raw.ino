/*
   Copyright 2017 Alessandro Pasqualini
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
     http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   @author    Alessandro Pasqualini <alessandro.pasqualini.1105@gmail.com>
   @url       https://github.com/alessandro1105

*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <SMTPClient.h>

const char* ssid = "";
const char* password = "";

//--- SMTP server settings ---
//GMAIL
// You will need a secure client to use Gmail on port 465 because it requires TLS.
// You need also to enable less secure apps from https://myaccount.google.com/lesssecureapps
#define SMTP_SERVER "smtp.gmail.com"
#define SMTP_PORT 465
//SMTP2GO
// You just need a normal client because the connection to server is not secure
//#define SMTP_SERVER "mail.smtp2go.com"
//#define SMTP_PORT 2525

//--- SMTP AUTH (must be in base64) ---
#define SMTP_LOGIN ""
#define SMTP_PASSWD ""

// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;

// Use WiFiClient class to create connection
//WiFiClient client;

void setup() {
  // ESP8266 connection stuff
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  //SMTPClient stuff
  // Create an SMTP client
  SMTPClient smtp(client, SMTP_SERVER, SMTP_PORT);
  // Connect to the SMTP server
  smtp.connect();
  // EHLO command
  smtp.ehlo("friend");
  // AUTH LOGIN command
  smtp.authLogin(SMTP_LOGIN, SMTP_PASSWD);
  // MAIL FROM command
  smtp.mailFrom("sender@example.com"); // From
  // RCPT TO command
  smtp.rcptTo("someone@example.com"); // To
  smtp.rcptTo("someoneelse@example.com"); // To
  smtp.rcptTo("another@example.com"); // CC
  smtp.rcptTo("secret@example.com"); // BCC
  // DATA command
  smtp.data();
  // Setting some headers
  smtp.header("From", "Some Sender <sender@example.com>"); // From
  smtp.header("To", "Someone <someone@example.com>, Someone Else <someoneelse@example.com>");
  smtp.header("CC", "Another <another@example.com>");
  smtp.header("Subject", "Hello there");
  smtp.body("Email sent from Arduino/ESP8266/Fishino!");
  smtp.finishData();
  smtp.quit();
  
}

void loop() {
}

