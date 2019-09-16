(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "Chart")
(init-audio-device)
(set-target-fps 60)

(def m (load-music-stream "test/bach.ogg"))
(play-music-stream m)
(set-music-volume m 1)

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])

  (update-music-stream m)
  (loop [x :range [20 (+ 40 (get-screen-width)) 40]
         y :range [20 (+ 40 (get-screen-height)) 40]]
    (draw-circle x y 20 [(math/random)
                         (math/random)
                         (math/random)]))

  (end-drawing))

(close-window)
