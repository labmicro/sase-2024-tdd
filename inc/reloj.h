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

#ifndef RELOJ_H
#define RELOJ_H

/** \brief Declarations for time and alarm clock management
 **
 ** \addtogroup clock Clock
 ** \brief Time and alarm clock management
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "reloj.h"
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

//! Puntero a un descriptor de reloj
typedef struct clock_s * clock_t;

//! Puntero a función para notificación de eventos de reloj
typedef void (*clock_event_t)(clock_t clock);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Función para iniciar el reloj
 *
 * @param ticks_per_second Cantidad de pulsos que debe recibir para contar un segundo
 *
 * @return Puntero con el descriptor del nuevo reloj creado
 */
clock_t ClockCreate(uint16_t ticks_per_second, clock_event_t event_handler);

/**
 * @brief Funcion para obtener la hora actual del reloj
 *
 * @param clock Puntero al descriptor obtenido al crear el reloj
 * @param time Vector donde se devuelve la hora, minutos y segundos en formato BCD
 * @param size Cantidad de elementos disponibles en el vector de resultado
 *
 * @return true La hora es válida
 * @return false El reloj no fué ajustado y por lo tanto la hora no es válida
 */
bool ClockGetTime(clock_t clock, uint8_t * time, uint8_t size);

/**
 * @brief Función para poner en hora el reloj
 *
 * @param clock Puntero al descriptor obtenido al crear el reloj
 * @param time Vector que contiene la hora, minutos y segundos a configurar en formato BCD
 * @param size Cantidad de elementos en el vector con la hora a configurar
 */
void ClockSetupTime(clock_t clock, uint8_t const * const time, uint8_t size);

/**
 * @brief Función para contar un nuevo tick de reloj y actualizar la hora
 *
 * @param clock Puntero al descriptor obtenido al crear el reloj
 */
void ClockNewTick(clock_t clock);

/**
 * @brief Función para fijar la hora de la alarma del reloj
 *
 * @param clock Puntero al descriptor obtenido al crear el reloj
 * @param time Vector que contiene la hora, minutos y segundos a configurar en formato BCD
 * @param size Cantidad de elementos en el vector con la hora a configurar
 */
void ClockSetupAlarm(clock_t clock, uint8_t const * const time, uint8_t size);

/**
 * @brief Funcion para obtener la hora y el estado actual de la alarma del reloj
 *
 * @remarks La función se puede utilizar con el puntero en el valor NULL y el parametro
 * size en cero para consultar solo si la alarma esta habilitada.
 *
 * @param clock Puntero al descriptor obtenido al crear el reloj
 * @param time Vector donde se devuelve la hora, minutos y segundos en formato BCD
 * @param size Cantidad de elementos disponibles en el vector de resultado
 *
 * @return true La alarma se encuentra activada y sonará a la hora fijada
 * @return false La alarma se encuentra deshabilitad y no sonará a la hora fijada
 */
bool ClockGetAlarm(clock_t clock, uint8_t * time, uint8_t size);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* RELOJ_H */