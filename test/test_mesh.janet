(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "Mesh Stuff")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))

(def meshes [(gen-mesh-poly 5 0.5)
             (gen-mesh-plane 1 1 10 10)
             (gen-mesh-cube 1 1 1)
             (gen-mesh-sphere 0.5 10 10)
             (gen-mesh-hemisphere 0.5 10 10)
             (gen-mesh-cylinder 0.5 1 10)
             (gen-mesh-cone 0.5 1 10)
             (gen-mesh-torus 0.25 1 10 10)
             (gen-mesh-knot 0.25 1 100 100)
             (gen-mesh-heightmap lenna [1 1 1])])

(def material (load-material-default))

# Spinning camera pointed at the center of the line of drawn meshes
(defn camera
  [t]
  (def center (- (length meshes) 0.5))
  (camera-3d :target [center 0 0]
             :up [0 1 0]
             :position [(+ center (* 5 (math/cos t))) 10 (* 5 (math/sin t))]
             :type :perspective
             :fovy 60))

# Transforms to lay out meshes in a line
(defn make-transform
  [x]
  [1 0 0 (* 2 x)
   0 1 0 0
   0 0 1 0
   0 0 0 1])

# Runtime used to animate camera motion. Will eventually overflow.
(var t 0)

(while (not (window-should-close))
  (+= t (/ 1 60))
  (begin-drawing)
  (clear-background [0 0 0])

  (begin-mode-3d (camera t))

  (for i 0 (length meshes)
    (draw-mesh (meshes i) material (make-transform i)))
  
  (draw-triangle-strip-3d [[0 0 2] [1 0 3] [1 0 2] [2 0 3]] :green)

  (end-mode-3d)

  (end-drawing))

(map unload-mesh meshes)

(close-window)
