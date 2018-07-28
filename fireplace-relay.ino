int relay = D0;
int relay_state = 0;
char localIp[] = "xxx.xxx.xxx.xxx";

void setup(){

   pinMode(relay, OUTPUT);

   Particle.function("relay", relayToggle);
   Particle.function("relayState", relayState);
   digitalWrite(relay, HIGH);
    
   Partile.variable("localIp", localIp);
   Particle.variable("relayState", relay_state);
    
   setLocalIp();
}

void setLocalIp(){
    IPAddress myAddr = WiFi.localIP();

    byte first_octet = myAddr[0];
    byte second_octet = myAddr[1];
    byte third_octet = myAddr[2];
    byte fourth_octet = myAddr[3];

     sprintf(localIp, "%d.%d.%d.%d", first_octet, second_octet, third_octet, fourth_octet);
}

void loop(){
   // Nothing to do here
}

int relayToggle(String command) {

    if (command=="off") {
        digitalWrite(relay,HIGH);
        Particle.publish("fireplace", "off", 60, PRIVATE);
        relay_state = 1;
        return 0;
    }
    else if (command=="on") {
        digitalWrite(relay,LOW);
        Particle.publish("fireplace", "on", 60, PRIVATE);
        relay_state = 0;
        return 1;
    }
    else {
        if(digitalRead(relay) == HIGH){
            digitalWrite(relay, LOW);
            relay_state = 0;
        }
        else{
            digitalWrite(relay, HIGH);
            relay_state = 1;
        }
        return 2;
    }
}

int getSwitchState(){
    relay_state = digitalRead(relay)==HIGH?1:0;
    return relay_state;
}

int relayState(String cmd){
    return getSwitchState();
}

