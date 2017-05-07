    /*  
    Pinagem Leitor RFID:
    
    O leitor RFID tem 8 pinos que seguem a seguinte
    sequência de ligação.
    
    Atenção à tensão de alimentação, que neste caso é de 3.3 volts

    Pino SDA  ligado na porta 10 do Arduino
    Pino SCK  ligado na porta 13 do Arduino
    Pino MOSI ligado na porta 11 do Arduino
    Pino MISO ligado na porta 12 do Arduino
    Pino NC – Não conectado
    Pino GND  ligado no pino GND do Arduino
    Pino RST  ligado na porta 9 do Arduino
    Pino 3.3 – ligado ao pino 3.3 V do Arduino
    
    Pinagem do LCD
    
    GND => (-)
    VCC => 5V
    SDA => A4
    SCL => A5 
    */
    
 
   #include <SPI.h>
   #include <MFRC522.h>
   #include <LiquidCrystal_I2C.h>
   #include <Wire.h> 
   int led = 3;
   #define SS_PIN 10
   #define RST_PIN 9
   MFRC522 mfrc522(SS_PIN, RST_PIN);

   
 
   LiquidCrystal_I2C lcd(39,16,2);
 
   char st[20];
 
   void setup()
   {
    
   pinMode(led, OUTPUT);
   digitalWrite(led, LOW); 
     
   Serial.begin(9600);   // Inicia a serial
   SPI.begin();          // Inicia  SPI bus
   mfrc522.PCD_Init();   // Inicia MFRC522
    
   lcd.init();           // Inicia o LCD 
   lcd.backlight();      // Ativa a Luz de Fundo do LCD
  
   mensageminicial();
   }
 
   void loop()
   {
   if ( ! mfrc522.PICC_IsNewCardPresent())
   {
   return;
   }
  
   if ( ! mfrc522.PICC_ReadCardSerial())
   {
   return;
   }
   
   Serial.print("UID da tag :");   // Mostra UID na serial
   String conteudo= "";
   byte letra;
   for (byte i = 0; i < mfrc522.uid.size; i++)
   {
   Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
   Serial.print(mfrc522.uid.uidByte[i], HEX);
   conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
   conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   Serial.println();
  
   conteudo.toUpperCase();
     
   if (conteudo.substring(1) == "72 AA 7A 6F") //UID 1 - Chaveiro
   {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("  Usuario - 01");
   lcd.setCursor(0,1);
   lcd.print("Acesso liberado!");
   
   digitalWrite(led, HIGH);
   delay(3000);
   digitalWrite(led, LOW);
   delay(3000);   
      
   mensageminicial();
   }
 
   if (conteudo.substring(1) == "A3 91 3A 02")
   {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("  Usuario - 02");
   lcd.setCursor(0,1);
   lcd.print("Acesso liberado!");
   
   digitalWrite(led, HIGH);
   delay(3000);
   digitalWrite(led, LOW);
   delay(3000);
 
   mensageminicial();
   }
 
   if (conteudo.substring(1) != "72 AA 7A 6F")
   if (conteudo.substring(1) != "A3 91 3A 02")
   {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Usuario Invalido");
   lcd.setCursor(0,1);
   lcd.print("Cartao Invalido");
   delay(3000);
   mensageminicial();
   }
   }
 
   void mensageminicial()
   {
   lcd.clear();
   lcd.print(" Aproxime o seu"); 
   lcd.setCursor(0,1);
   lcd.print("cartao do leitor"); 
   }
