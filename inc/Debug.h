#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG

#define Debug_Init() \
  do { \
    Serial.begin(115200); \
    delay(2000); \
    Debugln("Serial start..."); \
  } while (0)

#ifdef DEBUG
#define Debug(x) (Serial.print(x))
#define Debugln(x) (Serial.println(x))
#else
#define Debug(x)
#define Debugln(x)
#endif

#endif
