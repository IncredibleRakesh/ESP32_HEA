#include <WiFi.h>
#include <WebServer.h>
#include "mbedtls/aes.h"
#include <base64.h>
extern "C" {
#include "crypto/base64.h"
} 
void encrypt(char * plainText, char * key, unsigned char * outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}
 
void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer){
 
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}
const char*   ssid = "D-Link_DIR-615";
const char* password = "rakesh1995";
WebServer server(80);

String ROBOT_LorR_STATE = "";
String ROBOT_UorD_STATE = "";

const int GPIO_PIN_NUMBER_22 = LED_BUILTIN;
const int GPIO_PIN_NUMBER_23 = LED_BUILTIN;

void handleRoot() 
{

char * key = "abcdefghijklmnop";

  String toEncodeL = "LEFT";
  String encodedL = base64::encode(toEncodeL);
  int str_lenL = encodedL.length() + 1; 
  char plainTextL[str_lenL];
  encodedL.toCharArray(plainTextL, str_lenL);
  unsigned char cipherTextOutputL[16];
  unsigned char decipheredTextOutputL[16];
  encrypt(plainTextL, key, cipherTextOutputL);
  decrypt(cipherTextOutputL, key, decipheredTextOutputL);
  String tempLEFT = reinterpret_cast<const char*>(cipherTextOutputL);
  char * toDecodeL = reinterpret_cast<char*>(decipheredTextOutputL);
  size_t outputLengthL;
  unsigned char * decodedL = base64_decode((const unsigned char *)toDecodeL, strlen(toDecodeL), &outputLengthL);
  String strLEFT = reinterpret_cast<const char*>(decodedL);
  free(decodedL); 
   
  String toEncodeR = "RIGHT";
  String encodedR = base64::encode(toEncodeR);
  int str_lenR = encodedR.length() + 1; 
  char plainTextR[str_lenR];
  encodedR.toCharArray(plainTextR, str_lenR); 
  unsigned char cipherTextOutputR[16];
  unsigned char decipheredTextOutputR[16]; 
  encrypt(plainTextR, key, cipherTextOutputR);
  decrypt(cipherTextOutputR, key, decipheredTextOutputR);
  String tempRIGHT = reinterpret_cast<const char*>(cipherTextOutputR);
  char * toDecodeR = reinterpret_cast<char*>(decipheredTextOutputR);
  size_t outputLengthR;
  unsigned char * decodedR = base64_decode((const unsigned char *)toDecodeR, strlen(toDecodeR), &outputLengthR);
  String strRIGHT = reinterpret_cast<const char*>(decodedR);
  free(decodedR);

  String toEncodeU = "FORWARD";
  String encodedU = base64::encode(toEncodeU);
  int str_lenU = encodedU.length() + 1; 
  char plainTextU[str_lenU];
  encodedU.toCharArray(plainTextU, str_lenU); 
  unsigned char cipherTextOutputU[16];
  unsigned char decipheredTextOutputU[16]; 
  encrypt(plainTextU, key, cipherTextOutputU);
  decrypt(cipherTextOutputU, key, decipheredTextOutputU);
  String tempUPWARD = reinterpret_cast<const char*>(cipherTextOutputU);
  char * toDecodeU = reinterpret_cast<char*>(decipheredTextOutputU);
  size_t outputLengthU;
  unsigned char * decodedU = base64_decode((const unsigned char *)toDecodeU, strlen(toDecodeU), &outputLengthU);
  String strUPWARD = reinterpret_cast<const char*>(decodedU);
  free(decodedU); 
  
  String toEncodeD = "DOWNWARD";
  String encodedD = base64::encode(toEncodeD);
  int str_lenD = encodedD.length() + 1; 
  char plainTextD[str_lenD];
  encodedD.toCharArray(plainTextD, str_lenD); 
  unsigned char cipherTextOutputD[16];
  unsigned char decipheredTextOutputD[16]; 
  encrypt(plainTextD, key, cipherTextOutputD);
  decrypt(cipherTextOutputD, key, decipheredTextOutputD);
  String tempDOWNWARD = reinterpret_cast<const char*>(cipherTextOutputD);
  char * toDecodeD = reinterpret_cast<char*>(decipheredTextOutputD);
  size_t outputLengthD;
  unsigned char * decodedD = base64_decode((const unsigned char *)toDecodeD, strlen(toDecodeD), &outputLengthD);
  String strDOWNWARD = reinterpret_cast<const char*>(decodedD);
  free(decodedD);
  
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i)=="DIRECTION")
    {
      String str_Server = server.arg(i);
      if (str_Server==strLEFT) 
         {
            Serial.println("GPIO23 is high");
            Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
            ROBOT_LorR_STATE = "LEFT";
            digitalWrite(GPIO_PIN_NUMBER_22, HIGH);
            break;
         } 
      else if (str_Server==strRIGHT) 
        {
          Serial.println("GPIO23 is low");
          Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
          ROBOT_LorR_STATE = "RIGHT";
          digitalWrite(GPIO_PIN_NUMBER_22, LOW);
          break;
        } 
      else if (str_Server==strUPWARD)
         {
            Serial.println("GPIO23 is high");
            Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
            ROBOT_UorD_STATE = "FORWARD";
            digitalWrite(GPIO_PIN_NUMBER_23, HIGH);
            break;
          }
      else if (str_Server==strDOWNWARD) 
          {
            Serial.println("GPIO23 is low");
            Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
            ROBOT_UorD_STATE = "DOWNWARD";
            digitalWrite(GPIO_PIN_NUMBER_23, LOW);
            break;
            }
    }
  }

