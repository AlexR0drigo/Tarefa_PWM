#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/pwm.h" // Biblioteca para controle de PWM

#define PWM_SERVO 22 // Pino do SERVO conectado à GPIO como PWM (22) Caso for testar na Placa BitDogLab, modificar para o pino 12 
const uint16_t WRAP_PERIOD = 20000; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 125.0; // Divisor do clock para o PWM
const uint16_t SERVO_STEP = 5; // Passo de incremento/decremento para o duty cycle do SERVO
uint16_t SERVO_LEVEL = 500; // Nível inicial do PWM (duty cycle)

// Função para configurar o módulo PWM
void pwm_setup() {
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO); // Obtém o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); // Define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); // Define o valor de wrap (período do PWM)
    pwm_set_gpio_level(PWM_SERVO, SERVO_LEVEL); // Define o ciclo de trabalho inicial (duty cycle)
    pwm_set_enabled(slice, true); // Habilita o PWM no slice correspondente
}

int main() {
    stdio_init_all(); 
    pwm_setup(); // Configura o PWM

    uint up_down = 1; // Variável para controlar se o nível do SERVO aumenta ou diminui

    // Movimentos iniciais do servo (0, 90 e 180 graus)
    printf("Movendo para 180 graus...\n");
    pwm_set_gpio_level(PWM_SERVO, 2400);
    sleep_ms(5000);

    printf("Movendo para 90 graus...\n");
    pwm_set_gpio_level(PWM_SERVO, 1470);
    sleep_ms(5000);

    printf("Movendo para 0 graus...\n");
    pwm_set_gpio_level(PWM_SERVO, 500);
    sleep_ms(5000);

    printf("Iniciando movimento entre 0 e 180 graus...\n");
    // Loop principal para aumentar e deminuir grau do servo gradualemte (Com o led, aumenta e diminui sua intensidade)
    while (true) {

        pwm_set_gpio_level(PWM_SERVO, SERVO_LEVEL); // Atualiza o duty cycle
        sleep_ms(10); // Atraso de 10ms

        if (up_down) {
            SERVO_LEVEL += SERVO_STEP; // Incrementa o nível do servomotor
            if (SERVO_LEVEL >= 2400) // Limita ao valor máximo permitido
                up_down = 0; // Muda direção para diminuir
        } else {
            SERVO_LEVEL -= SERVO_STEP; // Decrementa o nível do servomotor
            if (SERVO_LEVEL <= 500) // Limita ao valor mínimo permitido
                up_down = 1; // Muda direção para aumentar
        }
    }
}