//Déclaration des entrées(bouton poussoir et potentiomètre)
#define PIN_POT A0  // Potentiomètre sur A0
#define buttonRed 2  // Bouton rouge
#define buttonGreen 3 // Bouton vert
#define buttonBlue 4 // Bouton bleu

//Déclaration des sorties(LEDs)
#define PIN_RED 9   // LED Rouge sur la broche D9
#define PIN_GREEN 10 // LED Verte sur la broche D10
#define PIN_BLUE 11  // LED Bleue sur la broche D11

//Variables pour l'état des boutons(appuyé ou non)
bool redState = false ;
bool greenState = false ;
bool blueState = false ;

// Durées pour le Morse
#define DOT 200      // Point : 200ms
#define DASH 800     // Trait : 800ms
#define GAP 200      // Pause entre signaux
#define LETTER_GAP 900 // Pause entre lettres


int sequence[] = {2, 2, 4, 2};  // Séquence correcte (Rouge, Rouge, Bleu, Rouge)
int userSequence[4]; //Tableau pour le stockage de la séquence de l'utilisateur
int currentStep = 0; 
const int sequenceLength = 4; //Taille de la séquence(nombre d'appuis)
bool sequenceComplete = false; //Etat de la séquence(correcte ou non)
int mode = 0; //Choix du mode(mode simple ou mode code mystique)

//Initialisation des LEDs
int redValue = 255, greenValue = 255, blueValue = 255;  // Eteindre la LED

void setup() 
{
    //Configuration des broches en sorties 
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    //Configuration des broches en entrées
    pinMode(buttonRed, INPUT_PULLUP);
    pinMode(buttonBlue, INPUT_PULLUP);
    pinMode(buttonGreen, INPUT_PULLUP);
    Serial.begin(9600); //Initialisation de la communication série
}

void loop() {
    int potValue = analogRead(PIN_POT);  // Lire la valeur du potentiomètre
    
     redState = digitalRead(buttonRed) == LOW;  // Vérifie l'état douton rouge (pressé ou non)
     blueState = digitalRead(buttonBlue) == LOW; // Vérifie l'état douton bleu (pressé ou non)
     greenState = digitalRead(buttonGreen) == LOW; // Vérifie l'état douton vert (pressé ou non)
     delay(200);

    if (greenState) { //Si bouton vert appuyé, activé le mode code mystique
        mode = 1;
        Serial.println("Activation du mode Code Mystique !");
        delay(100);
        while (mode == 1) {
          modeSequence(); //Récupéré et vérifier la séquence de l'utilisateur
          delay(100);
        }
    }
    if (potValue < 9) { //Activer le mode simple si la valeur du potentiomètre est inférieure à 9  
        ButonMode(redState, blueState); 
        
    } else if (potValue < 1000) { //Activé le mode Arcane Total si la valeur du potentiomètre est supérieure à 9 et inférieure à 1000  
        ArcEnCiel(potValue);
    } else { //Activé le mode énigme interdite si la valeur du potentiomètre est superieure à 1000
      morseCode();
    }
}


void ArcEnCiel(int potValue)
{
  // Déterminer la couleur selon la plage de valeurs du potentiomètre
     if (10 < potValue && potValue < 146) {  // Couleur Rouge
        redValue = 0; greenValue = 255; blueValue = 255;
    } 
    else if (146 < potValue && potValue < 292) {  // Couleur Orange
        redValue = 0; greenValue = 128; blueValue = 255;
    } 
    else if (292 < potValue && potValue < 438) {  // Couleur Jaune
        redValue = 0; greenValue = 0; blueValue = 255;
    } 
    else if (438 < potValue && potValue < 584) {  // Couleur Verte
        redValue = 255; greenValue = 0; blueValue = 255;
    } 
    else if (584 < potValue && potValue < 730) {  // Couleur Bleu
        redValue = 255; greenValue = 255; blueValue = 0;
    } 
    else if (730 < potValue && potValue < 876) {  // Couleur Indigo
        redValue = 180; greenValue = 250; blueValue = 125;
    } 
    else if (876 < potValue && potValue < 1000) {  // Couleur Violette
        redValue = 100; greenValue = 255; blueValue = 44;
    }

    // Appliquer les couleurs
    analogWrite(PIN_RED, redValue);
    analogWrite(PIN_GREEN, greenValue);
    analogWrite(PIN_BLUE, blueValue);

    delay(50); // Petite pause pour éviter les rafraîchissements trop rapides
}


