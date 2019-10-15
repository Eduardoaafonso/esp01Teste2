void setupLoop2()
{
  xTaskCreatePinnedToCore(
    loop2,                       /* Function to implement the task */
    "loop2 ",                    /* Name of the task */
    8192,                           /* Stack size in words */
    NULL,                           /* Task input parameter */
    1,                              /* Priority of the task */
    NULL,                           /* Task handle. */
    0);                             /* Core where the task should run */

    //setWatchDog(); //seta o WatchDog
}


void loop2( void * pvParameters )
{
  //Serial.printf("\nloop2() em core: %d", xPortGetCoreID());//Mostra no monitor em qual core o loop2() foi chamado
  while (1)
  {


  delay(1);
  }
}
