/// PROJETO DE UM CONTROLADOR PI BASICO  - LINCOMAR - UFU

/// ENTRADAS PARA O PARAÍSO <3
#define pSENSOR  A0
#define pSTEP    A1
#define pCONTROLE 3

/// VALORES DE TEMPO

float deltaTime,
      lastTime;

/// VALORES QUE QUEREMOS VER
int    cap= 0,
       tep= 0;
double Vcap=0;

/// CONTROLE P OU PROPORCIONAL
double error = 0;
  
double kp=0.4,
       ki=3.0; 

double P = 0.0,
       I = 0.0; 
       
double pid = 0;

double pwm = 0;

int controlePwm = 0;


/// VALOR QUE DESEJAMOS OU SETPOINT
double setPoint = 512;



void setup(){
  Serial.begin(9600);
  
/// DEFINE ENTRADAS E SAÍDAS PARA O NOSSO CORAÇÃO
  pinMode(pSENSOR,    INPUT);
  pinMode(pSTEP,      INPUT);
  pinMode(pCONTROLE, OUTPUT);

/// INICIA O PWM EM ZERO QUE É O CONTROLE DE UMA RESPOSTA AO IMPULSO QUE ESTAMOS FAZENDO LOGO COMEÇA EM ZERO
  analogWrite(pCONTROLE,0);
  
/// ATÉ HOJE NÃO SEI O QUE É ESSA LINHA DE CODIGO
  Serial.begin(9600);

/// DELAY IGUAL O QUE A GENTE TEM NA HORA DA PROVA  
  delay(5000);

/// INICIA O RELOGIO
  lastTime = millis();
}

void loop(){
/// O QUE SERA MOSTRADO NO GRAFICO
  cap = analogRead(pSENSOR);
  tep = analogRead(pSTEP);
  Serial.print(cap);
  Serial.print(",");
  Serial.println(tep);

/// LEITURA USADA PARA O PID
  Vcap = analogRead(pSENSOR);

/// REALIMENTAÇAO HAHAHAHA
  error  = setPoint - Vcap;

/// CONTROLE PROPORCIONAL 
  P = error*kp;
  
/// CONTROLE INTEGRAL
  deltaTime = (millis() - lastTime) / 1000.0;
  lastTime = millis();
  I = I + (error * ki) * deltaTime;

/// SOMA DE TUDO QUANDO ELA EXISTIR
  pid = map(P+I, 0, 1024, 0, 255);

/// CONTROLE PWM

  pwm = pid + map(setPoint, 0, 1024, 0, 255);
  
/// CORREÇÕES PWM
  if(pwm>255){
    pwm = 255;
  }
  if(pwm<0){
    pwm = 0;
  }
  
  controlePwm = (pwm);
  analogWrite(pCONTROLE, controlePwm); 
}

