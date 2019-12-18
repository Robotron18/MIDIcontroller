void doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done
  // Test transition, did things really change? 
  if( digitalRead(ENCODERA) != A_set ) {  // debounce once more
    A_set = !A_set;
    // adjust counter + if A leads B
    if ( A_set && !B_set ) 
      wheel += 1;
    rotating = false;  // no more debouncing until loop() hits again
  }
}
// Interrupt on B changing state, same as A above
void doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(ENCODERB) != B_set ) {
    B_set = !B_set;
    //  adjust counter – 1 if B leads A
    if( B_set && !A_set ) 
      wheel -= 1;
    rotating = false;
  }
}
