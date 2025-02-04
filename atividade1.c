#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LEDR 2
#define LEDY 3
#define LEDG 4
#define TROCA_MS 3000 // Tempo de troca: 3 segundos

volatile int state = 0; // 0 = vermelho, 1 = amarelo, 2 = verde
int segundos = 0;

// Callback do temporizador periódico
bool timer_callback(struct repeating_timer *t)
{
    gpio_put(LEDR, 0);
    gpio_put(LEDY, 0);
    gpio_put(LEDG, 0);

    // Alterna entre os estados do semáforo
    switch (state)
    {
    case 0:
        gpio_put(LEDR, 1); // Vermelho
        break;
    case 1:
        gpio_put(LEDY, 1); // Amarelo
        break;
    case 2:
        gpio_put(LEDG, 1); // Verde
        break;
    }

    state = (state + 1) % 3; // Alterna entre os estados
    segundos = segundos + 3;
    printf("segundo(s): %d\n", segundos);
    return true;
}

int main()
{
    stdio_init_all();
    gpio_init(LEDR);
    gpio_init(LEDY);
    gpio_init(LEDG);
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_set_dir(LEDY, GPIO_OUT);
    gpio_set_dir(LEDG, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(TROCA_MS, timer_callback, NULL, &timer);

    while (true)
    {
        // Pausa de 5 segundos para reduzir o uso da CPU.
        sleep_ms(5000);
    }
}
