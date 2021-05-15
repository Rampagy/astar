import platform

compiler_options = []

if platform.system() == 'Windows':
    compiler_options = ['/EHsc', '/Ox', '/std:c++17']
    print('Detected Windows...')
    
elif platform.system() == 'Linux':
    compiler_options = ['-std=c++1z', '-O3']
    print('Detected Linux...')

env=Environment(CXXFLAGS=compiler_options)

env.Program('astar_search', Glob('*.cpp'))