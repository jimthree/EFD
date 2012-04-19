int alertStatus[2] ={0,0};

int channel1Pins[] = {10,11,9};
int channel1PinValue[] = {0,0,0};
//int channel2Pins[] = {3,5,6};
//int channel2PinValue[] = {0,0,0};

int tick = 0;
int frame = 0;
int frameLength = 100;
int numFrames = 0;
int nextFrame = 1;


int noData[][4] = {{0,0,0,1},{0,0,0,10000},{0,0,0,1},{255,0,0,1},{255,0,0,100},{255,0,0,1}};
int normal[][4] = {{255,0,0,10000},{0,255,0,10000},{0,0,255,10000},{0,255,255,10000},{255,255,0,10000},{255,0,255,10000},{255,255,255,10000}};
int active[][4] = {{255,0,0,5000},{255,0,0,10000},{255,0,0,5000},{255,60,0,5000},{255,60,0,10000},{255,60,0,5000}};
int mClass[][4] = {{0,0,200,500},{0,0,200,5000},{0,0,200,500},{255,0,200,500},{255,0,200,5000},{255,0,200,500}};
int xClass[][4] = {{0,0,0,500},{0,0,0,5000},{0,0,0,500},{255,255,200,500},{255,255,200,5000},{255,255,200,500}};
int mega[][4]   = {{255,0,0,100},{0,255,0,100},{0,0,255,100},{0,255,255,100},{255,255,0,100},{255,0,255,100},{255,255,255,100}};

void setup()
{
  Serial.begin(9600);
  pinMode(channel1Pins[0], OUTPUT);
  pinMode(channel1Pins[1], OUTPUT);
  pinMode(channel1Pins[2], OUTPUT);
//  pinMode(channel2Pins[0], OUTPUT);
//  pinMode(channel2Pins[1], OUTPUT);
//  pinMode(channel2Pins[2], OUTPUT);
}


void loop()
{
  checkForData();
  
  
  switch (alertStatus[0]) 
  {
    case 0:
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




