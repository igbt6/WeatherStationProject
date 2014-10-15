/*
 * timeout.h
 *
 *  Created on: 15 paü 2014
 *      Author: lukasz
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "FC1.h"   //freecounter frequency: 32768 HZ
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif






void timeoutInit(void);

bool timeoutIsTimeoutOccured();

void timeoutSetTimeout(uint32_t ms);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TIMEOUT_H_ */
