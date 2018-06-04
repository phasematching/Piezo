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

void setup(void) {
  Serial.begin(9600);
  dac.begin(0x60); // The I2C Address: Run the I2C Scanner if you're not sure
  Serial.println("Begin Piezo Control\n");
  Serial.println("1. Set DAC value.");
  Serial.println("2. Increase DAC value by 1.");
  Serial.println("3. Decrease DAC value by 1.\n");
  
}

void loop() {
  while (Serial.available()){
    user_input = Serial.read(); // Read user input and trigger appropriate function
      if (user_input == '1'){
        SetDACValue();
      }

      if (user_input == '2'){
        StepOneUp();
      }

      if (user_input == '3'){
        StepOneDown();
      }
  }

}

void SetDACValue()
{
  while(entered == false){
    new_dac = Serial.readString();
    if (new_dac != ""){
     dac_int = new_dac.toInt();
     dac_value = (uint32_t) dac_int;
     entered = true; 
    }
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value set to: ");
  Serial.println(dac_value);
  }
}

void StepOneUp()
{
  dac_value++;
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value: ");
  Serial.println(dac_value);
}

void StepOneDown()
{
  dac_value--;
  dac.setVoltage(dac_value, false);
  Serial.print("DAC value: ");
  Serial.println(dac_value);
}

void DisplayChoices()
{
  Serial.println("1. Set DAC value.");
  Serial.println("2. Increase DAC value by 1.");
  Serial.println("3. Decrease DAC value by 1.\n");
}

