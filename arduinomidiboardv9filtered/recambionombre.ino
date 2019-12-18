void recambionombre(int i) {
  /*oled.clear();
    oled.set1X();
    oled.println("Cambio de nombre");
    oled.set2X();
    oled.println(arrayPresets[presetActual].nombrePreset);
    oled.println("^");*/
  for (int k = 0; k < 8; k++) {
    oled.clear();
    oled.set1X();
    oled.println("Cambio de nombre");
    oled.set2X();
    oled.println(arrayPresets[presetActual].nombrePreset);
    for (int f = 0; f < k; f++) {
      oled.print(" ");
    }
    oled.println("^");
    while (!botoncorto) {
      lecturaboton();
      if (wheel != 0) {
        arrayPresets[presetActual].nombrePreset[k] += wheel;

        /*32 a 57
          65 a 90
          97 a 122*/
        if (arrayPresets[presetActual].nombrePreset[k] > 90 && arrayPresets[presetActual].nombrePreset[k] < 97 && wheel>0) {
          arrayPresets[presetActual].nombrePreset[k] = 97;
         //         wheel = 0;

        }
        if (arrayPresets[presetActual].nombrePreset[k] < 97 && arrayPresets[presetActual].nombrePreset[k] > 90&& wheel<0) {
          arrayPresets[presetActual].nombrePreset[k] = 90;
       // wheel = 0;

        }
        if (arrayPresets[presetActual].nombrePreset[k] > 57 && arrayPresets[presetActual].nombrePreset[k] < 65 && wheel>0) {
          arrayPresets[presetActual].nombrePreset[k] = 65;
       // wheel = 0;

        }
        if (arrayPresets[presetActual].nombrePreset[k] < 65 && arrayPresets[presetActual].nombrePreset[k] > 57&& wheel<0) {
          arrayPresets[presetActual].nombrePreset[k] = 57;
     //   wheel = 0;

        }
        wheel = 0;

        if (arrayPresets[presetActual].nombrePreset[k] > 122)arrayPresets[presetActual].nombrePreset[k] = 32;
        else if (arrayPresets[presetActual].nombrePreset[k] < 32)arrayPresets[presetActual].nombrePreset[k] = 122;
        oled.clear();
        oled.set1X();
        oled.println("Cambio de nombre");
        oled.set2X();
        oled.println(arrayPresets[presetActual].nombrePreset);
        for (int f = 0; f < k; f++) {
          oled.print(" ");
        }
        oled.println("^");
      }
    }
    while (botoncorto) {
      lecturaboton();
      //            oled.clear();

      delay(200);
    }
    botoncorto = false;

  }
  // guardar a memoria
  EEPROM.put(sizeof(Preset)*arrayPresets[presetActual].numeroPreset, arrayPresets[presetActual]);

  pagina = 1;
  //  Serial.println("fin recalibracion");
  delay(100);
  botoncorto = false;
  botonlargo = false;
  //wheel=1;
  EEPROM.get(sizeof(Preset)*arrayPresets[presetActual].numeroPreset, arrayPresets[0]);
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
    muxPrev[i] = mux[i];
    muxPrev[i + 16] = mux[i + 16];
  }

  ultimomensaje = 1;
  mensajemain();
  //nombresiguiente();
}
