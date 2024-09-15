# create the testing file and list of tests
set (AllFailures
    AccumulatePriceToTotalPrice.cpp
)
create_test_sourcelist (AliasFailureList AliasFailures.cpp ${AllFailures})
create_test_sourcelist (EnumClassFailureList EnumClassFailures.cpp ${AllFailures})
create_test_sourcelist (NormalClassFailureList NormalClassFailures.cpp ${AllFailures})
create_test_sourcelist (MixinClassFailureList MixinClassFailures.cpp ${AllFailures})

# add the executable
add_executable (AliasFailures ${AliasFailureList})
add_executable (EnumClassFailures ${EnumClassFailureList})
add_executable (NormalClassFailures ${NormalClassFailureList})
add_executable (MixinClassFailures ${MixinClassFailureList})

target_include_directories(AliasFailures PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(EnumClassFailures PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(NormalClassFailures PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(MixinClassFailures PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )

target_compile_definitions(AliasFailures PRIVATE TEST_TYPES="lib/alias.hpp")
target_compile_definitions(EnumClassFailures PRIVATE TEST_TYPES="lib/enumclass.hpp")
target_compile_definitions(NormalClassFailures PRIVATE TEST_TYPES="lib/normalclass.hpp")
target_compile_definitions(MixinClassFailures PRIVATE TEST_TYPES="lib/mixinclass.hpp")

# Add all the ADD_TEST for each test
foreach (test ${AllFailures})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME "Alias_${TName}" COMMAND AliasFailures ${TName})
  set_property(TEST "Alias_${TName}" PROPERTY LABELS Alias)

  add_test (NAME "EnumClass_${TName}" COMMAND EnumClassFailures ${TName})
  set_property(TEST "EnumClass_${TName}" PROPERTY LABELS EnumClass)

  add_test (NAME "NormalClass_${TName}" COMMAND NormalClassFailures ${TName})
  set_property(TEST "NormalClass_${TName}" PROPERTY LABELS NormalClass)

  add_test (NAME "MixinClass_${TName}" COMMAND MixinClassFailures ${TName})
  set_property(TEST "MixinClass_${TName}" PROPERTY LABELS MixinClass)
  endforeach ()