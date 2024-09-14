# create the testing file and list of tests
set (AllTests
    CustomerIdFromUnsignedExplicit.cpp
    CustomerIdFromUnsignedNoImplicit.cpp
    PriceFromLinePriceExplicit.cpp
    PriceFromLinePriceNoImplicit.cpp
    PriceFromQuantityNoExplicit.cpp
    PriceFromQuantityNoImplicit.cpp
)
create_test_sourcelist (AliasTestList AliasTests.cpp ${AllTests})
create_test_sourcelist (EnumClassTestList EnumClassTests.cpp ${AllTests})
create_test_sourcelist (NormalClassTestList NormalClassTests.cpp ${AllTests})
create_test_sourcelist (MixinClassTestList MixinClassTests.cpp ${AllTests})

# add the executable
add_executable (AliasTests ${AliasTestList})
add_executable (EnumClassTests ${EnumClassTestList})
add_executable (NormalClassTests ${NormalClassTestList})
add_executable (MixinClassTests ${MixinClassTestList})

target_include_directories(AliasTests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(EnumClassTests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(NormalClassTests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(MixinClassTests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )

target_compile_definitions(AliasTests PRIVATE TEST_TYPES="lib/alias.hpp")
target_compile_definitions(EnumClassTests PRIVATE TEST_TYPES="lib/enumclass.hpp")
target_compile_definitions(NormalClassTests PRIVATE TEST_TYPES="lib/normalclass.hpp")
target_compile_definitions(MixinClassTests PRIVATE TEST_TYPES="lib/mixinclass.hpp")

# Add all the ADD_TEST for each test
foreach (test ${AllTests})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME "Alias_${TName}" COMMAND AliasTests ${TName})
  set_property(TEST "Alias_${TName}" PROPERTY LABELS Alias)

  add_test (NAME "EnumClass_${TName}" COMMAND EnumClassTests ${TName})
  set_property(TEST "EnumClass_${TName}" PROPERTY LABELS EnumClass)

  add_test (NAME "NormalClass_${TName}" COMMAND NormalClassTests ${TName})
  set_property(TEST "NormalClass_${TName}" PROPERTY LABELS NormalClass)

  add_test (NAME "MixinClass_${TName}" COMMAND MixinClassTests ${TName})
  set_property(TEST "MixinClass_${TName}" PROPERTY LABELS MixinClass)
  endforeach ()