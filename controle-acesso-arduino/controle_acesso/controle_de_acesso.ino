#include <Keypad.h>
#include <Servo.h>



const int L_VERDE = 10;
const int L_VERMELHO = 11;
const int BUZZER = 12;
const int PINO_SERVO = 13;


const String SENHA = "123";
String digitada = "";

Servo trava;


// ------ teclado -----

const byte LINHAS = 4;
const byte COLUNAS = 4;
char teclas [LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte pinosLinhas[LINHAS] = {9, 8, 7, 6};
byte pinosColunas[COLUNAS] = {5, 4, 3, 2};
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);


void setup() {
  Serial.begin(9600);
  pinMode(L_VERDE, OUTPUT);
  pinMode(L_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  trava.attach(PINO_SERVO);
  trava.write(0);
  Serial.println("Digite a senha e aperte #");
}

void acessoLiberado(){
  Serial.println("\nACESSO LIBERADO");
  digitalWrite(L_VERDE, HIGH);
  tone(BUZZER, 1000, 300);
  trava.write(90);
  delay(3000);
  trava.write(0);
  digitalWrite(L_VERDE, LOW);
}

void acessoNegado(){
  Serial.println("\nACESSO NEGADO");
  digitalWrite(L_VERMELHO, HIGH);
  tone(BUZZER, 300, 600);
  delay(2000);
  digitalWrite(L_VERMELHO, LOW);
}



// ------- inserir senha ----

void loop(){
 char tecla = teclado.getKey();
  if(!tecla) return; // nenhuma tecla apertada
  
  
  if (tecla == '#'){ // confirmar
    if (digitada == SENHA){
      acessoLiberado();
    } else {
      acessoNegado();
}
    
    
    digitada = "";
  } else if (tecla == '*'){ // apagar
    digitada = "";
    Serial.println("\nSenha apagada");
  } else { 			// digitar
    if (digitada.length() < 8){
      digitada += tecla;
  }
    tone(BUZZER, 800, 50);
    Serial.print('*'); // esconde os números
  }
}

    

