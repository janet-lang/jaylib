(use ../build/jaylib)

(init-window 800 600 "Test window")
(init-audio-device)

(set-target-fps 60)

(def s (load-sound "./test/snd1.wav"))
(def m (load-music-stream "test/bach.ogg"))
(play-music-stream m)
(set-music-volume m 1)

(while (not (window-should-close))
  (begin-drawing)

  (if (key-pressed? :space)
    (play-sound s))

  (clear-background [0 0 0])

  (update-music-stream m)
  (end-drawing))


(close-audio-device)
