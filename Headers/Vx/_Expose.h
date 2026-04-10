/*
  `_Expose.h` - defines macros to expose public functions from the shared library across different platforms.

  Specifically, it defines `Vx__Export`, `Vx__Extern`, and `Vx__Expose`.
  This file is not to be included in user code.
*/

// IWYU pragma: private
// IWYU pragma: no_include

#ifndef Vx__ExposeH
#define Vx__ExposeH

/*
  `Vx__Export` - marks symbols for export if we are building as a shared library.

  When building a shared library with certain compilers or on certain platforms,
  we have to export our symbols explicitly. We use platform or compiler specific
  macros to reliably export our symbols. On unknown systems, or if we are not
  building as shared, the macro is left blank.
*/
#ifdef Vx__Shared
  #ifdef _WIN32
    #ifdef Vx__Build
      #define Vx__Export __declspec(dllimport)
    #else
      #define Vx__Export __declspec(dllexport)
    #endif
  #elif defined(__GNUC__)
    #define Vx__Export __attribute__((visibility("default")))
  #else
    #define Vx__Export
  #endif
#else
  #define Vx__Export
#endif

/*
  `Vx__Extern` - marks symbols as C to make sure C++ compilers don't choke on our code.

  When a C++ compiler tries to compile C code, it cannot recognize the code as such
  and thinks they are C++. This is a problem because C++ mangles all symbol names,
  to make its many useless and stupid features like overloading possible. To shield
  our code from such blasphemy, we use the `extern "C"` syntax to mark our code as C.

  We set this to `extern` if we're not on C++ so that the compiler understands the symbols
  as declared, not defined. I know that nowadays compilers can do all sorts of gymnastics
  and figure this out, but my brain just does not let me ignore small details like this.
  Case in point, I have IWYU pragmas sprinkled all over instead of letting it infer them.
*/
#ifdef __cplusplus
  #define Vx__Extern extern "C"
#else
  #define Vx__Extern extern
#endif

/*
  `Vx__Expose` - combines `Vx__Extern` and `Vx__Export` together to properly declare our symbols.

  This macro combines `Vx__Extern` and `Vx__Export` together so that it is more convenient when
  defining symbols.
*/
#define Vx__Expose Vx__Extern Vx__Export

#endif
