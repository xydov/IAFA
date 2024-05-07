# Moodle
Have a look to http://moodle.univ-tlse3.fr/mod/page/view.php?id=114970


## Build
After placing source files inside the src/ directory, type

    make

to build the project.

## Cleanup

    make clean

## Launch debugger

    arm-none-eabi-gdb -ix Dashboard.gdbinit test.elf

### interact with debugger

    connect
    reset
    load

