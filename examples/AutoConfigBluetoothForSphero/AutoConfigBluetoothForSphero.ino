/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 MOdified on 10-20-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Sphero-Library
************************************************/

void setup(){
    // Give user a chance to power cycle Bluetooth Module
    delay(5000);
    
    // Init USB Serial
    Serial.begin(115200);   // Default Baud Rate
    Serial.println("Initializing Bluetooth");
    
    // Init Blutooth Serial
    // Uncomment to change baud rate
    /*Serial1.begin(115200);
    sendCmd("$$$");    
    sendCmd("U,115200,N");  // *** Replace this with desired Baud Rate ***
    sendCmd("---");
    */
    
    // Reconnect to Bluetooth and configure to master    
    Serial1.begin(115200);  // *** This too ***
    sendCmd("$$$");
    sendCmd("SM,1");
    sendCmd("---");
    
    Serial.println("\nEntering Command Mode");
    sendCmd("$$$");
    
    Serial.println("\nScanning for Spheros...");
    sendCmd("I,10");
}

void loop(){
  long start;
  String line;
  String sphero_id="";
  boolean commandComplete;
  
  line = "";
  commandComplete = false;
  while(!commandComplete){
    while(Serial1.available()){
      unsigned char tmp = Serial1.read();
      if (tmp == '\n'){  // End of Line
        if (line.indexOf("Sphero") != -1){
          //Save result
          //We can't exit because we need to wait for the command to finish
          if (sphero_id == ""){
            sphero_id = line;
            Serial.println(line);
          }
        }
        
        if (line.indexOf("Done") != -1)
          // We can leave now...
          commandComplete = true;
        
        line = "";
      }else
        line.concat(char(tmp));
    }
  }
  
  if (sphero_id != ""){
    Serial.print("Connecting to ");
    Serial.println(sphero_id.substring(13, sphero_id.indexOf(',', 13)));
   
    // Connect to Sphero Address
    sendCmd("C," + sphero_id.substring(0, 12));
    Serial.println("Connected.");
    
    // Save address
    sendCmd("SR," + sphero_id.substring(0, 12));
    
    // Configure Bluetooth to autoreconnect
    sendCmd("SM,3");
    
    // We're done here!
    sendCmd("---");
    Serial.println("\nConfiguration complete!\nYou're Sphero will now autoconnect upon powerup!\n\nHave fun ^^;");
    
    // Idle...
    while(true);
  } 
}

void sendCmd(String cmd){
  String line = "";
  
  // Send command
  if (cmd == "$$$")
    Serial1.print(cmd);
  else
    Serial1.println(cmd);
  
  // Short delay...
  delay(100);
  
  // Show which cmd is being sent
  Serial.println("> " + cmd);
  
  while(1){
    if (Serial1.available()){
      unsigned char tmp = Serial1.read();
      if (tmp == '\n')
        break;
      else
        line.concat(char(tmp));
    }
  }
  
  // Show Response
  Serial.println(line);
}