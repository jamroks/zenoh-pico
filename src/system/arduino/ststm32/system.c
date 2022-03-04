/*
 * Copyright (c) 2017, 2021 ADLINK Technology Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Apache License, Version 2.0
 * which is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *
 * Contributors:
 *   ADLINK zenoh team, <zenoh@adlink-labs.tech>
 */

#include "zenoh-pico/system/platform.h"
#include <hw/driver/delay.h>

/*------------------ Task ------------------*/
int z_task_init(z_task_t *task, z_task_attr_t *attr, void *(*fun)(void *), void *arg)
{
    return 0;
}

int z_task_join(z_task_t *task)
{
    return 0;
}

int z_task_cancel(z_task_t *task)
{
    return 0;
}

void z_task_free(z_task_t **task)
{
    z_task_t *ptr = *task;
    free(ptr);
    *task = NULL;
}

/*------------------ Mutex ------------------*/
int z_mutex_init(z_mutex_t *m)
{
    return 0;
}

int z_mutex_free(z_mutex_t *m)
{
    return 0;
}

int z_mutex_lock(z_mutex_t *m)
{
    return 0;
}

int z_mutex_trylock(z_mutex_t *m)
{
    return 0;
}

int z_mutex_unlock(z_mutex_t *m)
{
    return 0;
}

/*------------------ Condvar ------------------*/
int z_condvar_init(z_condvar_t *cv)
{
    return 0;
}

int z_condvar_free(z_condvar_t *cv)
{
    return 0;
}

int z_condvar_signal(z_condvar_t *cv)
{
    return 0;
}

int z_condvar_wait(z_condvar_t *cv, z_mutex_t *m)
{
    return 0;
}

/*------------------ Sleep ------------------*/
int z_sleep_us(unsigned int time)
{
    return usleep(time);
}

int z_sleep_ms(unsigned int time)
{
    return usleep(1000 * time);
}

int z_sleep_s(unsigned int time)
{
    return sleep(time);
}

/*------------------ Instant ------------------*/
void _zn_clock_gettime(clockid_t clk_id, z_clock_t *ts)
{
    uint64_t m = millis();
    ts->tv_sec = m / 1000000;
    ts->tv_nsec = (m % 1000000) * 1000;
}

z_clock_t z_clock_now()
{
    z_clock_t now;
    _zn_clock_gettime(NULL, &now);
    return now;
}

clock_t z_clock_elapsed_us(z_clock_t *instant)
{
    z_clock_t now;
    _zn_clock_gettime(NULL, &now);

    clock_t elapsed = (1000000 * (now.tv_sec - instant->tv_sec) + (now.tv_nsec - instant->tv_nsec) / 1000);
    return elapsed;
}

clock_t z_clock_elapsed_ms(z_clock_t *instant)
{
    z_clock_t now;
    _zn_clock_gettime(NULL, &now);

    clock_t elapsed = (1000 * (now.tv_sec - instant->tv_sec) + (now.tv_nsec - instant->tv_nsec) / 1000000);
    return elapsed;
}

clock_t z_clock_elapsed_s(z_clock_t *instant)
{
    z_clock_t now;
    _zn_clock_gettime(NULL, &now);

    clock_t elapsed = now.tv_sec - instant->tv_sec;
    return elapsed;
}

/*------------------ Time ------------------*/
struct timeval z_time_now()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return now;
}

time_t z_time_elapsed_us(struct timeval *time)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    time_t elapsed = (1000000 * (now.tv_sec - time->tv_sec) + (now.tv_usec - time->tv_usec));
    return elapsed;
}

time_t z_time_elapsed_ms(struct timeval *time)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    time_t elapsed = (1000 * (now.tv_sec - time->tv_sec) + (now.tv_usec - time->tv_usec) / 1000);
    return elapsed;
}

time_t z_time_elapsed_s(struct timeval *time)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    time_t elapsed = now.tv_sec - time->tv_sec;
    return elapsed;
}