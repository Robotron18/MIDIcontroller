void pagina1() {

  for (int i = 0; i < 16; i++)
  {
    //tira voltaje a los mux
    digitalWrite(CONTROL0, (i & 15) >> 3);
    digitalWrite(CONTROL1, (i & 7) >> 2);
    digitalWrite(CONTROL2, (i & 3) >> 1);
    digitalWrite(CONTROL3, (i & 1));
    //direcciona los 3 mux

    if (MUXATIPO == 1)  mux[i] = !digitalRead(MUXA); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
    else {
    //  temporalpote=(byte) ( analogRead(MUXA) >> 3); map(analogRead(MUXA),0,1023,0,128);
      temporalpote=(byte)map(analogRead(MUXA),0,1023,0,128);
      mux[i] = (temporalpote * alpha + mux[i] * beta) / (alpha + beta);
      if(mux[i]>=128)mux[i]=127;
      //mux[i] = (byte) ( analogRead(MUXA) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127
    }

    if (MUXBTIPO == 1)  mux[i + 16] = !digitalRead(MUXB); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
    else{
      //temporalpote=(byte) ( analogRead(MUXB) >> 3);
      temporalpote=(byte)map(analogRead(MUXB),0,1023,0,128);
      mux[i + 16] = (temporalpote * alpha + mux[i + 16] * beta) / (alpha + beta);
      if(mux[i+16]>=128)mux[i+16]=127;
     // mux[i + 16] = (byte) ( analogRead(MUXB) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127
    }

  }
  // Este bucle maneja entradas.
  for (int i = 0; i < 32; i++) {
    if (mux[i] != muxPrev[i] && (  millis() - debounceboton[i]) > tiempodebounce) {
      if (i < 16) {
        if (MUXATIPO == 1) manejobotones(i);
        else mensajepotes(i);
      }
      else {
        if (MUXBTIPO == 1) manejobotones(i);
        else mensajepotes(i);
      }
      muxPrev[i] = mux[i]; //resetea para volver a ejecutar el loop y el for y detectar el momento del cambio
      debounceboton[i] = millis();
    }

  }

}

void nombresiguiente(){
  static char numeropreset;
  numeropreset+=wheel;
  wheel=0;
  if(numeropreset>9) numeropreset=9;
  else if(numeropreset<0)numeropreset=0;
  arrayPresets[1]=
  EEPROM.get(sizeof(Preset)*numeropreset, arrayPresets[1]);
}


 
