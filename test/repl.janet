(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "In game repl")
(set-target-fps 60)

(defn make-repl
  "Create a repl that can be used in a game. Returns a fiber which should
  be resumed between (begin-drawing) and (end-drawing) once per frame.
  (Basically an immediate mode GUI). Shows a prompt, but output still 
  goes to stdout. Could be modified to also show a buffer of results, or
  include more features like using the arrow keys to navigate within a line."
  [&keys {:prompt-color pcolor
          :output-color ocolor
          :input-color icolor
          :cursor-color ccolor
          :env env
          :font font
          :fontsize fontsize
          :max-output max-output
          :spacing spacing}]

  # Repl state
  (def history @[])
  (def prebuf @"")
  (def output @"")

  # Params
  (default env (do
                 (-> (make-env)
                     (put :out output)
                     (put :err output))))
  (default pcolor :red)
  (default ocolor :ray-white)
  (default icolor :white)
  (default ccolor :gray)
  (default font (load-font "test/pdos.ttf"))
  (default fontsize 16)
  (default max-output 5000)
  (default spacing -1)

  (defn measure [text]
    (def [mw mh] (measure-text-ex font text fontsize spacing))
    mw)

  (defn key-checker
    "Make a key checker for special keys."
    [key]
    (var debounce 0)
    (fn []
      (if (key-down? key)
        (++ debounce)
        (set debounce 0))
      (or (key-pressed? key) (and (> debounce 32) (even? debounce)))))

  (def enter? (key-checker :enter))
  (def bs? (key-checker :backspace))
  (def right? (key-checker :right))
  (def left? (key-checker :left))
  (def up? (key-checker :up))
  (def down? (key-checker :down))

  (defn get-chunk
    "Line getter for jaylib repl. Also draws the repl."
    [buf p]

    # Per chunk state
    (array/push history "")
    (var historyi (- (length history) 1))
    (def [line] (parser/where p))
    (def prompt (string "janet:" line ":" (parser/state p :delimiters) "> "))
    (var counter 0)
    (buffer/clear prebuf)

    (while true

      # Measure screen
      (def h (get-screen-height))
      (def w (get-screen-width))

      # Draw the current prompt
      (def y (- h fontsize 6))
      (def promptw (+ 6 (measure prompt)))
      (draw-text-ex font prompt [6 y] fontsize spacing pcolor)
      (draw-text-ex font buf [promptw y] fontsize spacing icolor)

      # Draw cursor
      (def cursorw (+ promptw (measure prebuf) -4))
      (if (< (% (++ counter) 64) 32)
        (draw-text-ex font "|" [cursorw y] fontsize spacing ccolor))

      # Limit buffer size
      (when (> (length output) max-output)
        (def dlen (- (length output) max-output))
        (buffer/blit output output 0 dlen)
        (buffer/popn output dlen))

      # Draw output
      (def maxh (- h 40))
      (def [ow oh] (measure-text-ex font output fontsize spacing))
      (def oy (if (> oh maxh) (- (+ 6 maxh) oh) 6))
      (draw-text-ex font output [6 oy] fontsize spacing ocolor)

      # Get last key pressed
      (def kcode (get-key-pressed true))

      (def index (length prebuf))

      # Check for special keys for manipulating input buffer
      (cond
        # Check for backspace - you might want to check for
        # holding down the key.
        (bs?)
        (when (> index 0)
          (buffer/blit buf buf (- index 1) index)
          (buffer/popn buf 1)
          (buffer/popn prebuf 1)
          (set counter 0))

        # Check for enter
        (enter?)
        (do
          (array/pop history)
          (array/push history (string buf))
          (print buf)
          (buffer/push-string buf "\n")
          (yield)
          (break))

        # Move right
        (right?)
        (do
          (when-let [byte (get buf index)]
            (buffer/push-byte prebuf byte))
          (set counter 0))

        # Move left
        (left?)
        (do
          (unless (= 0 index)
            (buffer/popn prebuf 1))
          (set counter 0))

        # History forward
        (down?)
        (do
          (when (< historyi (- (length history) 1)) (++ historyi))
          (buffer/clear buf)
          (buffer/clear prebuf)
          (buffer/push-string buf (history historyi)))

        # History back
        (up?)
        (do
          (when (pos? historyi) (-- historyi))
          (buffer/clear buf)
          (buffer/clear prebuf)
          (buffer/push-string buf (history historyi)))

        # Default, key entered
        (when (not= 0 kcode)
          (set counter 0)
          (buffer/push-byte prebuf kcode)
          (if (= (length buf) index)
            (buffer/push-byte buf kcode)
            (do
              (def l (last buf))
              (buffer/blit buf buf (+ 1 index) index)
              (buffer/push-byte buf l)
              (set (buf index) kcode)))))

      # Input not done, so yield to the game loop to get more input
      (yield))

    # Return buffer for chunk-getting interface
    buf)

  # Create the repl
  (coro (with-dyns [:out output
                    :err output]
          (repl get-chunk nil env))))

(def repl-fiber (make-repl))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :black)
  (resume repl-fiber)
  (end-drawing))

(close-window)
