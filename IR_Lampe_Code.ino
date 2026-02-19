#include <IRremote.h> // Inclure la Bibliothèque IRemote pour pouvoir recupérer les informations envoyées par la commande 

/*
===========================================================
              CONFIGURATION DES BROCHES
===========================================================
*/

// Broche du récepteur infrarouge
int PIN_IR = 8;

// Broche de commande du module relais
int relay_pin = 7;

// Variable qui stockera le code du bouton pressé
int iValue;


void setup() {
  
  // Initialisation de la communication série
  // Permet d'afficher les codes IR reçus dans le Moniteur Série
  Serial.begin(9600);

  // Initialisation du récepteur IR sur la broche définie
  IrReceiver.begin(PIN_IR);

  // Définition de la broche du relais en sortie
  pinMode(relay_pin, OUTPUT);

  /*
  -----------------------------------------------------------
  INITIALISATION DU RELAIS
  -----------------------------------------------------------
  La majorité des modules relais sont de type "Active LOW".

  Cela signifie :
  - LOW  → Relais ACTIVÉ
  - HIGH → Relais DÉSACTIVÉ

  Pour éviter que le relais ne s'active au démarrage,
  on le met immédiatement à HIGH.
  -----------------------------------------------------------
  */
  digitalWrite(relay_pin, HIGH);
}


/*
===========================================================
        COMMENT UTILISER CE PROGRAMME AVEC
              VOTRE TÉLÉCOMMANDE IR
===========================================================

1) Téléverser d’abord le programme de lecture IR 
   pour récupérer les codes de votre télécommande.

2) Ouvrir le Moniteur Série.

3) Appuyer sur les boutons souhaités et noter
   les valeurs affichées.

4) Remplacer les valeurs dans le switch-case ci-dessous.

Exemple :
Si le bouton ON affiche 45 → écrire : case 45:
Si le bouton OFF affiche 46 → écrire : case 46:

Cela rend le programme compatible avec
n'importe quelle télécommande infrarouge.
===========================================================
*/


void loop() {

  // Vérifie si un signal IR a été reçu
  if (IrReceiver.decode()) {

    // Récupération du code correspondant au bouton pressé
    iValue = IrReceiver.decodedIRData.command;

    // Affichage du code dans le Moniteur Série
    Serial.print("Code reçu : ");
    Serial.println(iValue);
    
    /*
    -----------------------------------------------------------
                      STRUCTURE DE DÉCISION
    -----------------------------------------------------------
    En fonction du bouton pressé, on active ou désactive
    le relais.
    -----------------------------------------------------------
    */
    switch (iValue) {

      case 22:         // Bouton ON → Activer le relais
        digitalWrite(relay_pin, LOW);
        Serial.println("Relais activé (Lampe ON)");
        break;

      case 13:         // Bouton OFF → Désactiver le relais
        digitalWrite(relay_pin, HIGH);
        Serial.println("Relais désactivé (Lampe OFF)");
        break;
      
      default:
        // Si le bouton n'est pas reconnu,
        // aucune action n'est exécutée
        break;
    }

    // Prépare le récepteur à recevoir la prochaine commande
    IrReceiver.resume();
  }
}
