#include <stdio.h> // Biblioteca padrão da linguagem C
#include "pico/stdlib.h" // Subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" // Biblioteca para controle de PWM

#define PWM_PIN 22 // GPIO 22 para controle do servomotor

// Função para configurar o PWM
void setup_pwm() {
    // Configura o pino GPIO 22 para PWM
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    // Obter o número do slice PWM para a GPIO 22
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);

    // Configuração do PWM (50Hz = período de 20ms)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.0f); // Para 50Hz (125MHz / 50 = 125)
    pwm_init(slice_num, &config, true); // Inicia o PWM

    // Definir o período de 20ms (20000 microssegundos)
    pwm_set_wrap(slice_num, 20000 - 1);
}

// Função para configurar a posição do servomotor
void set_servo_position(uint slice_num, uint duty_us) {
    // Define o ciclo ativo para a posição desejada
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_us);
}

// Função para movimentar o servomotor entre 0 e 180 graus suavemente de forma infinita
void smooth_movement(uint slice_num) {
    int duty;
    
    while (true) {
        // Movendo de 0 para 180 graus (500 µs a 2400 µs)
        for (duty = 500; duty <= 2400; duty += 5) {
            set_servo_position(slice_num, duty);
            sleep_ms(10); // Espera 10 ms entre os ajustes para suavizar o movimento
        }

        // Movendo de 180 para 0 graus (2400 µs a 500 µs)
        for (duty = 2400; duty >= 500; duty -= 5) {
            set_servo_position(slice_num, duty);
            sleep_ms(10); // Espera 10 ms entre os ajustes para suavizar o movimento
        }
    }
}

int main() {
    stdio_init_all(); // Inicializa a biblioteca de I/O

    // Configurar PWM na GPIO 22
    setup_pwm();

    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN); // Obter o número do slice para a GPIO 22

    // Posição de 180 graus (ciclo ativo de 2400 µs)
    printf("Movendo para 180 graus...\n");
    set_servo_position(slice_num, 2400);
    sleep_ms(5000); // Aguarda 5 segundos na posição 180 graus

    // Posição de 90 graus (ciclo ativo de 1470 µs)
    printf("Movendo para 90 graus...\n");
    set_servo_position(slice_num, 1470);
    sleep_ms(5000); // Aguarda 5 segundos na posição 90 graus

    // Posição de 0 graus (ciclo ativo de 500 µs)
    printf("Movendo para 0 graus...\n");
    set_servo_position(slice_num, 500);
    sleep_ms(5000); // Aguarda 5 segundos na posição 0 graus

    // Movimentação suave infinita entre 0 e 180 graus
    printf("Movimentação suave infinita entre 0 e 180 graus...\n");
    smooth_movement(slice_num);

    return 0;
}
