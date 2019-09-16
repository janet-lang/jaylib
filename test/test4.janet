(use ../build/jaylib)

(init-audio-device)

(let [s (load-sound "./test/snd1.wav")]
  (play-sound s)
  (os/sleep 1)
  (set-sound-pitch s 2.0)
  (play-sound s)
  (os/sleep 1)
  (set-sound-pitch s 0.5)
  (play-sound s)
  (os/sleep 1))

(close-audio-device)
