#include <Firebase_ESP_Client.h>
#include <WiFi.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Sangita Yadav"
#define WIFI_PASSWORD "7975568374"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBFa_iZq43uK7nliGysZcF7C17diN9an9o"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://med-dispens-default-rtdb.firebaseio.com"  

//Define Firebase Data object
FirebaseData fbdo;

/* 4. Define the user Email and password that alreadey registerd or added in your project */
//#define USER_EMAIL "pratyush252003@gmail.com"
//#define USER_PASSWORD "pratyush#64"

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
int intValue2;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

 /* Assign the user sign in credentials */
 // auth.user.email = USER_EMAIL;
  //auth.user.password = USER_PASSWORD;
  
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();


   if (Firebase.RTDB.setFloat(&fbdo, "Val", 100)) {

}
else {
  Serial.println("FAILED");
  Serial.println("REASON: " + fbdo.errorReason());
}

    
    if (Firebase.RTDB.getInt(&fbdo, "Humid")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    if (Firebase.RTDB.getInt(&fbdo, "Temp")) {
            if (fbdo.dataType() == "int") {
        intValue2 = fbdo.intData();
        Serial.println(intValue2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}


   
