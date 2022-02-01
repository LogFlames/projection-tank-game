if [ "$1" == "help" ] || [ "$1" == "?" ]
then
    echo "Build script:"
    echo "Use 'help' or '?' to show this message"
    echo "Use 'debug' or nothing to build and run a debug-build of the project"
    echo "Use 'debug-norun' or 'norun' to build a debug-build of the project"
    echo "Use 'release' to build the project with optimizations"
    echo "Use 'setup' to create the folder structure. (src/ bin/ bin/debug/ bin/release/ res/ include/)"
    echo
    echo "When building all .o files will be deleted and the 'res' folder (excluding the dev folder) will be copied beside the executable" 

elif [ "$1" == "debug" ] || [ "$1" == "" ]
then
    echo "Building and Running Debug"

    # count=`ls -1 *.o 2>/dev/null | wc -l`
    # if [ $count -gt 0 ]
    # then
    #     rm *.o
    # fi

    if [ -d "bin/debug/res/" ]
    then
        rm -r bin/debug/res/
    fi
    rsync -a --exclude 'dev/' res bin/debug/

    g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -Wextra &&
    g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image &&
    rm *.o &&
    ./bin/debug/main

elif [ "$1" == "release" ]
then
    echo "Building Release"

    # count=`ls -1 *.o 2>/dev/null | wc -l`
    # if [ $count -gt 0 ]
    # then
    #     rm *.o
    # fi

    if [ -d "bin/release/res/" ]
    then
        rm -r bin/release/res/
    fi

    rsync -a --exclude 'dev/' res bin/release/

    g++ -c src/*.cpp -std=c++14 -m64 -O3 -Wall -Wextra &&
    g++ *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image &&
    rm *.o

elif [ "$1" == "debug-norun" ] || [ "$1" == "norun" ]
then
    echo "Building Debug"

    # count=`ls -1 *.o 2>/dev/null | wc -l`
    # if [ $count -gt 0 ]
    # then
    #     rm *.o
    # fi

    if [ -d "bin/debug/res/" ]
    then
        rm -r bin/debug/res/
    fi

    rsync -a --exclude 'dev/' res bin/debug/

    g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -Wextra &&
    g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image &&
    rm *.o

elif [ "$1" == "setup" ]
then
    echo "Creating folder structure"

    if [ ! -d "src" ]
    then
        mkdir -v src/
    fi

    if [ ! -d "bin" ]
    then
        mkdir -v bin/
    fi

    if [ ! -d "bin/debug/" ]
    then
        mkdir -v bin/debug
    fi

    if [ ! -d "bin/release/" ]
    then
        mkdir -v bin/release/
    fi

    if [ ! -d "res" ]
    then
        mkdir -v res/
    fi

else
    echo "Unknown option '$1', use 'help' if your lost"
fi
