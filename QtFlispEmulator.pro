TEMPLATE = subdirs
CONFIG+=ordered

SUBDIRS += \
    GUI \
    logic \
    tests

app.depends=logic
tests.depends=logic
