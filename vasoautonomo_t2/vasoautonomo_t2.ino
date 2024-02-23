const byte alimentazioneSensore = 10;
const byte pinSensore = A0;
const int relay = 2;

// cambiare i valori in in funzione della calibrazione

// Valore limite di terreno umido.
// Valori inferiori indicano terreno troppo umido
const int terrenoUmido = 350;

// Valore limite di terreno secco.
// Valori superiori indicano terreno troppo secco
const int terrenoSecco = 550;

void setup() {
  // Impostiamo il pin digitale 12 come OUTPUT
  pinMode(alimentazioneSensore, OUTPUT);

  // All'avvio impostiamo a LOW il +Vcc del sensore
  digitalWrite(alimentazioneSensore, LOW);

  //impostiamo il pin 3 del relay su output
  pinMode(relay, OUTPUT);

  // impostiamo la velocità della porta seriale
  Serial.begin(9600);
}

void loop() {
  // Lettura del sensore

  int umiditaTerreno = leggiSensore();
  Serial.print("Uscita analogica: ");
  Serial.println(umiditaTerreno);
  Serial.println("-----------------------------");
  Serial.println();
  Serial.println("----- Stato del terreno -----");
  Serial.println();

  // verifica livello umidità del terreno

  if (umiditaTerreno < terrenoUmido) {
    digitalWrite(relay, HIGH);
    Serial.println("    Terreno troppo umido");
    Serial.println();
    

  } else if (umiditaTerreno >= terrenoUmido && umiditaTerreno < terrenoSecco) {
    Serial.println("-----------------------------");
    Serial.println("Umidità del terreno ottimale");
  } else {
    Serial.println("    Terreno troppo secco");
    Serial.println();
    digitalWrite(relay, LOW);
    Serial.println("relay acceso");
    delay(900);
    digitalWrite(relay, HIGH);
    Serial.println("relay spento");
  }
  Serial.println("-----------------------------");
  Serial.println();

  delay(5400000);
}

// Funzione che permette la lettura del livello di
// umidità del terreno

int leggiSensore() {
  digitalWrite(alimentazioneSensore, HIGH);   // attiva il sensore - viene fornita alimentazione
  delay(50);                                  // breve attesa di 50 ms prima di effettuare la lettura
  int valoreUmidita = analogRead(pinSensore); // legge il valore e lo si memorizza nella variabile livelloLiquido
  digitalWrite(alimentazioneSensore, LOW);    // togliamo alimentazione al sensore
  return valoreUmidita;                       // invia alla funzione chiamante il valore letto
}
