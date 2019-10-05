#include <WiFiManager.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

WiFiManager wifiManager; //GERENCIADOR DA INTERNET--------------------------

void configModeCallback (WiFiManager *myWiFiManager); //callback da internet

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
#define FIREBASE_HOST "prototipofikiria.firebaseio.com"
#define FIREBASE_AUTH "TTD91ryycLLe3QVFO170lwgWq88AO1W6B5V4lAJD"

//****************************************************************

//__ Variável a ser publicada
int counter = 0;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  //__ Verifica se está conectada a cloud para envio dos dados
 /* if (!!!client.connected()) {
    //__ Caso não esteja conectada, tenta a conexão
    Serial.print("Reconectando-se em ");
    Serial.println(server);
    while (!!!client.connect(clientId, authMeth, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }*/
/*
  //__ Envia um dado para a cloud
  enviaDado(String("counter"), counter);
  */
  Firebase.pushInt("cont",counter);
  //__ Incrementa o contador, mudando o valor a ser enviado para a cloud.
  ++counter;

  //__ Faz o envio a cada 10 segundos.
  delay(10000);

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