#include <stdio.h> // Biblioteca padrão da linguagem C
#include "pico/stdlib.h" // Biblioteca central do SDK Pico
#include "hardware/pwm.h" // Biblioteca para controle de PWM

#define PWM_LED 22 // Pino do LED conectado à GPIO como PWM
const uint16_t WRAP_PERIOD = 20000; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 125.0; // Divisor do clock para o PWM
const uint16_t LED_STEP = 5; // Passo de incremento/decremento para o duty cycle do LED
uint16_t led_level = 500; // Nível inicial do PWM (duty cycle)

// Função para configurar o módulo PWM
void pwm_setup() {
    gpio_set_function(PWM_LED, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_LED); // Obtém o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); // Define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); // Define o valor de wrap (período do PWM)
    pwm_set_gpio_level(PWM_LED, led_level); // Define o ciclo de trabalho inicial (duty cycle)
    pwm_set_enabled(slice, true); // Habilita o PWM no slice correspondente
}

int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O
    pwm_setup(); // Configura o PWM

    uint slice = pwm_gpio_to_slice_num(PWM_LED); // Obtém o número do slice PWM
    uint up_down = 1; // Variável para controlar se o nível do LED aumenta ou diminui

    // Movimentos iniciais do servo (0, 90 e 180 graus)
    printf("Movendo para 180 graus...\n");
    pwm_set_gpio_level(PWM_LED, 2400);
    sleep_ms(5000);

    printf("Movendo para 90 graus...\n");
    pwm_set_gpio_level(PWM_LED, 1470);
    sleep_ms(5000);

    printf("Movendo para 0 graus...\n");
    pwm_set_gpio_level(PWM_LED, 500);
    sleep_ms(5000);

    // Loop principal para aumentar e diminuir o brilho gradualmente
    while (true) {

        pwm_set_gpio_level(PWM_LED, led_level); // Atualiza o duty cycle

        if (up_down) {
            led_level += LED_STEP; // Incrementa o nível do LED
            if (led_level >= 2400) // Limita ao valor máximo permitido
                up_down = 0; // Muda direção para diminuir
        } else {
            led_level -= LED_STEP; // Decrementa o nível do LED
            if (led_level <= 500) // Limita ao valor mínimo permitido
                up_down = 1; // Muda direção para aumentar
        }

        sleep_ms(10);
    }
}
