(use jaylib)

(init-window 800 600 "Blend Modes")
(set-target-fps 60)

(def tex (load-texture "test/lenna.png"))
(def glow-black-tx (load-texture "test/glow_black_128.png"))
(def glow-trans-tx (load-texture "test/glow_128.png"))

(var glow-tx glow-black-tx)

(gen-texture-mipmaps glow-tx)
(set-texture-filter glow-tx :trilinear)


(def pos @[300 400])
(def blend-modes [
  :alpha
  :additive
  :multiplied
  :add-colors
  :subtract-colors
  :alpha-premultiply
  :custom
  :custom-separate
  ])
(var i 0)

(var mode (in blend-modes i))

(while (not (window-should-close))
  # WASD movement
  (cond
    (key-down? :w) (+= (pos 1) -4)
    (key-down? :s) (+= (pos 1) 4))
  (cond
    (key-down? :a) (+= (pos 0) -4)
    (key-down? :d) (+= (pos 0) 4))

  # Change mode
  (when (key-pressed? :space)
    (set i 
      (% (++ i) (length blend-modes)))
    (set mode (in blend-modes i))
    )
  (when (key-pressed? :e)
    (cond
      (= glow-tx glow-black-tx) (set glow-tx glow-trans-tx)
      (= glow-tx glow-trans-tx) (set glow-tx glow-black-tx)))

  (begin-drawing)

  (clear-background [0 0 0])
  (draw-texture-ex tex [0 90] 0 1 :white)
  (def scl 1.5)
  (begin-blend-mode mode)
    (draw-texture-ex glow-tx [(- (pos 0) 0) (- (pos 1) (* scl 128))] 0 scl :red)
    (draw-texture-ex glow-tx [(- (pos 0) (* scl 64)) (- (pos 1) 0)] 0 scl :green)
    (draw-texture-ex glow-tx [(+ (pos 0) (* scl 64)) (- (pos 1) 0)] 0 scl :blue)
  (end-blend-mode)

  (def txt 
    (string
      "Press Space to change modes\n\n"
      "Press E to switch glow texture\n\n"
      "Press WASD to move the glow texture\n\n\n"
      "mode: " mode "\n\n"
      "texture: " (if (= glow-tx glow-trans-tx) "transparent BG" "opaque BG") "\n\n"
      )
    )
  (draw-text txt 10 10 20 :white)

  (end-drawing)
)

(close-window)
