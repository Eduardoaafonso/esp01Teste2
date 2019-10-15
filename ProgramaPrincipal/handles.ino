
void handleRoot() {
  
      String s = MAIN_page; //Read HTML contents
      server.send(200, "text/html", s); //Send web page
}

void handleDadosUsuario() {
  delay(100);
  ssidWifi = server.arg("ssidWifi");
  passWifi = server.arg("passWifi");
  emailUsuario = server.arg("emailUsuario");

  handleConfirmaDados();
  
}

void handleNotFound()
{ 
    server.sendHeader("Location", "/",true); //Redirect to our html web page 
    server.send(302, "text/plane",""); 
}

void handleConfirmaDados(){
   String s = CONF_page; //Read HTML contents
   server.send(200, "text/html", s); //Send web page
}

void handleConfirm(){
  Serial.println(emailUsuario);
  delay(500);
  server.close();
  WiFi.disconnect();
  delay(100);
  
  ssidWifiConnect = ssidWifi.c_str();
  passwordWifiConnect = passWifi.c_str();
  
  WiFi.begin(ssidWifiConnect,passwordWifiConnect);
  int cont = 0;
  while (WiFi.status() != WL_CONNECTED  && cont <= 10) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    cont++;
    //*****ACENDER LED VERMELHO*************************
  }
  
  if(WiFi.status()== WL_CONNECTED){
      statusESP = "online";
      //*****ACENDER LED VERDE*************************
    }else{
      statusESP = "offline";
  }
  Serial.println(statusESP);
  
      String s = VERIF_page; //Read HTML contents
      server.send(200, "text/html", s); //Send web page
}

void handleEmailConfirm() {
  server.send(200, "text/plane", emailUsuario); //Send ADC value only to client ajax request
}
