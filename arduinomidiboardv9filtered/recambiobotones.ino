void recambiobotones(int i) {
  int temporal = arrayPresets[presetActual].numero[i];
  boolean estado = false;
  delay(100);
  //botoncorto=false;
  oled.clear();
  oled.set1X();
  oled.println("NOTE ON");
  oled.set2X();
  oled.println(temporal);
  while (!botoncorto) {
    if (wheel != 0) {
      temporal += wheel;
      wheel = 0;
      if (temporal > 127) temporal -= 127;
      else if (temporal < 1) temporal += 127;
      oled.clear();
      oled.set1X();
      oled.println("NOTE ON");
      oled.set2X();
      oled.println(temporal);
    }
    lecturaboton();
  }
  while (botoncorto) {
    lecturaboton();
    oled.clear();

    delay(200);
  }
  arrayPresets[presetActual].numero[i] = temporal;
  botoncorto = false;
  temporal = arrayPresets[presetActual].channel[i];
  oled.clear();
  oled.set1X();
  oled.println("Channel");
  oled.set2X();
  oled.println(temporal);
  while (!botoncorto) {
    if (wheel != 0) {
      temporal += wheel;
      wheel = 0;
      if (temporal > 16) temporal -= 16;
      else if (temporal < 1) temporal += 16;
      oled.clear();
      oled.set1X();
      oled.println("Channel");
      oled.set2X();
      oled.println(temporal);
    }

    lecturaboton();
  }
  while (botoncorto) {
    lecturaboton();
    oled.clear();

    delay(200);
  }
  arrayPresets[presetActual].channel[i] = temporal;
  botoncorto = false;
  temporal = 1;
  oled.clear();
  oled.set1X();
  oled.println("Tipo de boton");
  oled.set2X();
  if ((temporal & 1) == 0) {
    oled.println("Con retencion");
    estado = true;
  }
  else {
    oled.println("Sin retencion");
    estado = false;
  }
  while (!botoncorto) {
    if (wheel != 0) {
      temporal += wheel;
      //   Serial.println((String) "Estado rueda " + temporal);
      if ((temporal & 1) == 0) estado = true;
      else estado = false;
      wheel = 0;
      oled.clear();
      oled.set1X();
      oled.println("Tipo de boton");
      oled.set2X();
      if (estado) oled.println("Con retencion");
      else oled.println("Sin retencion");
    }

    lecturaboton();
  }
  while (botoncorto) {
    lecturaboton();
    oled.clear();
    delay(200);
  }
  if (estado)   bitSet( arrayPresets[presetActual].tipoboton, (32 - i));
  else bitClear( arrayPresets[presetActual].tipoboton, (32 - i));
  botoncorto = false;
  //for(int j=0;j<32;j++)  Serial.print((String)arrayPresets[presetActual].numero[j]+" ");
  //Serial.println("");
  //Serial.println(arrayPresets[presetActual].tipoboton,BIN);
}
