/*
 * timeout.c

 *
 *  Created on: 15 paŸ 2014
 *      Author: lukasz
 */

#include "timeout.h"

typedef struct {
	volatile bool interruptOccured; /*set TRUE by interrupt, when we have received a block of data*/
	FC1_TValueType timeVal;
} Timeout_UsrData;

typedef struct {
	LDD_TDeviceData* mTimeout;
	Timeout_UsrData mTimeoutUsrData;
} TimeoutHandle;

static TimeoutHandle mTimeoutHandle;

void timeoutInit(void) {

	mTimeoutHandle.mTimeout = FC1_Init(&mTimeoutHandle.mTimeoutUsrData);
	if (mTimeoutHandle.mTimeout == NULL) {
		while (1)
			; //init failed
	}

	mTimeoutHandle.mTimeoutUsrData.interruptOccured = false;
	mTimeoutHandle.mTimeoutUsrData.timeVal = 0;

}

void timeoutSetTimeout(uint32_t ms) {
	if (mTimeoutHandle.mTimeout == NULL) {
		while (1)
			; //perform init before
	}
	mTimeoutHandle.mTimeoutUsrData.timeVal = ms;
	FC1_ResetCounter(mTimeoutHandle.mTimeout);
}

bool timeoutIsTimeoutOccured() {
	FC1_TValueType timeVal = FC1_GetCounterValue(mTimeoutHandle.mTimeout);
	uint32_t miliseconds = 0;
	/* Calculation of milliseconds */
#if FC1_COUNTER_DIR==0    //UP direction    miliseconds= timeVal*1000/FC1_CNT_INP_FREQ_U_0;#else         // DOWN direction	miliseconds = ((FC1_TValueType)(-timeVal)) *1000/FC1_CNT_INP_FREQ_U_0;#endif

	if (miliseconds > mTimeoutHandle.mTimeoutUsrData.timeVal)
		return true;
	return false;
}