void ButonMode(bool redState, bool blueState)
{
  if (redState && blueState) { //Allumé la couleur violette si les boutons rouge et bleu sont appuyés au même moment
          analogWrite(PIN_RED, 0);  // Allume la LED rouge à pleine intensité
          analogWrite(PIN_BLUE, 0); // Allume la LED bleu à pleine intensité
          analogWrite(PIN_GREEN, 255); // Eteint la LED verte
      } 
  else if (redState) { //Allumer la couleur rouge si le bouton rouge est appuyé 
          analogWrite(PIN_RED, 0);
          analogWrite(PIN_BLUE, 255);
          analogWrite(PIN_GREEN, 255);
      } 
  else if (blueState) {//Allumer la couleur bleu si le bouton bleu est appuyé 
          analogWrite(PIN_RED, 255);
          analogWrite(PIN_BLUE, 0);
          analogWrite(PIN_GREEN, 255);
      }
  else { //Eteindre la LED si aucun bouton n'est appuyé
          analogWrite(PIN_RED, 255);
          analogWrite(PIN_BLUE, 255);
          analogWrite(PIN_GREEN, 255);
      }
}


void morseCode () {
  if (redState && !blueState) { // Bouton rouge appuyé : Morse "R"
        morse(".-."); // Lettre R
        
    } else if (!redState && blueState) {
        // Bouton bleu appuyé : Morse "B"
        morse("-..."); // Lettre B
        
    } else if (redState && blueState) {// Les deux boutons appuyés : Morse "V"
        
        morse("...-"); // Lettre V
        delay(1000);
        // Ensuite, clignoter la séquence mystique en Morse (rouge, rouge, bleu, rouge -> RRBR)
        morse(".-. .-. -... .-.");
    } else { //Acun bouton pressé : Éteindre la LED
        //setColor(255, 255, 255); 
           analogWrite(PIN_RED, 255);
           analogWrite(PIN_GREEN, 255);
           analogWrite(PIN_BLUE, 255);
    }
  }




void morse(const char* code) {
    while (*code) {
        if (*code == '.') {
            blinkMorse(DOT);
        } else if (*code == '-') {
            blinkMorse(DASH);
        } else if (*code == ' ') {
            delay(LETTER_GAP); // Pause entre lettres
        }
        code++;
    }
    delay(LETTER_GAP); // Pause entre les lettres
}

void blinkMorse(int duration) {
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, HIGH);
    digitalWrite(PIN_BLUE, HIGH);
    delay(duration);
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(PIN_GREEN, HIGH);
    digitalWrite(PIN_BLUE, HIGH);
    delay(GAP);
}


void modeSequence() {
  
    if (digitalRead(buttonGreen) == LOW) {
      Serial.println("Désactivation du mode Code Mystique !");
      mode = 0;
      delay(100);
    }
    if (digitalRead(buttonRed) == LOW) {
        userSequence[currentStep] = 2;  // 2 correspond au bouton rouge
        currentStep++;
        delay(200); // Anti-rebond
    }
    if (digitalRead(buttonBlue) == LOW) {
        userSequence[currentStep] = 4;  // 4 correspond au bouton bleu
        currentStep++;
        delay(200); // Anti-rebond
    }

    if (currentStep == sequenceLength) {
        checkSequence();
    }
}

void checkSequence() { //Vérification de la séquence entrée par l'utilisateur
    bool correct = true;
    for (int i = 0; i < sequenceLength; i++) {
        if (userSequence[i] != sequence[i]) {
            correct = false;
            break;
        }
    }
    
    if (correct) { //Si la séquence est correcte, allumer la couleur violette : rouge + bleu
        Serial.println("Séquence validée, ouverture du coffre !");
        analogWrite(PIN_RED, 0);   // Allume la LED rouge
        analogWrite(PIN_BLUE, 0);  // Allume la LED bleue
        analogWrite(PIN_GREEN, 255); // Éteint la LED verte
        delay(3000);
    } else { //Si la séquence est incorrecte, réinitialiser la séquence saisie
        Serial.println("Séquence incorrecte, réinitialisation...");
    }
    resetSequence();
}

void resetSequence() { //Fonction de réinitialisation
    currentStep = 0;
    for (int i = 0; i < sequenceLength; i++) {
        userSequence[i] = 0; // Réinitialise la séquence saisie
    }
    
    analogWrite(PIN_RED, 255);  // Éteindre la LED rouge
    analogWrite(PIN_BLUE, 255); // Éteindre la LED bleue
    analogWrite(PIN_GREEN, 255); // Éteindre la LED verte
}
