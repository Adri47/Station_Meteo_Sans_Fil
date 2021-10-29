import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

void setup()
{
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  print(Serial.list());
  String portName = Serial.list()[3]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}
  void draw()
{
  if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('>');         // read it and store it in val
  } 
    if(val !=null)println(val); //print it out in the console
}





import org.gicentre.utils.stat.*; // Import the gicentre utils stat library for chart classes.
import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
XYChart myXYchart;                      // Declare an XYChart object.
XYChart myXYchart1;                      // Declare an XYChart object.
XYChart myXYchart2;                      // Declare an XYChart object.
XYChart myXYchart3;                      // Declare an XYChart object.
XYChart myXYchart4;                      // Declare an XYChart object.

float[] xData ; // x data table.
float[] yData ; // y data table.
float[] buffer; // buffer data table.
float[] buffer1; // buffer data table.
float[] buffer2; // buffer data table.
float[] buffer3; // buffer data table.
float[] buffer4; // buffer data table.


int cpt=0;

void ResetArray(float tab[])
{
  for(int i=0; i<tab.length; i++) {
    tab[i]=0; 
  }
}

void decalagebuffer(float buff[])
{
  for (int i = buff.length-1; i > 0; i--) {
    buff[i] = buff[i-1];
  }
}

/*

void setup() {
  size(1600, 800);
  xData = new float[720]; // x data table.
  yData = new float[720]; // y data table.
  buffer = new float[720]; // y data table.
  buffer1 = new float[720]; // y data table.
  buffer2 = new float[720]; // y data table.
  buffer3 = new float[720]; // y data table.
  buffer4 = new float[720]; // y data table.
  print(Serial.list());
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);

  // XY chart data initialisation.
  for(int i=0; i<xData.length; i++) {
    xData[i]=i;
    yData[i]=sin(radians(xData[i]));// The sin() function takes angles in radians as an input.
  }
  ResetArray(buffer);
  myXYchart = new XYChart(this); // Create an XYChart object.
  myXYchart.setData(xData, yData); // Assign data to the XYChart object.
  myXYchart1 = new XYChart(this); // Create an XYChart object.
  myXYchart1.setData(xData, yData); // Assign data to the XYChart object.

  myXYchart2 = new XYChart(this); // Create an XYChart object.
  myXYchart2.setData(xData, yData); // Assign data to the XYChart object

  myXYchart3 = new XYChart(this); // Create an XYChart object.
  myXYchart3.setData(xData, yData); // Assign data to the XYChart object

  myXYchart4 = new XYChart(this); // Create an XYChart object.
  myXYchart4.setData(xData, yData); // Assign data to the XYChart object

  
  // Chart parameters settings
  myXYchart.setPointSize(0);
  myXYchart.setLineWidth(2);
  myXYchart.setLineColour(color(255,80,80)); //red
  myXYchart.showXAxis(true);
  myXYchart.setXAxisLabel("X axis");
  myXYchart.showYAxis(true);
  myXYchart.setYAxisLabel("Sin(X)");
  myXYchart.setMaxY(1);
  myXYchart.setMinY(-1);

  myXYchart1.setPointSize(0);
  myXYchart1.setLineWidth(2);
  myXYchart1.setLineColour(color(255,100,250)); //pink
  myXYchart1.showXAxis(true);
  myXYchart1.setXAxisLabel("X axis");
  myXYchart1.showYAxis(true);
  myXYchart1.setYAxisLabel("Sin(X)");
  myXYchart1.setMaxY(1);
  myXYchart1.setMinY(-1);

  myXYchart2.setPointSize(0);
  myXYchart2.setLineWidth(2);
  myXYchart2.setLineColour(color(46, 204, 113 ));//green
  myXYchart2.showXAxis(true);
  myXYchart2.setXAxisLabel("X axis");
  myXYchart2.showYAxis(true);
  myXYchart2.setYAxisLabel("Sin2(X)");
  myXYchart2.setMaxY(1);
  myXYchart2.setMinY(-1);


  myXYchart3.setPointSize(0);
  myXYchart3.setLineWidth(2);
  myXYchart3.setLineColour(color(52, 152, 219));//blue
  myXYchart3.showXAxis(true);
  myXYchart3.setXAxisLabel("X axis");
  myXYchart3.showYAxis(true);
  myXYchart3.setYAxisLabel("Sin2(X)");
  myXYchart3.setMaxY(1);
  myXYchart3.setMinY(-1);


  myXYchart4.setPointSize(0);
  myXYchart4.setLineWidth(2);
  myXYchart4.setLineColour(color(244,208,63));//yellow
  myXYchart4.showXAxis(true);
  myXYchart4.setXAxisLabel("X axis");
  myXYchart4.showYAxis(true);
  myXYchart4.setYAxisLabel("Sin2(X)");
  myXYchart4.setMaxY(1);
  myXYchart4.setMinY(-1);


 
  
}

void draw() {
  background(255);
  myXYchart.setData(xData, buffer);
  myXYchart.draw(10,0,width-20, (height/5));

  myXYchart1.setData(xData, buffer1);
  myXYchart1.draw(10,(height/5)*1,width-20, (height/5));

  myXYchart2.setData(xData, buffer2);
  myXYchart2.draw(10,(height/5)*2,width-20, (height/5));

  myXYchart3.setData(xData, buffer3);
  myXYchart3.draw(10,(height/5)*3,width-20, (height/5));

  myXYchart4.setData(xData, buffer4);
  myXYchart4.draw(10,(height/5)*4,width-20, (height/5));

  
  if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
  if(val !=null) println(val);




  buffer[0]=yData[cpt]; 
  buffer1[0]=yData[cpt]; 
  buffer2[0]=yData[cpt]; 
  buffer3[0]=yData[cpt]; 
  buffer4[0]=yData[cpt]; 


  decalagebuffer(buffer);
  decalagebuffer(buffer1);
  decalagebuffer(buffer2);
  decalagebuffer(buffer3);
  decalagebuffer(buffer4);
  


  if (cpt<yData.length-1){
    cpt++;
  }
  else cpt = 0;
    
  // Draw a title over the top of the chart.
  fill(120);
  textSize(20);
  text("Example of a sinus plot using giCentre XYChart", 70,30);
  textSize(11);
  text("Help files are in the Processing/libraries/gicentreUtils/reference folder", 70,45);
}

*/