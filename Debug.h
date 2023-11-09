#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define Debug_Init() (Serial.begin(115200))
#define Debug(x) (Serial.print(x))
#define Debugln(x) (Serial.println(x))
#else
#define Debug_Init()
#define Debug(x)
#define Debugln(x)
#endif

#endif
