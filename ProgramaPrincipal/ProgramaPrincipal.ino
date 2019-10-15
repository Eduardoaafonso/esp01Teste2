#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "index.h"  //Web page header file
#include "confirm.h"  //Web page header file
#include "verifique.h"
#include "FirebaseESP32.h"

////////////////////MODIFICADO PARA FIKIRIA CONSOLE////////////////////////
#define FIREBASE_HOST "prototipofikiria.firebaseio.com" //
#define FIREBASE_AUTH "TTD91ryycLLe3QVFO170lwgWq88AO1W6B5V4lAJD"
/////////////////////////////////////////////////////////////////////////////

//Enter your SSID and PASSWORD
const char* ssid = "Fikiria"; //ssid usado no AP
const char* password = "fikiria"; //senha usada no AP
const char* ssidWifiConnect = ""; //ssid usado para conectar no WiFi.begin
const char* passwordWifiConnect = ""; //senha usado para conectar no WiFi.begin
const byte DNS_PORT = 53;
//const char* www_username = "fikiria";
//const char* www_password = "fikiria";
//Dados Usuarios
String ssidWifi = ""; //String para receber da Web o ssid
String passWifi = ""; //String para receber da Web a senha
String emailUsuario;
String statusESP = "offline";
String currentUID="default";

WebServer server(80);
DNSServer dnsServer;

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
FirebaseData firebaseData;
FirebaseJson updateDataDevice;
FirebaseJson updateDataRead;
FirebaseJson updateDataPlan;
//FirebaseJson jsonTemp;
//FirebaseJson jsonUmid;

String pathDataBaseDevice = "Dispositivo";
String pathDataBaseReads = "Leituras";
String pathDataBasePlan = "Planos";
String Nomeplano = "gratuito"; //Default por enquanto

void handleConfirmaDados();
char* readEEPROM();
void writeEEPROM();
void modoAP();
void modoOnline();
void modoAtivo();
void setupLoop2();

void setup() {
  Serial.begin(115200);
  
    WiFi.begin(ssidWifiConnect, passwordWifiConnect);
    int cont=0;
    while (WiFi.status() != WL_CONNECTED && cont <= 10) {
      delay(500);
      Serial.println("Connecting to WiFi..");
      cont++;
      //*****ACENDER LED VERMELHO*************************
    }
    delay(100);
  if(WiFi.status() != WL_CONNECTED){
     WiFi.disconnect();
     delay(100);
    //ESP32 As access point
    modoAP();
  }
  
//***********************FIREBASE**************************************
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//************************************************
  setupLoop2(); //Inicia o Core 2 do ESP32
  delay(1);

  
}

void loop() {
  
  if(statusESP == "offline" ){    
    server.handleClient();
    dnsServer.processNextRequest();
    delay(1);
  }    
  
  if(statusESP=="online"){
     Serial.println("conectado");
  modoOnline(); //Cria campos Dispositivo e Planos
 
}

if(statusESP == "ativo"){
 modoAtivo();
}

//**************Observa se nao teve atualização em Planos e Status***********
  if (Firebase.getString(firebaseData, pathDataBaseDevice+"/Plano")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      Nomeplano = firebaseData.stringData();
    }
  } /*else {
    Serial.println(firebaseData.errorReason());
  }*/
  
  if (Firebase.getString(firebaseData, pathDataBaseDevice+"/Status")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      statusESP = firebaseData.stringData();
    }
  } /*else {
    Serial.println(firebaseData.errorReason());
    //statusESP = "ErroStatus"; //TRATAMENTO DE ERRO
  }*/

  if (Firebase.getString(firebaseData, pathDataBaseDevice+"/CurrentUID")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      currentUID = firebaseData.stringData();
    }
  }
  delay(1);
}
