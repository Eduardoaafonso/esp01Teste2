#include <WiFiManager.h>
//#include <FirebaseArduino.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "index.h"  //Web page header file


WiFiManager wifiManager; //GERENCIADOR DA INTERNET--------------------------
FirebaseData firebaseData;
FirebaseJson updateData;
FirebaseJson json;
const char* www_username = "fikiria";
const char* www_password = "fikiria";
ESP8266WebServer server(80);
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void configModeCallback (WiFiManager *myWiFiManager); //callback da internet

String plano = "gratuito";
int delayPlano;

String email;

//DHT dht22;
//DHT dht11;
//*******************IBM*****************************************

/*
//#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//__ Informações do WIFI
//const char* ssid =     "SSID";
//const char* password = "Senha Wifi";

//__ Informações do dispositivo
#define DEVICE_TYPE  "esp01Aplicacao"
#define DEVICE_ID    "prototipoFikiria"

//__ Informações da conexão com o servidor
#define ORG     "evq5ua"
#define TOKEN   "s!Y_e8Z9KaM6qkBAzV"

//__ Variáveis de conexão com o servidor (Não customizaveis)
char server[]   = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]    = "iot-2/evt/status/fmt/json";
char authMeth[] = "a-evq5ua-jm2tbpskt1";
char token[]    = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);
*/
//****************************************************************
//*****************FIREBASE***************************************
 
// Configure com suas credenciais
// Credencial está em configuração do projeto, contas e serviços.
#define FIREBASE_HOST "prototipofikiria.firebaseio.com" //
#define FIREBASE_AUTH "TTD91ryycLLe3QVFO170lwgWq88AO1W6B5V4lAJD"

//****************************************************************

//__ Variável a ser publicada
int counter = 0;
String pathDataBase = WiFi.macAddress() +"/infos";
String statusEsp;

void setup() {
  
    //WiFiManager wifiManager;
    //wifiManager.resetSettings();
    
    Serial.begin(115200);
 
    wifiManager.setConfigPortalTimeout(600); //tempo usado para sair do looping caso nao conecte (em segundos)
//    wifiManager.setTimeout(10);
 //   wifiManager.setConnectTimeout(10);
    wifiManager.setAPCallback(configModeCallback); 
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.autoConnect("AP_Acess","123"); //cria uma rede sem senha
  //Serial.print("MAC: ");
  //Serial.println(WiFi.macAddress());

//*****************Confere se conectou****************************************
 /* Serial.println();
//  Serial.print("Conectando-se na rede "); Serial.print(ssid);

  //__ Conecta-se na rede WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");

  Serial.print("Conectado, endereço de IP: ");
  Serial.println(WiFi.localIP());*/

  //*********************************************************************
//***********************FIREBASE**************************************
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//************************************************

//Criando campos no DataBase
//json.addString("_data2","_value2");
if(!Firebase.pathExist(firebaseData, pathDataBase)){
    updateData.addString("email","-1");
    updateData.addString("status","criado");
    updateData.addString("dados","-1");
    updateData.addString("plano","-1");
    
    //updateData.addString("data1","value1").addJson("data2", &json);
    
    if (Firebase.updateNode(firebaseData, pathDataBase, updateData)) {
    
      /*Serial.println(firebaseData.dataPath());
    
      Serial.println(firebaseData.dataType());
    
      Serial.println(firebaseData.jsonData()); */
      statusEsp = "criado";
      
    } else {
      //Serial.println(firebaseData.errorReason());
      statusEsp = "NaoCriado";
    }
}


  server.on("/", [](){
    if(!server.authenticate(www_username, www_password))
      return server.requestAuthentication();
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
  });
  
  server.on("/", handleRoot);      //This is display page
  server.on("/email", handleEmail);//Pega o valor da temperatura


}

void loop() {

  if (Firebase.getString(firebaseData, pathDataBase+"/plano")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      plano = firebaseData.stringData();
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
  
  if (Firebase.getString(firebaseData, pathDataBase+"/status")) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      statusEsp = firebaseData.stringData();
    }
  } else {
    Serial.println(firebaseData.errorReason());
    statusEsp = "ErroStatus"; //TRATAMENTO DE ERRO
  }

  if(statusEsp == "sememail"){
    server.begin();                  //Start server
    server.handleClient();
    
    }
    
  //float temperatura = DHT.temperatura;
  //int umidade = DHT.umidade;  

  
//  firebase.pushInt("userData/dados",counter);
  /*Firebase.pushInt("temp",temperatura);
  Firebase.pushInt("umi",umidade);
  Firebase.pushInt("version", 1.0);
  
  if (counter%10==0){
  //__ Incrementa o contador, mudando o valor a ser enviado para a cloud.
    
    plano = Firebase.pull("versao");***
    
    if(plano==0){
      plano = 1000*60*60; 
      }
  }
  */
  ++counter;
  
  if(plano == "string"){
    delayPlano = 10000;
    }

  //__ Faz o envio a cada 10 segundos.
  delay(delayPlano); //plano

}


void configModeCallback (WiFiManager *myWiFiManager) {  
//  Serial.println("Entered config mode");
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede

}

void saveConfigCallback () {
//  Serial.println("Should save config");
  Serial.println("Configuração salva");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
}

void handleEmail() {

  email = server.arg("email");

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated– Press Back Button");
  //delay(100);
  Serial.println(email);
  server.close();
}

void handleRoot() {
      String s = MAIN_page; //Read HTML contents
      server.send(200, "text/html", s); //Send web page
}

/*
//__ Envia os dados para a cloud
void enviaDado(String nome_campo, int dado){
  //__ Formata a string que será envia para a cloud (JSON)
  String payload = "{\"d\":{\"" + nome_campo + "\":";
  payload += dado;
  payload += "}}";
 
  Serial.print("Sending payload: ");
  Serial.println(payload);
 
  //__ Envia o dado
  if (client.publish(topic, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
}*/
