TEMPLATE = subdirs

SUBDIRS += src

!android {
    CONFIG(debug, debug|release) {
        SUBDIRS += tests
    }
}
