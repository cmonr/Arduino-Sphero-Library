#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2,3);

void setup(){
    delay(10000);
    
    // Init USB Serial
    Serial.begin(115200);
    Serial.println("Initializing Bluetooth");
    
    
    // Init Blutooth Serial
    // (Configure to 9600 baud for more reliable communication)
    bluetooth.begin(115200);
    bluetooth.print("$$$");
    delay(100);
    bluetooth.print("U,9600,N");
    delay(100);
    bluetooth.println('---');
    delay(1000);
    
    // Reconnect to Bluetooth
    bluetooth.begin(9600);
    delay(1000);
    
    
    Serial.println("Entering Command Mode");
    bluetooth.print("$$$");
    
    delay(4000);
    bluetooth.flush();
    
    Serial.println("Scanning for Spheros...");
    //bluetooth.println();
}

void loop(){
  long start;
    String line;
    String sphero_id="";
    boolean commandComplete;
    
    bluetooth.print("I\n");
    
    line = "";
    commandComplete = false;
    while(!commandComplete){
        while(bluetooth.available()){
            //Serial.write(bluetooth.read());
            unsigned char tmp = bluetooth.read();
            if (tmp == '\n'){  // End of Line
                if (line.indexOf(",") == 12){
                    //Save result
                    // We can't exit because we need to wait for the command to finish
                    if (sphero_id == ""){
                      //Serial.println(line);
                      sphero_id = line;
                    }
                }
                if (line.indexOf("Done") != -1)
                  commandComplete = true;
                
                line = "";
            }else
                line.concat(char(tmp));
        }
    }
    
    // Flush excess characters
    bluetooth.flush();
    
    //Serial.println();
    delay(1000);
    
    if (sphero_id != ""){
      Serial.print("Connecting to ");
      Serial.println(sphero_id.substring(13, sphero_id.indexOf(',', 13)));
     
      // Connect to Sphero Address
      bluetooth.print("C,");
      bluetooth.println(sphero_id.substring(0, 12));
      
      commandComplete = false;
      while(!commandComplete){
          while(bluetooth.available()){
              //Serial.write(bluetooth.read());
              unsigned char tmp = bluetooth.read();
              if (tmp == '\n'){  // End of Line
                // TODO: Check for successful connection
                 commandComplete = true;   
              }
          }
      }
      
      Serial.println("Connected.");
      
      // Save address
      bluetooth.print("SR,");
      bluetooth.println(sphero_id.substring(0, 12));
      delay(250);
      
      // Configure Bluetooth to autoreconnect
      bluetooth.println("SM,3");
      delay(250);
      
      // Disconnect from Command Mode
      bluetooth.println("---");
      delay(250);
      
      // We're done here!
      Serial.println("\nConfiguration complete!\nYou're Sphero will now autoconnect upon powerup!\n\nHave fun ^^;");
      
      // Idle...
      while(true);
    }
    
    Serial.println("Scanning...");
}