String content="<!DOCTYPE html><html>";
content+="<head> <title>Robot Controls</title><head>";
content+="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
content+="<link rel=\"icon\" href=\"data:,\">";
content+="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
content+=".button { background-color: #4CAF50; border: 2px solid #4CAF50;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }";
content+="text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"; 
content+="</style></head>";
content+="<body><center><h1>ROBOT Controllers</h1></center>";
content+="<center><h2>Press on button to move ROBOT LEFT/RIGHT/UPWARD/DOWNWARDS</h3></center>";
content+="<form><center>";
content+="<p> ROBOT IS MOVING IN DIRECTION: " + ROBOT_LorR_STATE + "</p>";
content+="<center> <button id=\"myBtnLEFT\" class=\"button\" name=\"DIRECTION\" value=\"LEFT\" type=\"submit\" onclick=\"myFunctionLEFT()\">LEFT</button>";
content+="<script>function myFunctionLEFT() {var str = document.getElementById(\"myBtnLEFT\").value; var str1 =Sring(tempLEFT);var encdstr = escspe(tempLEFT);document.getElementById(\"mybtnLEFT\").value=str1;return true}</script>";
content+="<button id=\"myBtnRIGHT\" class=\"button\" name=\"DIRECTION\" value=\"RIGHT\" type=\"submit\" onclick=\"myFunctionRIGHT()\">RIGHT</button><br><br>";
content+="<script>function myFunctionRIGHT() {var str = document.getElementById(\"myBtnRIGHT\").value; var str1 =Sring(tempRIGHT);var encdstr = escspe(tempRIGHT);document.getElementById(\"mybtnRIGHT\").value=str1;return true}</script>";
content+="<p>ROBOT IS MOVING IN DIRECTION: " + ROBOT_UorD_STATE + "</p>";
content+="<center> <button id=\"myBtnFORWARD\" class=\"button\" name=\"DIRECTION\" value=\"FORWARD\" type=\"submit\" onclick=\"myFunctionFORWARD()\">FORWARD</button>";
content+="<script>function myFunctionFORWARD() {var str = document.getElementById(\"myBtnFORWARD\").value; var str1 =Sring(tempFORWARD);var encdstr = escspe(tempFORWARD);document.getElementById(\"mybtFORWARD\").value=str1;return true}</script>";
content+="<center><button id=\"myBtnDownward\" class=\"button\" name=\"DIRECTION\" value=\"DOWNWARD\" type=\"submit\" onclick=\"myFunctionDOWNWARD()\">DOWNWARD</button> <br><br>";
content+="<script>function myFunctionDOWNWARD() {var str = document.getElementById(\"myBtnDOWNWARD\").value; var str1 =Sring(tempDOWNWARD);var encdstr = escspe(tempDOWNWARD);document.getElementById(\"mybtDOWNWARD\").value=str1;return true}</script>";
content+="</center></form></body></html>";
server.send(200, "text/html", content);  
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}
void setup() {
Serial.begin(115200);
pinMode(GPIO_PIN_NUMBER_22, OUTPUT);
pinMode(GPIO_PIN_NUMBER_23, OUTPUT);

digitalWrite(GPIO_PIN_NUMBER_22, LOW);
digitalWrite(GPIO_PIN_NUMBER_23, LOW);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   Serial.println("");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void) {
  server.handleClient();}
