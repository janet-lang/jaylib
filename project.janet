( declare-project
  :name "jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(declare-native
  :name "jaylib"
  :source ["src/main.c"]
  :headers ["src/core.h"
            "src/types.h"
            "src/audio.h"
            "src/gestures.h"
            "src/shapes.h"]
  # The exact flags needed may depend on the platform and
  # your build of raylib.
  :lflags ["-lraylib" "-lpthread" "-lX11"])

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
