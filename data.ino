void checkForData()
{
    if (Serial.available())
    {
      // get incoming byte:
      int inByte = Serial.read();
      if (inByte==37) // 37 = '%'
      {
          Serial.print("Got Data:");
          delay(50);
          int channel = Serial.read();
          delay(50);
          int val = Serial.read();
          Serial.print(channel);
          Serial.print(":");
          Serial.println(val);
          
          alertStatus[channel]=val;
          //Serial.print("Channel One now at alert level: ");
          //Serial.println(alertStatus[0]);
          //Serial.print("Channel Two now at alert level: ");
          //Serial.println(alertStatus[1]);
        
      }
      else 
      {
        
        Serial.print("ERROR! ");
        Serial.println(inByte);
        Serial.flush();
      }      
    }
}


