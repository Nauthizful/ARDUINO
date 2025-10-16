#include <Servo.h>

//Déclaration des entrées
#define JOYSTICK_X A2
#define JOYSTICK_Y A3
#define JOYSTICK_BUTTON 1

#define SERVO_CONTINU_PIN A4 // Moteur continu
#define SERVO_MOTEUR_PIN A5 // Moteur 180

//Déclaration des valeurs pour l'axe X du joystick
#define ANALOG_X_CENTER 92
#define ANALOG_X_DEADZONE_MAX 96
#define ANALOG_X_DEADZONE_MIN 85

//Déclaration des valeurs pour l'axe Y du joystick
#define MOTEUR_Y_MIN 90
#define MOTEUR_Y_MAX 180

//Déclaration des variables qui liront les entrées analaogiques
long joystick_x;
long joystick_y;

//Déclaration des servos
Servo continu;
Servo moteur;

void setup()
{
  //Initialisation des entrées
  pinMode(JOYSTICK_X, INPUT_PULLUP);
  pinMode(JOYSTICK_Y, INPUT_PULLUP);

  //Permet de choisir les pins qui sont utilisés comme sortie pour les servos
  continu.attach(SERVO_CONTINU_PIN);
  moteur.attach(SERVO_MOTEUR_PIN);
}

void loop()
{
  //Permet de limiter les valeurs renvoyées par le joystick à quelquechose d'utilisable pour le servo
  joystick_x = map(analogRead(JOYSTICK_X), 0, 1023, 75, 115);
 
  //Pour chaque moteur, la valeur correspodante est appliquée
  continu.write(deadZone(joystick_x)); // Applique une zone morte sur l'axe X du joystick
  moteur.write(moteurY());
}

/********************************************************
Permet d'appliquer une zone sur l'axe X du joystick
pour éviter que le moteur ne bouge quand le joystick
est au centre.

Args:
  x (int): Valeur lue sur l'axe X du joystick
*********************************************************/
int deadZone(int x) 
{
  // Si la valeur lue est dans la zone morte, on la remplace par la valeur où le moteur ne bouge pas
  if(x >= ANALOG_X_DEADZONE_MIN && x <= ANALOG_X_DEADZONE_MAX)
  {
    x = ANALOG_X_CENTER;
  }

  return x;
} 

/********************************************************
Si le joystick est dans un sens, on tourne le 
moteur au maximum dans une direction, sinon dans l'autre.
*********************************************************/
int moteurY(){
  // 800 et 200 sont des valeurs choisis arbitrairement et correpondent à la motié de la course du joystick
  // Si le joystick est au milieu, le moteur reste en place
  if(analogRead(JOYSTICK_Y) > 800){
    return MOTEUR_Y_MAX;
  }
  if(analogRead(JOYSTICK_Y) < 200){
    return MOTEUR_Y_MIN;
  } 
}