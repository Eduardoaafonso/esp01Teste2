
void modoAtivo() {
  if (Firebase.getString(firebaseData, pathDataBaseDevice+"/" +currentUID)) {
    if (firebaseData.dataType() == "string") {
      Serial.println(firebaseData.stringData());
      currentUID = firebaseData.stringData();
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
  //jsonTemp.addString("Temperatura","0");
  //jsonUmid.addString("Umidade","0");
  
  if(!Firebase.pathExist(firebaseData, pathDataBaseReads)){
    updateDataRead.addString("Temperatura", "0");
    updateDataRead.addString("Umidade", "0");
    
    if (Firebase.updateNode(firebaseData, pathDataBaseReads+"/"+currentUID+"/"+WiFi.macAddress(), updateDataRead)) {
    
      /*Serial.println(firebaseData.dataPath());
    
      Serial.println(firebaseData.dataType());
    
      Serial.println(firebaseData.jsonData()); */
      statusESP = "funcionamento";
      
    } else {
      //Serial.println(firebaseData.errorReason());
      statusESP = "Inativo";//TRATAR ERRO****************
    }     
  }
}
