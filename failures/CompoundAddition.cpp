#include TEST_TYPES

int CompoundAddition(int, char** const) {
  using namespace phil;
  CompoundAdditionTarget tgt{1};
  tgt += YesCompoundAdditionSource{2};
  return 0;
}

// clang-format: off
//
// MSVC Error messages:
//
// ...\failures\CompoundAddition.cpp(6,7): error C2280: 'phil::CompoundAdditionTarget &phil::CompoundAdditionTarget::operator +=(phil::NoCompoundAdditionSource)': attempting to reference a deleted function [...\build\failures\MixinClassFailures.vcxproj]
//       ...\lib\mixinclass.hpp(64,27):
//       see declaration of 'phil::CompoundAdditionTarget::operator +='
//       ...\lib\mixinclass.hpp(64,27):
//       'phil::CompoundAdditionTarget &phil::CompoundAdditionTarget::operator +=(phil::NoCompoundAdditionSource)': function was explicitly deleted
//   
// ...\failures\CompoundAddition.cpp(6,7): error C2088: built-in operator '+=' cannot be applied to an operand of type 'phil::CompoundAdditionTarget' [...\build\failures\MixinClassFailures.vcxproj]
//
//
// Clang Error messages:
//
// .../failures/CompoundAddition.cpp:6:7: error: overload resolution selected deleted operator '+='
//     6 |   tgt += YesCompoundAdditionSource{2};
//       |   ~~~ ^  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// .../lib/mixinclass.hpp:64:27: note: candidate function has been explicitly deleted
//    64 |   CompoundAdditionTarget& operator+=(NoCompoundAdditionSource) = delete;
//       |                           ^
// 1 error generated.
//
//
// GCC Error messages:
//
// .../failures/CompoundAddition.cpp: In function ‘int CompoundAddition(int, char**)’:
// .../failures/CompoundAddition.cpp:6:37: error: use of deleted function ‘phil::CompoundAdditionTarget& phil::CompoundAdditionTarget::operator+=(phil::NoCompoundAdditionSource)’
//     6 |   tgt += YesCompoundAdditionSource{2};
//       |                                     ^
// In file included from .../failures/CompoundAddition.cpp:1:
// .../lib/mixinclass.hpp:64:27: note: declared here
//    64 |   CompoundAdditionTarget& operator+=(NoCompoundAdditionSource) = delete;
//       | 
//
//
// clang-format: on