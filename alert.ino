
void alert(int frames[][4], int num)
{

   if(tick>frames[frame][3])
   {
     tick = 0;
     frame++;
     if (frame>num-1) frame = 0;
   }
   
   nextFrame = frame+1;
   if (nextFrame > num-1) nextFrame = 0;
   
   
   blend(&frames[frame][0],&frames[nextFrame][0],tick,frames[frame][3]);

   analogWrite(channel1Pins[0],255-channel1PinValue[0]);
   analogWrite(channel1Pins[1],255-channel1PinValue[1]);
   analogWrite(channel1Pins[2],255-channel1PinValue[2]);
   
   tick++;
}

void blend(int color_start[],int color_end[],int blend_level, int max_level)
{
	channel1PinValue[0] = (color_start[0] - (blend_level*((color_start[0]-(float)color_end[0])/max_level)));
	channel1PinValue[1] = (color_start[1] - (blend_level*((color_start[1]-(float)color_end[1])/max_level)));
	channel1PinValue[2] = (color_start[2] - (blend_level*((color_start[2]-(float)color_end[2])/max_level)));
}

