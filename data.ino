// this function looks for data in the serial buffer and updates
// the alert status of each channel depending on what it finds

void checkForData()
{
    if (Serial.available()) // is there data waiting for us in the serial buffer?
    {
      // get incoming byte:
      int inByte = Serial.read();
      if (inByte==37) // 37 = '%' (is this the start of a valid packet)
      {
          delay(50); // just give us a momment here to make sure the next byte has arrived
          int channel = Serial.read(); // read it in and add this to a channel buffer
          delay(50); // wait another brief momment 
          int val = Serial.read(); // read the next byte and put this in the Value buffer

          // wirte an acknowledgement back out to the serial port 
          Serial.print(channel);
          Serial.print(":");
          Serial.println(val);
          
          // update the alert status of the channel held in 'channel' with the
          // value held in 'val'
          alertStatus[channel]=val;
        
      }
      else // or if the first byte we see is not a packet start inidicator
      {
        
        Serial.print("ERROR! "); // write an alert back to the serial port
        Serial.println(inByte); // along with the byte that was recived (for debug)
        Serial.flush(); // flush the serial buffer
      }      
    }
}


