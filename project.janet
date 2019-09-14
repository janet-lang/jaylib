( declare-project
  :name "jaylib"
  :author "Calvin Rose <calsrose@gmail.com>")

(declare-native
  :name "jaylib"
  :source ["src/main.c"]
  :headers ["src/core.h"
            "src/types.h"
            "src/shapes.h"]
  :lflags ["-lraylib" "-lpthread"])
