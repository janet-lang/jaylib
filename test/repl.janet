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
  []
  (def history @[])
  (defn get-chunk
    "Line getter for jaylib repl. Also draws the repl."
    [buf p]
    (array/push history "")
    (var historyi (- (length history) 1))
    (def [line] (parser/where p))
    (def prompt (string "janet:" line ":" (parser/state p :delimiters) "> "))
    (def fontsize 20)
    (var counter 0)
    (while true
      # Measure screen
      (def h (get-screen-height))
      # Draw the current prompt
      (def y (- h fontsize 5))
      (def promptw (+ 5 (measure-text prompt fontsize)))
      (draw-text prompt 5 y fontsize :red)
      (draw-text buf promptw y fontsize :white)
      (def cursorw (+ promptw (measure-text buf fontsize)))
      (if (< (% (++ counter) 64) 32)
        (draw-text "|" cursorw y fontsize :gray))
      # Draw cursor
      # Get last key pressed
      (def kcode (get-key-pressed true))
      (cond
        # Check for backspace - you might want to check for
        # holding down the key.
        (key-pressed? :backspace) (buffer/popn buf 1)

        # Check for enter
        (key-pressed? :enter) 
        (do
          (array/pop history)
          (array/push history (string buf))
          (buffer/push-string buf "\n")
          (yield)
          (break))

        # History forward
        (key-pressed? :down)
        (do
          (when (< historyi (- (length history) 1)) (++ historyi))
          (buffer/clear buf)
          (buffer/push-string buf (history historyi)))

        # History back
        (key-pressed? :up)
        (do
          (when (pos? historyi) (-- historyi))
          (buffer/clear buf)
          (buffer/push-string buf (history historyi)))

        # Default, key entered
        (when (not= 0 kcode)
          (set counter 0)
          (buffer/push-byte buf kcode)))

      # Input not done, so yield to the game loop to get more input
      (yield))
    buf)
  # Simple repl. For more customization, replace with run-context
  (coro (repl get-chunk)))

(def repl-fiber (make-repl))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :black)
  (draw-fps 5 5)
  (resume repl-fiber)
  (end-drawing))

(close-window)
