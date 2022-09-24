/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Function test for time and alarm clock management
 **
 ** \addtogroup clock Clock
 ** \brief Time and alarm clock management
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include "unity.h"

/* === Macros definitions ====================================================================== */

//! Cantidad de ticks por segundo utilizado en las pruebas
#define TICKS_PER_SECOND 5

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

static clock_t reloj;

static bool alarma_activada;

/* === Private function implementation ========================================================= */

void SimularTicks(int cantidad) {
    for (int contador = 0; contador < cantidad; contador++) {
        ClockNewTick(reloj);
    }
}

void EventoAlarma(clock_t reloj) {
    alarma_activada = true;
}

/* === Public function implementation ========================================================= */

void setUp(void) {
    static const uint8_t INICIAL[] = {1, 2, 3, 4};

    alarma_activada = false;

    reloj = ClockCreate(TICKS_PER_SECOND, EventoAlarma);
    ClockSetupTime(reloj, INICIAL, sizeof(INICIAL));
}

void test_start_up(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(TICKS_PER_SECOND, EventoAlarma);
    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_set_up_current_time(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_one_second_elapsed(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};
    uint8_t hora[6];

    SimularTicks(TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_one_second_elapsed_with_diferent_frecuency(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 1};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(2, EventoAlarma);
    ClockNewTick(reloj);
    ClockNewTick(reloj);

    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_ten_second_elapsed(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 1, 0};
    uint8_t hora[6];

    SimularTicks(10 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_one_minute_elapsed(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 5, 0, 0};
    uint8_t hora[6];

    SimularTicks(60 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_ten_minute_elapsed(void) {
    static const uint8_t ESPERADO[] = {1, 2, 4, 4, 0, 0};
    uint8_t hora[6];

    SimularTicks(10 * 60 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_one_hour_elapsed(void) {
    static const uint8_t ESPERADO[] = {1, 3, 3, 4, 0, 0};
    uint8_t hora[6];

    SimularTicks(60 * 60 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_ten_hour_elapsed(void) {
    static const uint8_t ESPERADO[] = {2, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    SimularTicks(10 * 60 * 60 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_new_day_arrived(void) {
    static const uint8_t INICIAL[] = {2, 3, 5, 9};
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6];

    ClockSetupTime(reloj, INICIAL, sizeof(INICIAL));
    SimularTicks(60 * TICKS_PER_SECOND);
    ClockGetTime(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

void test_setup_and_get_alarm(void) {
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    uint8_t hora[4];

    ClockSetupAlarm(reloj, ALARMA, sizeof(ALARMA));
    TEST_ASSERT_TRUE(ClockGetAlarm(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ALARMA, hora, sizeof(ALARMA));
}

void test_setup_and_fire_alarm(void) {
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    uint8_t hora[4];

    ClockSetupAlarm(reloj, ALARMA, sizeof(ALARMA));
    SimularTicks(60 * TICKS_PER_SECOND);

    TEST_ASSERT_TRUE(alarma_activada);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
