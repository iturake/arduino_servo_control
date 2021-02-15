#include<Servo.h>
Servo servo_1, servo_2, servo_3, servo_4;
char uart_rx_data[18];
int angle_values[4] = {0, 0, 0, 0};

//Prototypes Function Define
void RAKE_UART_Rx_Data(int order, int value);
 
void setup() {
  
 //Seri Port Start 9600 Boudrate
 Serial.begin(9600);

 //Servo data pin define
 servo_1.attach(3);
 servo_2.attach(5);
 servo_3.attach(6);
 servo_4.attach(9);
 
 while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
 }
 }
void loop(){

  //Uart data type template
  //"Svvv-vvv-vvv-vvvCF" 
  //S = start bit
  //vvv = angle value of servo (0-180)
  //C = control bit
  //F = finish bit
 if(Serial.available()>0){
  Serial.readBytes(uart_rx_data,18);

  angle_values[0] = ((uart_rx_data[1]-'0')*100)+((uart_rx_data[2]-'0')*10)+((uart_rx_data[3]-'0'));
  angle_values[1] = ((uart_rx_data[5]-'0')*100)+((uart_rx_data[6]-'0')*10)+((uart_rx_data[7]-'0'));
  angle_values[2] = ((uart_rx_data[9]-'0')*100)+((uart_rx_data[10]-'0')*10)+((uart_rx_data[11]-'0'));
  angle_values[3] = ((uart_rx_data[13]-'0')*100)+((uart_rx_data[14]-'0')*10)+((uart_rx_data[15]-'0'));

  for (int i = 0; i < 4; i++) {
  RAKE_UART_Rx_Data(i+1, angle_values[i]);
  } 
 }
}

void RAKE_UART_Rx_Data(int order, int value) {
  if(order == 1) {
  Serial.print("angle_value_1= ");
  Serial.println(value);
  servo_1.write(value);
  }
  else if(order==2) {
  Serial.print("angle_value_2= ");
  Serial.println(value);
  }
  else if(order==3) {
  Serial.print("angle_value_3= ");
  Serial.println(value);
  servo_3.write(value);
  }
  else if(order==4) {
  Serial.print("angle_value_4= ");
  Serial.println(value);
  servo_4.write(value);
  }
 }
