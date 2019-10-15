void modoAP() {
  WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
  
    dnsServer.start(DNS_PORT, "fikiria.com", local_ip);
    
    server.on("/", handleRoot);      //This is display page
    server.on("/dadosUsuario", handleDadosUsuario);
    server.on("/emailConfirm", handleEmailConfirm);
    server.on("/confirm", handleConfirm); 
    server.onNotFound(handleNotFound);
    server.begin();                  //Start server
  
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

}
