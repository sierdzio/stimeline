CONFIG += sanitizer sanitize_address
QMAKE_CXXFLAGS+="-fsanitize=address -fno-omit-frame-pointer"
QMAKE_CFLAGS+="-fsanitize=address -fno-omit-frame-pointer"
QMAKE_LFLAGS+="-fsanitize=address"
