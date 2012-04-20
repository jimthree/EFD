// An Extreeme feedback device for arduino, with two RGB channels of 
// Feedback. Written by Jim Blackhurst - www.jimblackhurst.com

// the EFD looks for a packet to come in on the serial line with the 
// format "%xy" for example "%001008"
// The packet always starts with a percent sign "%" (ascii byte 37)
// If it finds anything else it discards the data and flushes the buffer.
// If it does find a % then it reads the next two bytes as Channel and 
// alert status.  As this is a two channel EFD, channel can only be 0 or 1
// Alert status can any value between 0 and 255.  No error checking is done 
// to detect out of bounds values, the responsibility for this is on the 
// sender.

// Currently this EFD is set up to inidicate the alert status set by
// an application that monitors the activity of the sun (often refered
// to as 'Space Weather'.

// alertStatus holds the alert level of the two different channels as 
// determined by the data passed in via serial 
int alertStatus[2] ={0,0};

// define the pins for each channel and initialise the arrays for 
// holding the value written out to the pins.
int channel1Pins[] = {10,11,9};
int channel2Pins[] = {3,5,6};
int channel1PinValue[] = {0,0,0};
int channel2PinValue[] = {0,0,0};

// more global variable definitions 
int tick = 0;
int frame = 0;
int frameLength = 100;
int numFrames = 0;
int nextFrame = 1;

// The arrays holding the RGB looping colour sequences.
// you can specify an arbitary number of frames, probably a minimum of two. 
// I've no idea what would happen if you only put one in.  the universe would bork probably.
// Each array element (frame) has four values.  the first three are RGB (0-255)
// the Fourth is the number of 'ticks' over which to transition from this frame to the next.
// you can use a tick value of '1' to instanly change to the next frame.  Useful for creating
// harsh flashes.

int noData[][4] = {{0,0,0,1},{0,0,0,10000},{0,0,0,1},{255,0,0,1},{255,0,0,100},{255,0,0,1}};
int normal[][4] = {{255,0,0,10000},{0,255,0,10000},{0,0,255,10000},{0,255,255,10000},{255,255,0,10000},{255,0,255,10000},{255,255,255,10000}};
int active[][4] = {{255,0,0,5000},{255,0,0,10000},{255,0,0,5000},{255,60,0,5000},{255,60,0,10000},{255,60,0,5000}};
int mClass[][4] = {{0,0,200,500},{0,0,200,5000},{0,0,200,500},{255,0,200,500},{255,0,200,5000},{255,0,200,500}};
int xClass[][4] = {{0,0,0,500},{0,0,0,5000},{0,0,0,500},{255,255,200,500},{255,255,200,5000},{255,255,200,500}};
int mega[][4]   = {{255,0,0,100},{0,255,0,100},{0,0,255,100},{0,255,255,100},{255,255,0,100},{255,0,255,100},{255,255,255,100}};

void setup()
{
  Serial.begin(9600); //open serial port
  pinMode(channel1Pins[0], OUTPUT); // define required pins as outputs
  pinMode(channel1Pins[1], OUTPUT);
  pinMode(channel1Pins[2], OUTPUT);
  pinMode(channel2Pins[0], OUTPUT);
  pinMode(channel2Pins[1], OUTPUT);
  pinMode(channel2Pins[2], OUTPUT);
}


void loop()
{
  // check to see if there is any data waiting for us in the serial buffer
  // if there is, parse it and update the alert status for that channel
  checkForData();
  
  // for each channel, create play an appropriate sequence for that channel's
  // alert status
  switch (alertStatus[0]) 
  {
    case 0:
      // the alert function takes the name of the array holdint the sequence, 
      // and the length of the array (which for some unknown reason needs to 
      // be divided by eight to reflect the number of frames)
      alert(noData,sizeof(noData)/8);
      break;
    case 1:
      alert(normal,sizeof(normal)/8);
      break;
    case 2:
      alert(active,sizeof(active)/8);
      break;
    case 3:
      alert(mClass,sizeof(mClass)/8);
      break;
    case 4:
      alert(xClass,sizeof(xClass)/8);
      break;
    case 5:
      alert(mega,sizeof(mega)/8);
      break;
    default: 
      alert(noData,sizeof(noData)/8);
  }
}




