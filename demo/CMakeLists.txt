# create the testing file and list of tests
set (AllDemos
    DivZero.cpp
)
create_test_sourcelist (AliasDemoList AliasDemos.cpp ${AllDemos})
create_test_sourcelist (EnumClassDemoList EnumClassDemos.cpp ${AllDemos})
create_test_sourcelist (NormalClassDemoList NormalClassDemos.cpp ${AllDemos})
create_test_sourcelist (MixinClassDemoList MixinClassDemos.cpp ${AllDemos})

# add the executable
add_executable (AliasDemos ${AliasDemoList})
add_executable (EnumClassDemos ${EnumClassDemoList})
add_executable (NormalClassDemos ${NormalClassDemoList})
add_executable (MixinClassDemos ${MixinClassDemoList})

target_include_directories(AliasDemos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(EnumClassDemos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(NormalClassDemos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )
target_include_directories(MixinClassDemos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
        )

target_compile_definitions(AliasDemos PRIVATE TEST_TYPES="lib/alias.hpp")
target_compile_definitions(EnumClassDemos PRIVATE TEST_TYPES="lib/enumclass.hpp")
target_compile_definitions(NormalClassDemos PRIVATE TEST_TYPES="lib/normalclass.hpp")
target_compile_definitions(MixinClassDemos PRIVATE TEST_TYPES="lib/mixinclass.hpp")

# Add all the ADD_TEST for each test
# foreach (test ${AllDemos})
#   get_filename_component (TName ${test} NAME_WE)
#   add_test (NAME "Alias_${TName}" COMMAND AliasDemos ${TName})
#   set_property(TEST "Alias_${TName}" PROPERTY LABELS Alias)

#   add_test (NAME "EnumClass_${TName}" COMMAND EnumClassDemos ${TName})
#   set_property(TEST "EnumClass_${TName}" PROPERTY LABELS EnumClass)

#   add_test (NAME "NormalClass_${TName}" COMMAND NormalClassDemos ${TName})
#   set_property(TEST "NormalClass_${TName}" PROPERTY LABELS NormalClass)

#   add_test (NAME "MixinClass_${TName}" COMMAND MixinClassDemos ${TName})
#   set_property(TEST "MixinClass_${TName}" PROPERTY LABELS MixinClass)
# endforeach ()