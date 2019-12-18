void pagina2() {
  int selected = 99;

  //Serial.println("texto");
  oled.clear();
  oled.set1X();
  oled.println("presiona el boton o ");
  oled.println("gira la perilla que"); 
  oled.println("deseas cambiar");
  for (int i = 0; i < 32; i++) {
    //le asigna un valor a ambos arrays
//    mux[i] = muxPrev[i] = false;
    debounceboton[i] = 0;
    estadobotones[i] = false;
    
  }
  /*Serial.print("Mux:    ");
  for (int i = 0; i < 32; i++) {
    Serial.print((String)  mux[i]+" ");
  }
  Serial.println("");
  Serial.print("MuxPrev ");
    for (int i = 0; i < 32; i++) {
    Serial.print((String)  muxPrev[i]+" ");
  }
  Serial.println("");
*/
  while (selected == 99) {
    for (int i = 0; i < 16; i++)
    {
      //tira voltaje a los mux
      digitalWrite(CONTROL0, (i & 15) >> 3);
      digitalWrite(CONTROL1, (i & 7) >> 2);
      digitalWrite(CONTROL2, (i & 3) >> 1);
      digitalWrite(CONTROL3, (i & 1));
      //direcciona los 3 mux

      if (MUXATIPO == 1)  mux[i] = !digitalRead(MUXA); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
      else mux[i] = (byte) ( analogRead(MUXA) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127

      if (MUXBTIPO == 1)  mux[i + 16] = !digitalRead(MUXB); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
      else mux[i + 16] = (byte) ( analogRead(MUXB) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127

    }
    /* Serial.println("esperando");   // Este bucle maneja entradas.
    Serial.print("Mux:    ");
  for (int i = 0; i < 32; i++) {
    Serial.print((String)  mux[i]+" ");
  }
  Serial.println("");
  Serial.print("MuxPrev ");
    for (int i = 0; i < 32; i++) {
    Serial.print((String)  muxPrev[i]+" ");
  }*/
 // Serial.println("");
    for (int i = 0; i < 32; i++) {
      if (mux[i] != muxPrev[i] && (  millis() - debounceboton[i]) > tiempodebounce) {
        selected = i;
        muxPrev[i] = mux[i]; //resetea para volver a ejecutar el loop y el for y detectar el momento del cambio
        debounceboton[i] = millis();
      }
    }
  }
  //Serial.println("Selecciono algo");
  //Serial.println(selected);
  if (selected < 16) {
    if (MUXATIPO == 1) recambiobotones(selected);
    else recambiopotes(selected);
  }
  else if (selected < 32 && selected > 15) {
    if (MUXBTIPO == 1) recambiobotones(selected);
    else recambiopotes(selected);
  }

  recambionombre(selected);

}
