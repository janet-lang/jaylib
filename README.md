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

This should compile `build\jaylib.so` on nix systems, which you can import in a janet repl. Jaylib does not build
on Windows with jpm because jpm expects MSVC, but Raylib requires gcc or clang
for C99 features that MSVC does not support. A long term goal is to be able to install jaylib on windows
with minimal dependencies on the external build system.

```clojure
(use ./build/jaylib)
```

## Install

You no longer need to put any dependencies on your system to get jaylib, it
should autodetect and build right out of the box.

```
[sudo] jpm install https://github.com/janet-lang/jaylib.git
```

## Documentation

The best documentation for Jaylib is the [documentation for raylib](https://www.raylib.com/cheatsheet/cheatsheet.html).
You can also find extensive examples for Raylib at https://www.raylib.com/examples.html.

The C API of Raylib has been mirrored in Janet as predictably as I can while
making it pleasant to use. See api.txt for functions that have been implemented.
The rules for binding a Raylib function to a Janet
function are as follows:

* Functions in Raylib are in `PascalCase`; the corresponding janet functions are in `kebab-case`.
* Functions usually take the same arity of arguments as the corresponding C functions. If the Raylib C API
  function signature contains a pointer, there might be some differences. For example, functions that take
  an integer counter n and then a pointer to n items will instead take a byte sequence or indexed data structure,
* Simple structures, like Vectors, Rectangles, and colors are represented as arrays or tuples of values.
  This means a Vector2 is simply a tuple `[x y]`. I prefer an representation of vectors rather than named components (0 1 2 vs. x y z), as
  it makes many algorithms simpler, and the representation more efficient.
* Colors can also be represented by named keyword constants.
* Enums in the C API become kebab case keywords in the Janet API. Leading prefixes are also dropped. This means something like
  `CAMERA_MODE_ORTHOGRAPHIC` becomes just `:orthographic`, but will only work in a context where the API expects a camera mode.
* Complex types that represent game resources, like images or sounds, are represented as opaque abstract types. They are not
  garbage collected for you; you must call the resource destructor to get rid of the resource.
* The API does not yet protect misuse of resources beyond what raylib does.
  This means that Jaylib will go ahead and let you use destroyed resources, just
  as raylib would let you do.

### Colors

Colors can be specified a few different ways:
* Keywords, such as `:white`, `:green`, `:black`, or `:raywhite`. These color constants come from raylib.
* RGB or RGBA tuples. Color components should be integers from 0 to 1.
* A single integer representing an RGBA color, where the components
  are the bytes of the 32 bit unsigned integer representation of that number.
  For example, `0x00FF00FF` is green, `0xFFFFFFFF` is white, etc. Remember to always include
  the alpha. `0xFFFFFF` is cyan, not white.

### Vectors (Vector2, Vector3, Vector4)

* Use a tuple `[x y]`, `[x y z]`, or `[x y z w]`.

### Cameras

Instantiate a Camera2D or Camera3D with the `camera-2d` and `camera-3d` functions. Since these types
are expected to constructed manually in the C API, Jaylib provides functions for initializing these structs.
They take a variable number of keyword arguments that correspond to the structure arguments. Missing arguments
will have a fallback to sensible defaults, such as 0.

```
(def cam (camera-3d :target [0 3 0]
                    :up [0 1 0]
                    :fovy 60
                    :type :perspective
                    :position [6 3 6]))
```

### Additional functions

In addition to the functions mapping directly to Raylib functions, the following
have been implemented in Jaylib:

#### Images

#### get-image-dimensions
`Image -> Vector2`

Extract width and height from an `Image`.

###
