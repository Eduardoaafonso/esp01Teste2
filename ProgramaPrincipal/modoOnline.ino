
void modoOnline() {
  
//Criando campos no DataBase

if(!Firebase.pathExist(firebaseData, pathDataBaseDevice)){
    updateDataDevice.addString("Email",emailUsuario);
    updateDataDevice.addString("CurrentUID",currentUID);
    updateDataDevice.addString("Status","criado");
    updateDataDevice.addString("Nome", Nomeplano);
    updateDataDevice.addString("MAC Adress", WiFi.macAddress());
    
    //updateData.addString("data1","value1").addJson("data2", &json);
    
    if (Firebase.updateNode(firebaseData, pathDataBaseDevice, updateDataDevice)) {
    
      /*Serial.println(firebaseData.dataPath());
    
      Serial.println(firebaseData.dataType());
    
      Serial.println(firebaseData.jsonData()); */
      statusESP = "criado";
      
    } else {
      //Serial.println(firebaseData.errorReason());
      statusESP = "NaoCriado";//TRATAR ERRO****************
    }     
  }


  if(!Firebase.pathExist(firebaseData, pathDataBasePlan)){
    updateDataPlan.addString("Nome", Nomeplano);
    updateDataPlan.addString("Tempo", "60");
    
    //updateData.addString("data1","value1").addJson("data2", &json);
    
    if (Firebase.updateNode(firebaseData, pathDataBasePlan, updateDataPlan)) {
    
      /*Serial.println(firebaseData.dataPath());
    
      Serial.println(firebaseData.dataType());
    
      Serial.println(firebaseData.jsonData()); */
      statusESP = "criado";
      
    } else {
      //Serial.println(firebaseData.errorReason());
      statusESP = "NaoCriado";//TRATAR ERRO****************
    }     
  }
}
