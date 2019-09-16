( declare-project
  :name "jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(declare-native
  :name "jaylib"
  :source ["src/main.c"]
  :headers ["src/core.h"
            "src/types.h"
            "src/audio.h"
            "src/shapes.h"]
  :lflags ["-lraylib" "-lpthread"])

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
