

// projeto final sirene 02 tons (horn hi-yelp)
// finalizado dia 29/04/2017 - 08:30
// desenvolvedor: Noberto Maciel

#include <NewTone.h>
#include <Bounce2.h>

#define tempo 10
#define intervalo 50

int frequencia = 0;
int Pinofalante = 10; // pino utilizado na placa eh o 10 para testes com micro speaker utilizar o pino 11
int Botao_horn = 3; // aciona o horn - pino 3
int Botao_yelp = 5; // aciona/desaciona yelp - pino 5
int estado=0;  // guarda o valor 0 ou 1 (HIGH ou LOW)
int val1 = HIGH;
int val2 = HIGH;

Bounce debouncer_horn = Bounce();
Bounce debouncer_yelp = Bounce();


void setup()
{ 
  pinMode(Pinofalante,OUTPUT); //Pino do buzzer
  pinMode(Botao_horn,INPUT_PULLUP); //Pino do Botao_horn
  pinMode(Botao_yelp,INPUT_PULLUP); //Pino do Botao_yelp

  debouncer_horn.attach(Botao_horn);       // Informa que o tratamento de debouce será feito no pino horn;
  debouncer_yelp.attach(Botao_yelp);       // Informa que o tratamento de debouce será feito no pino yelp;  
  debouncer_horn.interval(intervalo);             // Seta o intervalo de trepidação;
  debouncer_yelp.interval(intervalo);             // Seta o intervalo de trepidação;    
}

void loop()
{
  int sirene; // declara a varivel da funcao de sirene
  debouncer_horn.update();        // Executa o algorítimo de tratamento;  
  debouncer_yelp.update();        // Executa o algorítimo de tratamento; 
  int val1 = debouncer_horn.read();  // Lê o valor tratado do botão;
  int val2 = debouncer_yelp.read();  // Lê o valor tratado do botão;


  // o Botao_horn pressionado em negativo, positivo no resistor
  if (val1 == LOW) {
         sirene = sirene_0(); // executa o horn

  }  
  
  if (val2 == LOW) {
    sirene = sirene_1();
  }  
  
}
  // sirene horn (padrao de 29-01-2017 = 450 a 1200)
  int sirene_0(){
     for (frequencia = 550; frequencia <= 1300; frequencia += 5)
     {
      NewTone(Pinofalante, frequencia, tempo);
        if (debouncer_horn.read() == HIGH) { // se o Botao_horn foi solto, interrompa a funcao
          return 0;
        }       
     }
  }
  
  // sirene yelp com interrupcao no Botao_horn  (padrao de 29-01-2017 = 300 a 1900)
  int sirene_1(){
     for (frequencia = 300; frequencia < 1900; frequencia += 2) 
     {
        // parada atraves do Botao_horn
        if (debouncer_horn.read() == LOW) { // se botao horn foi pressionado enquanto yelp ativo
          return 0;
        }
       NewTone(Pinofalante, frequencia, tempo);        
     }
     
     for (frequencia = 1900; frequencia > 300; frequencia -= 2) 
     {
        // parada atraves do Botao_horn
        if (debouncer_horn.read() == LOW) { // se botao horn foi pressionado enquanto yelp ativo
          return 0;
        }       
       NewTone(Pinofalante, frequencia, tempo); 
       
     }
  }
