// Programa : Envio de texto utilizando Xbee S1
// Autor : Arduino e Cia
// Carrega a biblioteca LiquidCrystal
   
// Define os pinos que serão utilizados para ligação ao display  
int incomingByte = 0;
char buf[20];     //Tamanho da mensagem - 20 caracteres
int num = 0;
String dados;
void setup()
{
  // Inicializacao da serial e mensagem inicial
  Serial.begin(9600);
  Serial.println("Aguardando envio de texto...");
  Serial.println();
}
void loop()
{
  while(Serial.available() > 0)
  {
    // Armazena os caracteres no buffer
    buf[num] = Serial.read();
    // Verifica se foi recebido o caracter de nova linha
    if (buf[num] == 'n') 
    {
      String dados = buf;
      dados.trim();
      int tamanho_string = dados.length();
      
      // Imprime o texto recebido na serial
      Serial.print("Dados recebidos : ");
      Serial.println(dados);
      
      // Apaga o buffer para receber novo texto
      for (int ca =0; ca<20; ca++)
      {
        buf[ca]=0;
      }
      num=0;
      break;
    }
    num++;
  }
}
