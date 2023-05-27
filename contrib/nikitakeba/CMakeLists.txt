add_library(_nikitakeba
    "src/nikitakeba.cpp"
    "include/nikitakeba.h"
)

target_include_directories(_nikitakeba PUBLIC include)
add_library(ch_contrib::nikitakeba ALIAS _nikitakeba)