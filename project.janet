( declare-project
  :name "jaylib"
  :description "Janet bindings to Raylib"
  :url "https://github.com/janet-lang/jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(def o (os/which))

(def cflags
  (case o
    :macos '["-Iraylib/src" "-ObjC" "-Iraylib/src/external/glfw/include"]
    :windows ["-Iraylib/src" "-Iraylib/src/external/glfw/include" ]
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

  :cflags [;default-cflags ;cflags]

  :defines {"PLATFORM_DESKTOP" true "_POSIX_C_SOURCE" "200809L" "_DARWIN_C_SOURCE" (if (= o :macos) "1" nil)}

  :source ["src/main.c"

           # raylib sources
           "raylib/src/rcore.c"
           "raylib/src/rmodels.c"
           "raylib/src/raudio.c"
           "raylib/src/rglfw.c"
           "raylib/src/rshapes.c"
           "raylib/src/rtext.c"
           "raylib/src/rtextures.c"
           "raylib/src/utils.c"]

  :headers ["src/core.h"
            "src/types.h"
            "src/audio.h"
            "src/gestures.h"
            "src/text.h"
            "src/image.h"
            "src/shapes.h"
            "src/3d.h"]

  :lflags [;default-lflags ;lflags])

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
