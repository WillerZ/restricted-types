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
// ...\RestrictedTypes\failures\CompoundAddition.cpp(6,7): error C2280: 'phil::CompoundAdditionTarget &phil::CompoundAdditionTarget::operator +=(phil::NoCompoundAdditionSource)': attempting to reference a deleted function [...\RestrictedTypes\build\failures\MixinClassFailures.vcxproj]
//       ...\RestrictedTypes\lib\mixinclass.hpp(64,27):
//       see declaration of 'phil::CompoundAdditionTarget::operator +='
//       ...\RestrictedTypes\lib\mixinclass.hpp(64,27):
//       'phil::CompoundAdditionTarget &phil::CompoundAdditionTarget::operator +=(phil::NoCompoundAdditionSource)': function was explicitly deleted
//   
// ...\RestrictedTypes\failures\CompoundAddition.cpp(6,7): error C2088: built-in operator '+=' cannot be applied to an operand of type 'phil::CompoundAdditionTarget' [...\RestrictedTypes\build\failures\MixinClassFailures.vcxproj]
//
//
//
// clang-format: on