                                                                                                                                                                                                                                                                                                                                                                                                                    void mensajepotes(int i) {


  if (MIDIOUSB) MIDI.sendControlChange(arrayPresets[presetActual].numero[i], mux[i], arrayPresets[presetActual].channel[i]);
  else Serial.println((String) "Control Change:" + arrayPresets[presetActual].numero[i] + " Valor" + mux[i] + " Canal:" + arrayPresets[presetActual].channel[i]); //  //nota, velocity, channel
  if(screenActive) mandarmensaje(i, 3,mux[i]);

}
