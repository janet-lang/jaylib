(use ../build/jaylib)

(set-trace-log-callback nil)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :green)
  (end-drawing))

(close-window)
