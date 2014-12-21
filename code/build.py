from fabricate import *

sources = ['t1', 't2']


def build():
    compile()
    link()


def compile():
    for source in sources:
        run('clang', '-c', source+'.c')


def link():
    objects = [s+'.o' for s in sources]
    run('clang', '-o', 'program', objects)


def clean():
    autoclean()


main()