( declare-project
  :name "jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(def o (os/which))

(def cflags
  (case o
    :macos '["-Iraylib/src" "-ObjC"]
    #default
    '["-Iraylib/src"]))

(def lflags
  (case o
    :windows '["user32.lib" "gdi32.lib" "winmm.lib" "shell32.lib"]
    :macos '["-lpthread" "-framework" "Cocoa" "-framework" "CoreVideo" "-framework" "IOKit" "-framework" "OpenGL"]
    :linux '["-lpthread" "-lX11"]
    #default
    '["-lpthread"]))

(declare-native
  :name "jaylib"

  :cflags cflags

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
            "src/shapes.h"
            "src/3d.h"]

  :lflags lflags)

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
