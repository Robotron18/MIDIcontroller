void recambiopotes(int i) {
  int temporal = arrayPresets[presetActual].numero[i];
  boolean estado = false;
  oled.clear();
  oled.set1X();
  oled.println("Control Change");
  oled.set2X();
  oled.println(temporal);
  botoncorto=false;
  while (!botoncorto) {
    if (wheel != 0) {
      temporal += wheel;
      wheel = 0;
      if (temporal > 127) temporal -= 127;
      else if (temporal < 1) temporal += 127;
      oled.clear();
      oled.set1X();
      oled.println("Control Change");
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
}
