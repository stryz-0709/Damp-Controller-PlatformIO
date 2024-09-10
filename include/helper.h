#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include "global.h"

void esp1PinSetup();

void esp2PinSetup();

bool isNumber(String payload);

void backgroundCheck();

bool readInputs();

void decodePendingMessage(String pendingMessage);


#endif