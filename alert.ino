// this function renders the current 'tick' (position between frames) 

void alert(int frames[][4], int num) // accept the sequence name and it's length
{
  
  // if we get to the last tick, move to the next frame
  if(tick>frames[frame][3])
   {
     tick = 0;
     frame++;
     if (frame>num-1) frame = 0; // if we are at the last frame, move back to the first
   }
   
   nextFrame = frame+1; // nextFrame is the next frame in the sequence
   if (nextFrame > num-1) nextFrame = 0; // but it can also be the first one, if the current frame is the last
   
   // call the blend function with the current frame, next frame, our current position 
   // in the transition (tick) and the number of ticks.  This will update the pin values
   blend(&frames[frame][0],&frames[nextFrame][0],tick,frames[frame][3]); 

   // write the pin values out too the pins.  the "255-" allows us to use
   // common annode LEDs, remove this for common cathode, or individual LEDs
   analogWrite(channel1Pins[0],255-channel1PinValue[0]);
   analogWrite(channel1Pins[1],255-channel1PinValue[1]);
   analogWrite(channel1Pins[2],255-channel1PinValue[2]);
   
   tick++; // move on please.
}


// this function does the blending between frames over a period of time based cutr up into ticks.
// it's based on some code from the arduino forums by 'SirPoonga' in this thread.
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1279754605

void blend(int color_start[],int color_end[],int blend_level, int max_level)
{
	channel1PinValue[0] = (color_start[0] - (blend_level*((color_start[0]-(float)color_end[0])/max_level)));
	channel1PinValue[1] = (color_start[1] - (blend_level*((color_start[1]-(float)color_end[1])/max_level)));
	channel1PinValue[2] = (color_start[2] - (blend_level*((color_start[2]-(float)color_end[2])/max_level)));
}

