import controlP5.*;

ControlP5 cp5; 
PFont titleFont;
int prevMouseX, prevMouseY;
void setup(){ //same as arduino setup
  
  cp5 = new ControlP5(this);
  titleFont = createFont("Charter-Bold", 30); //create new font with size
  printArray(PFont.list());
  
  size(1000, 600); //set window size
  background(0, 50, 255); //set background color with rgb values
  fill(0, 150, 0); //set text color
  textFont(titleFont); //set text font
  text("NARWHAL Control Panel", 330, 50); //create text ("text", x pos, y pos)
  
  for(int i = 0; i < 30; i++){
    for(int j = 0; j < 20; j++){
      cp5.addButton(i + "," + j).setPosition(120 + i * 25, 80 +  j * 25).setSize(20, 20);
    }
  }
}

void draw(){ //same as loop in arduino
  
  if(mouseX != prevMouseX || mouseY != prevMouseY){
    System.out.println("Mouse X: " + mouseX);
    System.out.println("Mouse Y: " + mouseY);
  }
  
  prevMouseX = mouseX;
  prevMouseY = mouseY;

}
