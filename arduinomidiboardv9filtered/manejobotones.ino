void manejobotones(int i) {
  if (bitRead(arrayPresets[presetActual].tipoboton , 32 - i) == 1) {
    //Serial.println("caca");
    botontoggle(i);
  }
  else {
    botonestandar(i);
  }
}

void botontoggle(int i) {


  if (mux[i]) {
    if (!estadobotones[i]) {
      estadobotones[i] = true;
      if (MIDIOUSB) MIDI.sendNoteOn(arrayPresets[presetActual].numero[i], VELOCITY, arrayPresets[presetActual].channel[i]);
      else Serial.println((String) "toggle NOTEON " + arrayPresets[presetActual].numero[i] + " velocity: " + VELOCITY + " Canal: " + arrayPresets[presetActual].channel[i]); //  //nota, velocity, channel
      if(screenActive) mandarmensaje(i, 1,0);
    }
    else {
      estadobotones[i] = false;
      if (MIDIOUSB) MIDI.sendNoteOff(arrayPresets[presetActual].numero[i], 0, arrayPresets[presetActual].channel[i]);
      else Serial.println((String) "toggle NOTEOFF " + arrayPresets[presetActual].numero[i] + " velocity: 0 Canal: " + arrayPresets[presetActual].channel[i]); //  //nota, velocity, channel
      if(screenActive) mandarmensaje(i, 2,0);
    }
  }
}

void botonestandar(int i) {
  if (mux[i] == true) {
    if (MIDIOUSB) MIDI.sendNoteOn(arrayPresets[presetActual].numero[i], VELOCITY, arrayPresets[presetActual].channel[i]);
    else Serial.println((String) "estandar NOTEON:" + arrayPresets[presetActual].numero[i] + " velocity: " + VELOCITY + " Canal: " + arrayPresets[presetActual].channel[i]); //  //nota, velocity, channel
    if(screenActive) mandarmensaje(i, 1,0);
  }
  else {
    if (MIDIOUSB) MIDI.sendNoteOff(arrayPresets[presetActual].numero[i], 0, arrayPresets[presetActual].channel[i]);
    else Serial.println((String) "estandar NOTEOFF:" + arrayPresets[presetActual].numero[i] + " velocity: 0 Canal: " + arrayPresets[presetActual].channel[i]); //  //nota, velocity, channel
    if(screenActive) mandarmensaje(i, 2,0);
  }
}
void mandarmensaje(int i, int tipo, int valor) {
  oled.clear();
  oled.set2X();
  oled.println((String) " " + arrayPresets[presetActual].nombrePreset);

  oled.set1X();
  oled.setFont(newbasic3x5);
  oled.println();
  oled.setFont(lcd5x7);

  oled.set2X();
  if (tipo == 1)  oled.println((String) "NoteOn " + arrayPresets[presetActual].numero[i]);
  else if (tipo == 2) oled.println((String) "NoteOff " + arrayPresets[presetActual].numero[i]);
  else if (tipo == 3) oled.println((String) "CC" + arrayPresets[presetActual].numero[i]+" "+valor);

  oled.set1X();
  if (tipo == 1) oled.println((String) "VEL: " + VELOCITY + " CHAN: " + arrayPresets[presetActual].channel[i]);
  else if (tipo == 2) oled.println((String) "VEL: " + 0 + " CHAN: " + arrayPresets[presetActual].channel[i]);
  else oled.println((String) "CHAN: " + arrayPresets[presetActual].channel[i]);
  oled.println();
  oled.println((String)arrayPresets[1].nombrePreset);
  ultimomensaje=millis();
}
