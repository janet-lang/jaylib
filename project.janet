( declare-project
  :name "jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(def o (os/which))

(def lflags
  (case o
    :windows '[]
    :macos '["-lpthread"]
    :linux '["-lpthread" "-lX11"]
    #default
    '["-lpthread"]))
  
(declare-native
  :name "jaylib"

  :cflags ["-Iraylib/src"]

  :defines {"PLATFORM_DESKTOP" true}

  :source ["src/main.c"
           
           # raylib sources
           "raylib/src/core.c"
           "raylib/src/models.c"
           "raylib/src/raudio.c"
           "raylib/src/rglfw.c"
           "raylib/src/shapes.c"
           "raylib/src/text.c"
           "raylib/src/textures.c"
           "raylib/src/utils.c"]

  :headers ["src/core.h"
            "src/types.h"
            "src/audio.h"
            "src/gestures.h"
            "src/text.h"
            "src/image.h"
            "src/shapes.h"]

  :lflags lflags)

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
