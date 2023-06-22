import os
import sys

BUILD_TYPE = sys.argv[1] if len(sys.argv) >= 2 else 'debug'
TOOLCHAIN  = os.getenv('CMAKE_TOOLCHAIN_FILE')

if not os.path.exists('build'):
    print('build folder not found, creating one right now...')
    os.mkdir('build')

os.system(f'cmake -DCMAKE_BUILD_TYPE={BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE={TOOLCHAIN} -G Ninja -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -B./build/ -S./')