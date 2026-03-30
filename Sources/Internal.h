#ifndef Vx__InternalH
#define Vx__InternalH

#ifdef _DEBUG
  #include <stdio.h> // IWYU pragma: export
  #define Vx__Fatal(MSG) puts(MSG)
#else
  #define Vx__Fatal(MSG)
#endif

#define Vx__FalseCheck(VAL, MSG) if (!VAL) { Vx__Fatal(MSG); return false; }
#define Vx__FalseCheckVoid(VAL) if (!VAL) { return false; }

#endif
