# jaylib

[Janet](https://janet-lang.org) bindings to [Raylib](https://www.raylib.com). The bindings
are faithful to the original C API, especially where it makes sense, but function names
have been "lispified" (kebab case, question marks instead of the word "Is", etc.). See api.txt
for an overview of which API functions have been ported.

## Example

```clojure
(use jaylib)

(init-window 100 100 "Test Game")
(set-target-fps 60)
(hide-cursor)

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])
  (let [[x y] (get-mouse-position)]
    (draw-circle-gradient x y 31.4 :lime :red)
    (draw-poly [500 200] 5 40 0 :magenta)
    (draw-line-bezier
      [(- x 100) y]
      [(+ x 100) (+ y 50)]
      4 :pink)
    (draw-line-ex
      [x (- y 10)]
      [x (+ y 10)]
      4 :sky-blue)
    (draw-line-strip
      [[x 0] [x 100] [50 y] [10 180]]
      :ray-white))

  (end-drawing))

(close-window)
```

## Building

Clone the repo with submodules, or use `git submodule update --init --recursive`.

```
jpm build
```

This should compile `build\jaylib.so`, which you can import in a janet repl. Tested
so far only on linux with Wayland, you will likely need to figure out a working configuration
for raylib, as well as some system specific changes in project.janet for your system.

```clojure
(use ./build/jaylib)
```

## Install

You no longer need to put any dependencies on your system to get jaylib, it
should autodetect and build right out of the box.

```
[sudo] jpm install https://github.com/janet-lang/jaylib.git
```

