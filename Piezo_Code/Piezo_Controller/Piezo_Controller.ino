#include <Wire.h>
#include <Adafruit_MCP4725.h>
#define voltsIn A0

Adafruit_MCP4725 dac;

uint32_t dac_value;
String new_dac;
int adcValueRead = 0;
float voltageRead = 0;
float dac_expected_output;
char user_input;
bool entered = false;
int dac_int;
int steps;
float volts = 0;

void setup() {
  Serial.begin(9600);  // Make sure the COM reads the same BAUD rate
  dac.begin(0x60); // The I2C Address: Run the I2C Scanner if you're not sure
  Serial.println("Begin Piezo Control\n");
  Serial.println("1. Set DAC value.");
  Serial.println("2. Increase DAC value by 1");
  Serial.println("3. Decrease DAC value by 1");
  Serial.println("4. Set DAC value steps");
  Serial.println();
  
}

void loop() {
  while (Serial.available()){
    user_input = Serial.read(); // Read user input and trigger appropriate function
      if (user_input == '1'){
        SetDACValue();
      }

      if (user_input == '2'){
        StepUp();
      }

      if (user_input == '3'){
        StepDown();
      }

      if (user_input == '4'){
        SetSteps();
      }
  }

}

void SetDACValue()
{
  entered = false;
  Serial.println("Enter the DAC value you wish to move to: \n");
  while(entered == false){
    new_dac = Serial.readString();
    if (new_dac != ""){
     dac_int = new_dac.toInt();
     dac_value = (uint32_t) dac_int;
     entered = true; 
    }
  }
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value set to: ");
  Serial.println(dac_value);
  Serial.print("Voltage: ");
  Serial.println(volts);
  Serial.println();
  DisplayChoices();
}

void StepUp()
{
  dac_value += (uint32_t) steps;
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value: ");
  Serial.println(dac_value);
  Serial.print("Voltage: ");
  Serial.print(volts);
  Serial.println();
  DisplayChoices();
}

void StepDown()
{
  dac_value -= (uint32_t) steps;
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value: ");
  Serial.println(dac_value);
  Serial.print("Voltage: ");
  Serial.print(volts);
  Serial.println();
  DisplayChoices();
}

void SetSteps()
{
  entered = false;
  String newSteps;
  Serial.println("Enter the number of steps you want to move: \n");
  while (entered == false){
    newSteps = Serial.readString();
    if (newSteps !=0){
      entered = true;
    }
  }
  steps = newSteps.toInt();
  Serial.print("Steps set to: ");
  Serial.println(steps);
  Serial.println();
  DisplayChoices();
}

void DisplayChoices()
{
  Serial.println("1. Set DAC value.");
  Serial.print("2. Increase DAC value by ");
  Serial.println(steps);
  Serial.print("3. Decrease DAC value by ");
  Serial.println(steps);
  Serial.println("4. Set DAC value steps");
  Serial.println();
}

