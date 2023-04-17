(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "Mesh Stuff")
(set-target-fps 60)

(def camera (camera-3d :target [0 0 0]
                       :up [0 0 1]
                       :position [5 5 7]
                       :type :perspective
                       :fovy 60))

(def mesh (gen-mesh-cube 2 2 2))
(def material (load-material-default))
(def transform [1 0 0 0
                0 1 0 0
                0 0 1 0
                0 0 0 1])

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])

  (begin-mode-3d camera)
  (draw-mesh mesh material transform)
  (end-mode-3d)

  (end-drawing))

(close-window)
