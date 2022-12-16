// Parlante
const int buzzerPin = 9;
// LEDs
const int ledRojo = 13;
const int ledAzul = 12;
const int ledVerde = 11;
// Potenciómetro y LDR
const int potPin = A0;
const int ldrPin = A1;

// Variables auxiliares
int potValue;
int ldrValue;
int mappedValue;
char op;
int count;

// Declaración de las funciones
void encenderLEDRojo();
void encenderLEDAzul();
void encenderTodosLosLEDs();
void encenderLEDs(unsigned long tiempo = 0)
{
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledAzul, HIGH);
  digitalWrite(ledVerde, HIGH);
  if (tiempo > 0)
  {
    delay(tiempo);
  }
}

void apagarLEDs(unsigned long tiempo = 0)
{
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  if (tiempo > 0)
  {
    delay(tiempo);
  }
}

void setup()
{
    // Configurar el pin del parlante como salida
    pinMode(buzzerPin, OUTPUT);
    // Configurar los pins de los LEDs como salida
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAzul, OUTPUT);
    pinMode(ledRojo, OUTPUT);
    // Iniciar el puerto serie
    Serial.begin(9600);

    // Mostrar el mensaje de ingreso de un número
    Serial.println("Ingrese un numero del 1 al 3: ");
}

void loop()
{
    // Lee el valor del potenciómetro y del LDR
    potValue = analogRead(potPin);
    ldrValue = analogRead(ldrPin);

    // Comprobar si hay datos disponibles en el puerto serie
    if (Serial.available() > 0)
    {
        // Leer el valor del teclado
        op = Serial.read();

        // Verifica si se ha ingresado un número del 1 al 3
        switch (op)
        {
        case '1':
            // Ejecutar la función encenderLEDRojo
            encenderLEDRojo();
            break;
        case '2':
            // Ejecutar la función encenderLEDAzul
            encenderLEDAzul();
            break;
        case '3':
            // Ejecutar la función encenderTodosLosLEDs
            encenderTodosLosLEDs();
            break;

        // Valor por defecto en caso de elegir un número que no está en la sugerencia
        default:
            // Mostrar el mensaje de ingreso de un número inválido
            Serial.println("Ingrese un valor valido: ");
            break;
        }
    }
}

void encenderLEDRojo()
{
    // Encender el LED rojo, apagar los otros LEDs y generar un tono en el parlante
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);

    // Inicializar la variable count en cero
    count = 0;

    // Bucle que se ejecuta continuamente
    while (true)
    {
        // Leer el valor del potenciómetro
        potValue = analogRead(potPin);

        // Convertir el valor del potenciómetro en un valor entre 0 y 255
        mappedValue = map(potValue, 0, 1023, 0, 255);

        // Generar un tono en el buzzer con la frecuencia calculada
        if (mappedValue > 10)
        {
            tone(buzzerPin, potValue);
        }
        else
        {
            noTone(buzzerPin);
        }

        // Esperar 10 milisegundos
        delay(10);

        // Comprobar si count es igual a cero
        if (count == 0)
        {
            // Mostrar el mensaje de ingreso de un número
            Serial.println("Ingrese un numero del 1 al 3: --1--");

            // Actualizar la variable count con uno
            count = count + 1;
        }

        // Comprobar si hay datos disponibles en el puerto serie
        if (Serial.available())
        {
            // Leer el valor del teclado
            op = Serial.read();

            // Verificar si se ha ingresado un número diferente de 1
            if (op != '1')
            {
                // Salir del bucle
                break;
            }
        }
    }
}
void encenderLEDAzul()
{
    // Encender el LED azul, apagar los otros LEs y generar un tono en el parlante
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, LOW);

    // Inicializar la variable count en cero
    count = 0;

    // Bucle que se ejecuta continuamente
    while (true)
    {
        // Leer el valor del potenciómetro
        ldrValue = analogRead(ldrPin);

        // Convertir el valor del potenciómetro en un valor entre 0 y 255
        mappedValue = map(ldrValue, 0, 1023, 0, 255);

        // Generar un tono en el buzzer con la frecuencia calculada
        if (mappedValue > 10)
        {
            tone(buzzerPin, ldrValue);
        }
        else
        {
            noTone(buzzerPin);
        }

        // Esperar 10 milisegundos
        delay(10);

        // Comprobar si count es igual a cero
        if (count == 0)
        {
            // Mostrar el mensaje de ingreso de un número
            Serial.println("Ingrese un numero del 1 al 3: --2--");

            // Actualizar la variable count con uno
            count = count + 1;
        }

        // Comprobar si hay datos disponibles en el puerto serie
        if (Serial.available())
        {
            // Leer el valor del teclado
            op = Serial.read();

            // Verificar si se ha ingresado un número diferente de 2
            if (op != '2')
            {	
              	// Sllenciamos el parlante
              	noTone(buzzerPin);
              	// Apagar LEDS
  				apagarLEDs();
                // Salir del bucle
                break;
            }
        }
    }
}
void encenderTodosLosLEDs()
{
  // Encender leds 5s
  encenderLEDs(5000);

  // Apagar 1s
  apagarLEDs(1000);

  // Encender leds 2s
  encenderLEDs(2000);

  // Apagar
  apagarLEDs();

  // Comprobar si hay datos disponibles en el puerto serie
  if (Serial.available())
  {
    // Leer el valor del teclado
    op = Serial.read();

    // Verificar si se ha ingresado un número diferente de 3
    if (op != '3')
    {
      return;
    }
  }
}