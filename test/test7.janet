(use ../build/jaylib)
(use spork/test)

# Adjust this to get numbers that are easily comparable
(def repeat-times 50000)

(defmacro time-fun-and-cfun (desc fun cfun & args)
  ~(do
    (print ,desc)
    (print "\tjanet function")
    (timeit
     (repeat ,repeat-times
             (,fun ,;args)))
    (print "\tc function")
    (timeit
     (repeat ,repeat-times
             (,cfun ,;args)))
    (print "------------------------------------------")))

(def identity-matrix
  [1 0 0 0
   0 1 0 0
   0 0 1 0
   0 0 0 1])

(def matrix-of-ones
  [1 1 1 1
   1 1 1 1
   1 1 1 1
   1 1 1 1])

# Vector2 ================================================
(defn v2-zero []
  [0 0])
(assert (= (v2-zero) [0 0]))
(assert (= (vector2-zero) [0 0]))
(time-fun-and-cfun
  "v2 zeros"
  v2-zero vector2-zero)

(defn v2-one []
  [1 1])
(assert (= (v2-one) [1 1]))
(assert (= (vector2-one) [1 1]))
(time-fun-and-cfun
  "v2 ones"
  v2-one vector2-one)

(defn v2+ [[x1 y1] [x2 y2]]
      [(+ x1 x2) (+ y1 y2)])
(assert (= (v2+ [200 200] [100 100]) [300 300]))
(assert (= (vector2-add [200 200] [100 100]) [300 300]))
(assert (= (v2+ [200 200] [100 100])
           (vector2-add [200 200] [100 100])))
(time-fun-and-cfun
  "v2 add"
  v2+ vector2-add
  [1200 1800] [1790 2000])

(defn v2+v [[x y] add]
  [(+ x add) (+ y add)])
(assert (= (v2+v [200 200] 100) [300 300]))
(assert (= (vector2-add-val [200 200] 100) [300 300]))
(assert (= (v2+v [200 200] 100)
           (vector2-add-val [200 200] 100)))
(time-fun-and-cfun
  "v2 add value"
  v2+v vector2-add-val
  [1200 1800] 200)

(defn v2- [[x1 y1] [x2 y2]]
   [(- x1 x2) (- y1 y2)])
(assert (= (v2- [200 200] [100 100]) [100 100]))
(assert (= (vector2-sub [200 200] [100 100]) [100 100]))
(assert (= (v2- [200 200] [100 100])
           (vector2-sub [200 200] [100 100])))
(time-fun-and-cfun
  "v2 subtract"
  v2- vector2-sub
  [1200 1800] [1790 2000])

(defn v2-v [[x y] add]
  [(- x add) (- y add)])
(assert (= (v2-v [200 200] 100) [100 100]))
(assert (= (vector2-sub-val [200 200] 100) [100 100]))
(time-fun-and-cfun
  "v2 subtract value"
  v2-v vector2-sub-val
  [1200 1800] 200)

(defn v2-length [[x y]]
  (math/sqrt (+ (math/pow x 2) (math/pow y 2))))
(assert (= (v2-length [3 4]) 5))
(assert (= (vector2-length [3 4]) 5))
(assert (= (v2-length [3 4])
           (vector2-length [3 4])))
(assert (utils/float-equals (v2-length [90 90])
                            (vector2-length [90 90])))
(time-fun-and-cfun
  "v2 length"
  v2-length vector2-length
  [1200 1800])

(defn v2-length-sqr [[x y]]
  (+ (math/pow x 2) (math/pow y 2)))
(assert (= (v2-length-sqr [3 4]) 25))
(assert (= (vector2-length-sqr [3 4]) 25))
(assert (= (v2-length-sqr [3 4])
           (vector2-length-sqr [3 4])))
(time-fun-and-cfun
  "v2 length square"
  v2-length-sqr vector2-length-sqr
  [1200 1800])

(defn v2-dot [[x1 y1] [x2 y2]]
  (+ (* x1 x2) (* y1 y2)))
(assert (= (v2-dot [3 4] [5 9]) 51))
(assert (= (vector2-dot [3 4] [5 9]) 51))
(assert (= (v2-dot [3 4] [5 9])
           (vector2-dot [3 4] [5 9])))
(time-fun-and-cfun
  "v2 dot product"
  v2-dot vector2-dot
  [1200 1800] [992 882])

(defn v2-distance [[x1 y1] [x2 y2]]
  (math/sqrt (+ (math/pow (- x1 x2) 2)
                (math/pow (- y1 y2) 2))))
(assert (= (v2-distance [3 5] [10 5]) 7))
(assert (= (vector2-distance [3 5] [10 5]) 7))
(assert (utils/float-equals (v2-distance [60 29] [22 21])
                            (vector2-distance [60 29] [22 21])))
(time-fun-and-cfun
  "v2 distance"
  v2-distance vector2-distance
  [1200 1800] [992 882])

(defn v2-distance-sqr [[x1 y1] [x2 y2]]
  (+ (math/pow (- x1 x2) 2)
     (math/pow (- y1 y2) 2)))
(assert (= (v2-distance-sqr [3 5] [10 5]) 49))
(assert (= (vector2-distance-sqr [3 5] [10 5]) 49))
(assert (= (v2-distance-sqr [3 5] [10 5])
           (vector2-distance-sqr [3 5] [10 5])))
(time-fun-and-cfun
  "v2 distance square"
  v2-distance-sqr vector2-distance-sqr
  [1200 1800] [992 882])

(defn v2-angle [[x1 y1] [x2 y2]]
  (let [dot (+ (* x1 x2) (* y1 y2))
        det (- (* x1 y2) (* y1 x2))]
    (math/atan2 det dot)))
(assert (utils/float-equals (v2-angle [1400 900] [1920 1080])
                            (vector2-angle [1400 900] [1920 1080])))
(time-fun-and-cfun
  "v2 angle"
  v2-angle vector2-angle
  [1200 1800] [992 882])

(defn v2-line-angle [[startx starty] [endx endy]]
      (- (math/atan2 (- endy starty) (- endx startx))))
(assert (utils/float-equals
          (v2-line-angle [1400 900] [1920 1080])
          (vector2-line-angle [1400 900] [1920 1080])))
(time-fun-and-cfun
  "v2 line angle"
  v2-line-angle vector2-line-angle
  [1200 1800] [992 882])

(defn v2-scale [[x y] scalar]
  [(* x scalar) (* y scalar)])
(assert (= (v2-scale [200 200] 2) [400 400]))
(assert (= (vector2-scale [200 200] 2) [400 400]))
(assert (= (v2-scale [200 200] 2)
           (vector2-scale [200 200] 2) ))
(time-fun-and-cfun
  "v2 scale"
  v2-scale vector2-scale
  [1200 1800] 4)

(defn v2-multiply [[x1 y1] [x2 y2]]
  [(* x1 x2) (* y1 y2)])
(assert (= (v2-multiply [200 200] [400 400]) [80000 80000]))
(assert (= (vector2-multiply [200 200] [400 400]) [80000 80000]))
(assert (= (v2-multiply [200 200] [400 400])
           (vector2-multiply [200 200] [400 400]) ))
(time-fun-and-cfun
  "v2 multiply"
  v2-multiply vector2-multiply
  [1200 1800] [800 800])

(defn v2-negate [[x y]]
  [(- x) (- y)])
(assert (= (v2-negate [200 200]) [-200 -200]))
(assert (= (vector2-negate [200 200]) [-200 -200]))
(assert (= (v2-negate [200 200])
           (vector2-negate [200 200])))
(time-fun-and-cfun
  "v2 negate"
  v2-negate vector2-negate
  [1200 1800])

(defn v2-divide [[x1 y1] [x2 y2]]
  [(/ x1 x2) (/ y1 y2)])
(assert (= (v2-divide [200 200] [100 100]) [2 2]))
(assert (= (vector2-divide [200 200] [100 100]) [2 2]))
(assert (= (vector2-divide [200 200] [100 100])
           (vector2-divide [200 200] [100 100])))
(time-fun-and-cfun
  "v2 divide"
  v2-divide vector2-divide
  [1200 1800] [200 200])

(defn v2-normalize [[x y]]
  (let [length (math/sqrt (+ (math/pow x 2)
                             (math/pow y 2)))]
    (if (> length 0)
      (let [ilength (/ 1.0 length)]
        [(* x ilength) (* y ilength)])
      [0 0])))
(assert (vector2-equals
          (v2-normalize [5 10])
          (vector2-normalize [5 10])))
(time-fun-and-cfun
  "v2 normalize"
  v2-normalize vector2-normalize
  [1200 1800])

(defn v2-transform [[x y] mat]
  (let [z 0]
    [(+ (* (mat 0) x) (* (mat 4) y) (* (mat 8) z) (mat 12))
     (+ (* (mat 1) x) (* (mat 5) y) (* (mat 9) z) (mat 13))]))

(assert (= (v2-transform [256 512] identity-matrix) [256 512]))
(assert (= (vector2-transform [256 512] identity-matrix) [256 512]))
(assert (= (vector2-transform [256 512] matrix-of-ones) [769 769]))
(assert (= (v2-transform [256 512] matrix-of-ones)
           (vector2-transform [256 512] matrix-of-ones)))
(time-fun-and-cfun
  "v2 transform"
  v2-transform vector2-transform
  [1200 1800] matrix-of-ones)

(defn v2-lerp [[x1 y1] [x2 y2] amount]
  [(+ x1 (* amount (- x2 x1)))
   (+ y1 (* amount (- y2 y1)))])

(assert (= (v2-lerp [512 256] [1024 768] 4)
           (vector2-lerp [512 256] [1024 768] 4)))
(time-fun-and-cfun
  "v2 lerp"
  v2-lerp vector2-lerp
  [1200 1800] [512 333] 4)

(defn v2-reflect [[x y] [normx normy]]
  (let [dot (+ (* x normx)
               (* y normy))]
    [(- x (* 2.0 normx dot))
     (- y (* 2.0 normy dot))]))

(assert (= (v2-reflect [512 256] [24 24])
           (vector2-reflect [512 256] [24 24])))
(time-fun-and-cfun
  "v2 reflect"
  v2-reflect vector2-reflect
  [1200 1800] [512 333])

(defn v2-rotate [[x y] angle]
  (let [cosres (math/cos angle)
        sinres (math/sin angle)]
    [(- (* x cosres)
        (* y sinres))
     (+ (* x sinres)
        (* y cosres))]))
(assert (vector2-equals (v2-rotate [512 256] 8)
                        (vector2-rotate [512 256] 8)))
(time-fun-and-cfun
  "v2 rotate"
  v2-rotate vector2-rotate
  [1200 1800] math/pi)

(defn v2-move-towards [[x y] [tx ty] max-distance]
  (let [dx (- tx x)
        dy (- ty y)
        value (+ (math/pow dx 2)
                 (math/pow dy 2))]
    (if (or (zero? value)
            (and (>= max-distance 0)
                 (<= value (math/pow max-distance 2))))
      [tx ty]
      (let [dist (math/sqrt value)]
        [(+ x (* (/ dx dist) max-distance))
         (+ y (* (/ dy dist) max-distance))]))))

(assert (vector2-equals (v2-move-towards [512 256] [1024 1024] 200)
                        (vector2-move-towards [512 256] [1024 1024] 200)))
(time-fun-and-cfun
  "v2 move towards"
  v2-move-towards vector2-move-towards
  [1200 1800] [2048 2048] math/pi)

(defn v2-invert [[x y]]
  [(/ 1.0 x) (/ 1.0 y)])

(assert (= (v2-invert [512 256])
           (vector2-invert [512 256])))
(time-fun-and-cfun
  "v2 invert"
  v2-invert vector2-invert
  [1200 1800])

(defn v2-clamp [[x y] [minx miny] [maxx maxy]]
  [(min maxx (max minx x))
   (min maxy (max miny y))])

(assert (= (v2-clamp [31 19] [20 20] [30 30])
           (vector2-clamp [31 19] [20 20] [30 30])))
(time-fun-and-cfun
  "v2 clamp between v2s"
  v2-clamp vector2-clamp
  [444 888] [555 555] [777 777])

(defn v2-clamp-val [[x y] fmin fmax]
  (var result (array/slice [x y]))
  (var len (+ (math/pow x 2)
              (math/pow y 2)))
  (when (> len 0)
    (set len (math/sqrt len))
    (when (< len fmin)
      (let [scale (/ fmin len)]
        (set (result 0) (* x scale))
        (set (result 1) (* y scale))))
    (when (> len fmax)
      (let [scale (/ fmax len)]
        (set (result 0) (* x scale))
        (set (result 1) (* y scale)))))
  result)

(assert (vector2-equals (v2-clamp-val [30 20] 21 28)
                        (vector2-clamp-val [30 20] 21 28)))
(time-fun-and-cfun
  "v2 clamp between 2 floating values"
  v2-clamp-val vector2-clamp-val
  [444 888] 555 777)


# Vector3 ================================================
(defn v3-zero []
  [0 0 0])
(assert (= (v3-zero) [0 0 0]))
(assert (= (vector3-zero) [0 0 0]))
(time-fun-and-cfun
  "v3 zeros"
  v3-zero vector3-zero)

(defn v3-one []
  [1 1 1])
(assert (= (v3-one) [1 1 1]))
(assert (= (vector3-one) [1 1 1]))
(time-fun-and-cfun
  "v3 ones"
  v3-one vector3-one)

(defn v3+ [[x1 y1 z1] [x2 y2 z2]]
   [(+ x1 x2) (+ y1 y2) (+ z1 z2)])
(assert (= (v3+ [200 200 200] [100 100 100]) [300 300 300]))
(assert (= (vector3-add [200 200 200] [100 100 100]) [300 300 300]))
(assert (= (v3+ [200 200 200] [100 100 100])
           (vector3-add [200 200 200] [100 100 100])))
(time-fun-and-cfun
  "v3 add"
  v3+ vector3-add
  [1200 1800 2424] [1790 2000 2424])

(defn v3+v [[x y z] add]
  [(+ x add) (+ y add) (+ z add)])
(assert (= (v3+v [200 200 200] 100) [300 300 300]))
(assert (= (vector3-add-val [200 200 200] 100) [300 300 300]))
(assert (= (v3+v [200 200 200] 100)
           (vector3-add-val [200 200 200] 100)))
(time-fun-and-cfun
  "v3 add value"
  v3+v vector3-add-val
  [1200 1800 2424] 200)

(defn v3- [[x1 y1 z1] [x2 y2 z2]]
   [(- x1 x2) (- y1 y2) (- z1 z2)])
(assert (= (v3- [200 200 200] [100 100 100]) [100 100 100]))
(assert (= (vector3-sub [200 200 200] [100 100 100]) [100 100 100]))
(assert (= (v3- [200 200 200] [100 100 100])
           (vector3-sub [200 200 200] [100 100 100])))
(time-fun-and-cfun
  "v3 subtract"
  v3- vector3-sub
  [1200 1800 2424] [1790 2000 2424])

(defn v3-v [[x y z] add]
  [(- x add) (- y add) (- z add)])
(assert (= (v3-v [200 200 200] 100) [100 100 100]))
(assert (= (vector3-sub-val [200 200 200] 100) [100 100 100]))
(time-fun-and-cfun
  "v3 subtract value"
  v3-v vector2-sub-val
  [1200 1800 2424] 200)

(defn v3-scale [[x y z] scalar]
  [(* x scalar) (* y scalar) (* z scalar)])
(assert (= (v3-scale [200 200 200] 2)
           (vector3-scale [200 200 200] 2) ))
(time-fun-and-cfun
  "v3 scale"
  v3-scale vector3-scale
  [1200 1800 2324] 4)

(defn v3-multiply [[x1 y1 z1] [x2 y2 z2]]
  [(* x1 x2) (* y1 y2) (* z1 z2)])
(assert (= (v3-multiply [200 200 200] [400 400 400]) [80000 80000 80000]))
(assert (= (vector3-multiply [200 200 200] [400 400 400]) [80000 80000 80000]))
(assert (= (v3-multiply [200 200 200] [400 400 400])
           (vector3-multiply [200 200 200] [400 400 400])))
(time-fun-and-cfun
  "v3 multiply"
  v3-multiply vector3-multiply
  [1200 1800 2424] [800 800 6969])

(defn v3-cross [[x1 y1 z1] [x2 y2 z2]]
  [(- (* y1 z2) (* z1 y2))
   (- (* z1 x2) (* x1 z2))
   (- (* x1 y2) (* y1 x2))])
(assert (= (v3-cross [1234 1234 1234] [4321 4321 4321])
           (vector3-cross [1234 1234 1234] [4321 4321 4321])))
(time-fun-and-cfun
 "v3 cross product"
 v3-cross vector3-cross
 [1200 1800 2424] [4200 4200 4200])

(defn v3-perpendicular [[x y z]]
  (var min (math/abs x))
  (var cardinal-axis [1.0 0.0 0.0])
  (when (< (math/abs y) min)
    (set min (math/abs y))
    (set cardinal-axis [0.0 1.0 0.0]))
  (when (< (math/abs z) min)
    (set cardinal-axis [0.0 0.0 1.0]))
  [(- (* y (cardinal-axis 2))
      (* z (cardinal-axis 1)))
   (- (* z (cardinal-axis 0))
      (* x (cardinal-axis 2)))
   (- (* x (cardinal-axis 1))
      (* y (cardinal-axis 0)))])

(assert (= (v3-perpendicular [1234 8080 4040])
           (vector3-perpendicular [1234 8080 4040])))
(assert (= (v3-perpendicular [69999 20 1234])
           (vector3-perpendicular [69999 20 1234])))
(time-fun-and-cfun
 "v3 perpendicular"
 v3-perpendicular vector3-perpendicular
 [12000 18002 24244])

(defn v3-length [[x y z]]
  (math/sqrt (+ (math/pow x 2)
                (math/pow y 2)
                (math/pow z 2))))
(assert (utils/float-equals (v3-length [90 90 90])
                            (vector3-length [90 90 90])))
(time-fun-and-cfun
 "v3 length"
 v3-length vector2-length
 [1200 1800 2424])

(defn v3-length-sqr [[x y z]]
  (+ (math/pow x 2)
     (math/pow y 2)
     (math/pow z 2)))
(assert (utils/float-equals (v3-length-sqr [3 4 5])
                            (vector3-length-sqr [3 4 5])))
(time-fun-and-cfun
  "v3 length square"
  v3-length-sqr vector3-length-sqr
  [1200 1800 2424])

(defn v3-dot [[x1 y1 z1] [x2 y2 z2]]
  (+ (* x1 x2)
     (* y1 y2)
     (* z1 z2)))
(assert (= (v2-dot [3 4 5] [5 9 8])
           (vector2-dot [3 4 5] [5 9 8])))
(time-fun-and-cfun
  "v3 dot product"
  v3-dot vector2-dot
  [1200 1800 2424] [992 882 2424])

(defn v3-distance [[x1 y1 z1] [x2 y2 z2]]
  (math/sqrt
    (+ (math/pow (- x1 x2) 2)
       (math/pow (- y1 y2) 2)
       (math/pow (- z1 z2) 2))))
(assert (utils/float-equals (v2-distance [60 29 32] [22 21 19])
                            (vector2-distance [60 29 32] [22 21 19])))
(time-fun-and-cfun
  "v3 distance"
  v3-distance vector3-distance
  [1200 1800 2424] [992 882 1010])

(defn v3-distance-sqr [[x1 y1 z1] [x2 y2 z2]]
  (+ (math/pow (- x1 x2) 2)
     (math/pow (- y1 y2) 2)
     (math/pow (- z1 z2) 2)))
(assert (= (v3-distance-sqr [3 5 2] [10 5 3])
           (vector3-distance-sqr [3 5 2] [10 5 3])))
(time-fun-and-cfun
  "v3 distance square"
  v3-distance-sqr vector3-distance-sqr
  [1200 1800 1212] [992 882 2020])

(defn v3-angle [[x1 y1 z1] [x2 y2 z2]]
  (let [cross [(- (* y1 z2)
                  (* z1 y2))
               (- (* z1 x2)
                  (* x1 z2))
               (- (* x1 y2)
                  (* y1 x2))]
        len (math/sqrt (+ (math/pow (cross 0) 2)
                          (math/pow (cross 1) 2)
                          (math/pow (cross 2) 2)))
        dot (+ (* x1 x2)
               (* y1 y2)
               (* z1 z2))]
    (math/atan2 len dot)))
(assert (utils/float-equals (v3-angle [1400 900 2424] [1920 1080 1212])
                            (vector3-angle [1400 900 2424] [1920 1080 1212])))
(time-fun-and-cfun
  "v3 angle"
  v3-angle vector3-angle
  [1200 1800 2424] [992 882 1212])

(defn v3-negate [[x y z]]
  [(- x) (- y) (- z)])
(assert (= (v3-negate [200 200 1212])
           (vector3-negate [200 200 1212])))
(time-fun-and-cfun
  "v3 negate"
  v3-negate vector3-negate
  [1200 1800 2424])

(defn v3-divide [[x1 y1 z1] [x2 y2 z2]]
  [(/ x1 x2) (/ y1 y2) (/ z1 z2)])
(assert (= (vector2-divide [200 200 200] [100 100 100])
           (vector2-divide [200 200 200] [100 100 100])))
(time-fun-and-cfun
  "v3 divide"
  v3-divide vector3-divide
  [1200 1800 1234] [200 200 200])

(defn v3-normalize [[x y z]]
  (let [length (math/sqrt (+ (math/pow x 2)
                             (math/pow y 2)
                             (math/pow z 2)))]
    (if (not= length 0)
      (let [ilength (/ 1.0 length)]
        [(* x ilength) (* y ilength) (* z ilength)])
      [0 0 0])))
(assert (vector3-equals
          (v3-normalize [5 10 2424])
          (vector3-normalize [5 10 2424])))
(time-fun-and-cfun
  "v3 normalize"
  v3-normalize vector3-normalize
  [1200 1800 6969])

  (defn v3-project [[x1 y1 z1] [x2 y2 z2]]
  (let [v1dv2 (+ (* x1 x2)
                 (* y1 y2)
                 (* z1 z2))
        v2dv2 (+ (math/pow x2 2)
                 (math/pow y2 2)
                 (math/pow z2 2))
        mag (/ v1dv2 v2dv2)]
    [(* x2 mag) (* y2 mag) (* z2 mag)]))
(assert (vector3-equals (v3-project [1212 2424 3535] [4040 5050 6060])
                        (vector3-project [1212 2424 3535] [4040 5050 6060])))

(time-fun-and-cfun
  "v3 project"
  v3-project vector3-project
  [1200 1800 6969] [2020 4040 6060])

(defn v3-reject [[x1 y1 z1] [x2 y2 z2]]
  (let [v1dv2 (+ (* x1 x2)
                 (* y1 y2)
                 (* z1 z2))
        v2dv2 (+ (math/pow x2 2)
                 (math/pow y2 2)
                 (math/pow z2 2))
        mag (/ v1dv2 v2dv2)]
    [(- x1 (* x2 mag))
     (- y1 (* y2 mag))
     (- z1 (* z2 mag))]))

(assert (vector3-equals (v3-project [1212 2424 3535] [4040 5050 6060])
                        (vector3-project [1212 2424 3535] [4040 5050 6060])))
(time-fun-and-cfun
  "v3 reject"
  v3-reject vector3-reject
  [1200 1800 6969] [2020 4040 6060])

(defn v3-transform [[x y z] mat]
  [(+ (* (mat 0) x) (* (mat 4) y) (* (mat 8) z) (mat 12))
   (+ (* (mat 1) x) (* (mat 5) y) (* (mat 9) z) (mat 13))
   (+ (* (mat 2) x) (* (mat 6) y) (* (mat 10) z) (mat 14))])

(assert (= (v2-transform [256 512 1919] matrix-of-ones)
           (vector2-transform [256 512 1919] matrix-of-ones)))
(time-fun-and-cfun
  "v3 transform"
  v3-transform vector3-transform
  [1200 1800 6060] matrix-of-ones)

(defn v3-rotate-quat [[vx vy vz] [qx qy qz qw]]
  (let [x (+ (* vx (+ (* qx qx) (* qw qw) (- (* qy qy)) (- (* qz qz))))
             (* vy (- (* 2 qx qy) (* 2 qw qz)))
             (* vz (+ (* 2 qx qz) (* 2 qw qy))))
        y (+ (* vx (+ (* 2 qw qz) (* 2 qx qy)))
             (* vy (+ (* qw qw) (- (* qx qx)) (* qy qy) (- (* qz qz))))
             (* vz (+ (- (* 2 qw qx)) (* 2 qy qz))))
        z (+ (* vx (+ (- (* 2 qw qy)) (* 2 qx qz)))
             (* vy (+ (* 2 qw qx) (* 2 qy qz)))
             (* vz (+ (* qw qw) (- (* qx qx)) (- (* qy qy)) (* qz qz))))]
    [x y z]))
(assert (vector3-equals (v3-rotate-quat [512 256 6969] [1024 768 2020 12])
                        (vector3-rotate-quat [512 256 6969] [1024 768 2020 12])))
(time-fun-and-cfun
  "v3 rotate by quaternion"
  v3-rotate-quat vector3-rotate-quat
  [1200 1800 6060] [40 20 30 10])

(defn v3-rotate-axis [[vx vy vz] [ax ay az] angle]
  (let [len (math/sqrt (+ (* ax ax) (* ay ay) (* az az)))
        len (if (zero? len) 1.0 len)
        ilen (/ 1.0 len)
        ax (* ax ilen)
        ay (* ay ilen)
        az (* az ilen)
        half-angle (/ angle 2.0)
        sin-ha (math/sin half-angle)
        cos-ha (math/cos half-angle)
        b (* ax sin-ha)
        c (* ay sin-ha)
        d (* az sin-ha)
        wv [(- (* c vz) (* d vy))
            (- (* d vx) (* b vz))
            (- (* b vy) (* c vx))]
        wwv [(- (* c (wv 2)) (* d (wv 1)))
             (- (* d (wv 0)) (* b (wv 2)))
             (- (* b (wv 1)) (* c (wv 0)))]
        wv [( * (wv 0) (* 2.0 cos-ha))
            ( * (wv 1) (* 2.0 cos-ha))
            ( * (wv 2) (* 2.0 cos-ha))]
        wwv [( * (wwv 0) 2.0)
             ( * (wwv 1) 2.0)
             ( * (wwv 2) 2.0)]]
    [(+ vx (wv 0) (wwv 0))
     (+ vy (wv 1) (wwv 1))
     (+ vz (wv 2) (wwv 2))]))
(assert (vector3-equals (v3-rotate-axis [512 256 6969] [1024 768 2020] 21)
                        (vector3-rotate-axis [512 256 6969] [1024 768 2020] 21)))
(time-fun-and-cfun
  "v3 rotate by axis angle"
  v3-rotate-axis vector3-rotate-axis
  [1200 1800 6060] [40 20 30] 4)

(defn v3-lerp [[x1 y1 z1] [x2 y2 z2] amount]
  [(+ x1 (* amount (- x2 x1)))
   (+ y1 (* amount (- y2 y1)))
   (+ z1 (* amount (- z2 z1)))])
(assert (= (v3-lerp [512 256 6969] [1024 768 2020] 4)
           (vector3-lerp [512 256 6969] [1024 768 2020] 4)))
(time-fun-and-cfun
  "v3 lerp"
  v3-lerp vector3-lerp
  [1200 1800 1241] [512 333 1256] 4)

(defn v3-reflect [[x y z] [normx normy normz]]
  (let [dot (+ (* x normx)
               (* y normy)
               (* z normz))]
    [(- x (* 2.0 normx dot))
     (- y (* 2.0 normy dot))
     (- z (* 2.0 normz dot))]))

(assert (= (v3-reflect [512 256 2424] [24 24 12])
           (vector3-reflect [512 256 2424] [24 24 12])))
(time-fun-and-cfun
  "v3 reflect"
  v3-reflect vector3-reflect
  [1200 1800 60] [512 333 420])

(defn v3-min [[x1 y1 z1] [x2 y2 z2]]
  [(min x1 x2) (min y1 y2) (min z1 z2)])
(assert (= (v3-min [12 40 29] [11 20 40]))
        (= (vector3-min [12 40 29] [11 20 40])))
(time-fun-and-cfun
  "v3 min"
  v3-min vector3-min
  [1200 1800 60] [512 333 420])

(defn v3-max [[x1 y1 z1] [x2 y2 z2]]
  [(max x1 x2) (max y1 y2) (max z1 z2)])
(assert (= (v3-max [12 40 29] [11 20 40]))
        (= (vector3-max [12 40 29] [11 20 40])))
(time-fun-and-cfun
  "v3 max"
  v3-max vector3-max
  [1200 1800 60] [512 333 420])

(defn v3-barycenter [[px py pz] [ax ay az] [bx by bz] [cx cy cz]]
  (let [[v0x v0y v0z] [(- bx ax) (- by ay) (- bz az)]
        [v1x v1y v1z] [(- cx ax) (- cy ay) (- cz az)]
        [v2x v2y v2z] [(- px ax) (- py ay) (- pz az)]
        d00 (+ (* v0x v0x) (* v0y v0y) (* v0z v0z))
        d01 (+ (* v0x v1x) (* v0y v1y) (* v0z v1z))
        d11 (+ (* v1x v1x) (* v1y v1y) (* v1z v1z))
        d20 (+ (* v2x v0x) (* v2y v0y) (* v2z v0z))
        d21 (+ (* v2x v1x) (* v2y v1y) (* v2z v1z))
        denom (- (* d00 d11) (* d01 d01))
        y (/ (- (* d11 d20) (* d01 d21)) denom)
        z (/ (- (* d00 d21) (* d01 d20)) denom)
        x (- 1.0 (+ z y))]
    [x y z]))
(assert (= (v3-barycenter [40 50 60] [40 50 60] [4 50 20] [40 20 30])
           (vector3-barycenter [40 50 60] [40 50 60] [4 50 20] [40 20 30])))

(defn v3-unproject [[sx sy sz] proj view]
  (let [[m0 m1 m2 m3
         m4 m5 m6 m7
         m8 m9 m10 m11
         m12 m13 m14 m15] proj
        [v0 v1 v2 v3
         v4 v5 v6 v7
         v8 v9 v10 v11
         v12 v13 v14 v15] view
        mat [(+ (* v0 m0) (* v1 m4) (* v2 m8) (* v3 m12))
             (+ (* v0 m1) (* v1 m5) (* v2 m9) (* v3 m13))
             (+ (* v0 m2) (* v1 m6) (* v2 m10) (* v3 m14))
             (+ (* v0 m3) (* v1 m7) (* v2 m11) (* v3 m15))
             (+ (* v4 m0) (* v5 m4) (* v6 m8) (* v7 m12))
             (+ (* v4 m1) (* v5 m5) (* v6 m9) (* v7 m13))
             (+ (* v4 m2) (* v5 m6) (* v6 m10) (* v7 m14))
             (+ (* v4 m3) (* v5 m7) (* v6 m11) (* v7 m15))
             (+ (* v8 m0) (* v9 m4) (* v10 m8) (* v11 m12))
             (+ (* v8 m1) (* v9 m5) (* v10 m9) (* v11 m13))
             (+ (* v8 m2) (* v9 m6) (* v10 m10) (* v11 m14))
             (+ (* v8 m3) (* v9 m7) (* v10 m11) (* v11 m15))
             (+ (* v12 m0) (* v13 m4) (* v14 m8) (* v15 m12))
             (+ (* v12 m1) (* v13 m5) (* v14 m9) (* v15 m13))
             (+ (* v12 m2) (* v13 m6) (* v14 m10) (* v15 m14))
             (+ (* v12 m3) (* v13 m7) (* v14 m11) (* v15 m15))]
        [a00 a01 a02 a03
         a10 a11 a12 a13
         a20 a21 a22 a23
         a30 a31 a32 a33] mat
        b00 (- (* a00 a11) (* a01 a10))
        b01 (- (* a00 a12) (* a02 a10))
        b02 (- (* a00 a13) (* a03 a10))
        b03 (- (* a01 a12) (* a02 a11))
        b04 (- (* a01 a13) (* a03 a11))
        b05 (- (* a02 a13) (* a03 a12))
        b06 (- (* a20 a31) (* a21 a30))
        b07 (- (* a20 a32) (* a22 a30))
        b08 (- (* a20 a33) (* a23 a30))
        b09 (- (* a21 a32) (* a22 a31))
        b10 (- (* a21 a33) (* a23 a31))
        b11 (- (* a22 a33) (* a23 a32))

        inv-det (/ 1.0
                   (+ (- (* b00 b11) (* b01 b10))
                      (* b02 b09) (* b03 b08)
                      (- (* b04 b07)) (* b05 b06)))

        inv [(* inv-det (+ (* a11 b11) (- (* a12 b10)) (* a13 b09)))
             (* inv-det (+ (- (* a01 b11)) (* a02 b10) (- (* a03 b09))))
             (* inv-det (+ (* a31 b05) (- (* a32 b04)) (* a33 b03)))
             (* inv-det (+ (- (* a21 b05)) (* a22 b04) (- (* a23 b03))))

             (* inv-det (+ (- (* a10 b11)) (* a12 b08) (- (* a13 b07))))
             (* inv-det (+ (* a00 b11) (- (* a02 b08)) (* a03 b07)))
             (* inv-det (+ (- (* a30 b05)) (* a32 b02) (- (* a33 b01))))
             (* inv-det (+ (* a20 b05) (- (* a22 b02)) (* a23 b01)))

             (* inv-det (+ (* a10 b10) (- (* a11 b08)) (* a13 b06)))
             (* inv-det (+ (- (* a00 b10)) (* a01 b08) (- (* a03 b06))))
             (* inv-det (+ (* a30 b04) (- (* a31 b02)) (* a33 b00)))
             (* inv-det (+ (- (* a20 b04)) (* a21 b02) (- (* a23 b00))))

             (* inv-det (+ (- (* a10 b09)) (* a11 b07) (- (* a12 b06))))
             (* inv-det (+ (* a00 b09) (- (* a01 b07)) (* a02 b06)))
             (* inv-det (+ (- (* a30 b03)) (* a31 b01) (- (* a32 b00))))
             (* inv-det (+ (* a20 b03) (- (* a21 b01)) (* a22 b00)))]

        [m0 m1 m2 m3
         m4 m5 m6 m7
         m8 m9 m10 m11
         m12 m13 m14 m15] inv

        x (+ (* m0 sx) (* m4 sy) (* m8 sz) m12)
        y (+ (* m1 sx) (* m5 sy) (* m9 sz) m13)
        z (+ (* m2 sx) (* m6 sy) (* m10 sz) m14)
        w (+ (* m3 sx) (* m7 sy) (* m11 sz) m15)]

    [(/ x w) (/ y w) (/ z w)]))
(assert (vector3-equals (v3-unproject [5 6 7] identity-matrix [0 0 1 0 0 0 0 1 1 0 0 0 0 1 0 0])
                        (vector3-unproject [5 6 7] identity-matrix [0 0 1 0 0 0 0 1 1 0 0 0 0 1 0 0])))
(time-fun-and-cfun
  "v3 unproject"
  v3-unproject vector3-unproject
  [50 60 70] identity-matrix [0 0 1 0 0 0 0 1 1 0 0 0 0 1 0 0])

(defn v3-to-array [v]
  (array/slice v))
(assert (deep= (v3-to-array [4 5 6])
               (vector3-to-array [4 5 6])))
(time-fun-and-cfun
  "v3 to array"
  v3-to-array vector3-to-array
  [1200 1800 2020])

(defn v3-invert [[x y z]]
      [(/ 1.0 x) (/ 1.0 y) (/ 1.0 z)])
(assert (vector3-equals (v3-invert [1 2 3])
                        (vector3-invert [1 2 3])))

(time-fun-and-cfun
  "v3 invert"
  v3-invert vector3-invert
  [1200 1800 2020])

(defn v3-clamp [[x y z] [minx miny minz] [maxx maxy maxz]]
  [(min maxx (max minx x))
   (min maxy (max miny y))
   (min maxz (max minz z))])
(assert (= (v3-clamp [31 19 14] [20 20 18] [30 30 20])
           (vector3-clamp [31 19 14] [20 20 18] [30 30 20])))
(time-fun-and-cfun
  "v3 clamp between min and max"
  v3-clamp vector3-clamp
  [444 888 111] [555 555 222] [777 777 333])

(defn v3-clamp-val [[x y z] fmin fmax]
  (var result (array x y z))
  (var len (+ (math/pow x 2)
              (math/pow y 2)
              (math/pow z 2)))
  (when (> len 0)
    (set len (math/sqrt len))
    (when (< len fmin)
      (let [scale (/ fmin len)]
        (set (result 0) (* x scale))
        (set (result 1) (* y scale))
        (set (result 2) (* z scale))))
    (when (> len fmax)
      (let [scale (/ fmax len)]
        (set (result 0) (* x scale))
        (set (result 1) (* y scale))
        (set (result 2) (* z scale)))))
  result)
(assert (vector3-equals (v3-clamp-val [30 20 10] 21 28)
                        (vector3-clamp-val [30 20 10] 21 28)))
(time-fun-and-cfun
  "v3 clamp between 2 floating values"
  v3-clamp-val vector3-clamp-val
  [444 888 999] 555 777)

(defn v3-refract [[vx vy vz] [nx ny nz] r]
  (let [dot (+ (* vx nx) (* vy ny) (* vz nz))
        d (- 1.0 (* r r (- 1.0 (* dot dot))))]
    (if (>= d 0)
      (let [d (math/sqrt d)
            vx (- (* r vx) (* (+ (* r dot) d) nx))
            vy (- (* r vy) (* (+ (* r dot) d) ny))
            vz (- (* r vz) (* (+ (* r dot) d) nz))]
        [vx vy vz])
      [0 0 0])))
(assert (vector3-equals (v3-refract [4 5 6] [0 1 0] 4)
                        (vector3-refract [4 5 6] [0 1 0] 4)))
(time-fun-and-cfun
  "v3 refract"
  v3-refract vector3-refract
  [40 50 60] [0 1 0] 8)

# Matrix =================================================
(defn m-determinant [m]
  (let [a00 (m 0)  a01 (m 1)  a02 (m 2)  a03 (m 3)
        a10 (m 4)  a11 (m 5)  a12 (m 6)  a13 (m 7)
        a20 (m 8)  a21 (m 9)  a22 (m 10) a23 (m 11)
        a30 (m 12) a31 (m 13) a32 (m 14) a33 (m 15)]
    (+ (* a30 a21 a12 a03) (- (* a20 a31 a12 a03))
       (- (* a30 a11 a22 a03)) (+ (* a10 a31 a22 a03))
       (+ (* a20 a11 a32 a03)) (- (* a10 a21 a32 a03))
       (- (* a30 a21 a02 a13)) (+ (* a20 a31 a02 a13))
       (+ (* a30 a01 a22 a13)) (- (* a00 a31 a22 a13))
       (- (* a20 a01 a32 a13)) (+ (* a00 a21 a32 a13))
       (+ (* a30 a11 a02 a23)) (- (* a10 a31 a02 a23))
       (- (* a30 a01 a12 a23)) (+ (* a00 a31 a12 a23))
       (+ (* a10 a01 a32 a23)) (- (* a00 a11 a32 a23))
       (- (* a20 a11 a02 a33)) (+ (* a10 a21 a02 a33))
       (+ (* a20 a01 a12 a33)) (- (* a00 a21 a12 a33))
       (- (* a10 a01 a22 a33)) (+ (* a00 a11 a22 a33)))))
(assert (= (m-determinant identity-matrix)
           (matrix-determinant identity-matrix)))
(time-fun-and-cfun
  "matrix determinant"
  m-determinant matrix-determinant
  identity-matrix)

(defn m-trace [m]
    #float result = (mat.m0 + mat.m5 + mat.m10 + mat.m15);
  (+ (m 0) (m 5) (m 10) (m 15)))
(assert (= (m-trace identity-matrix)
           (matrix-trace identity-matrix)))
(time-fun-and-cfun
  "matrix trace"
  m-trace matrix-trace
  identity-matrix)

(defn m-transpose [m]
  [(m 0) (m 4) (m 8) (m 12)
   (m 1) (m 5) (m 9) (m 13)
   (m 2) (m 6) (m 10) (m 14)
   (m 3) (m 7) (m 11) (m 15)])
(assert (= (m-transpose identity-matrix)
           (matrix-transpose identity-matrix)))
(time-fun-and-cfun
  "matrix transpose"
  m-transpose matrix-transpose
  identity-matrix)

(defn m-invert [m]
  (let [a00 (m 0)  a01 (m 1)  a02 (m 2)  a03 (m 3)
        a10 (m 4)  a11 (m 5)  a12 (m 6)  a13 (m 7)
        a20 (m 8)  a21 (m 9)  a22 (m 10) a23 (m 11)
        a30 (m 12) a31 (m 13) a32 (m 14) a33 (m 15)

        b00 (- (* a00 a11) (* a01 a10))
        b01 (- (* a00 a12) (* a02 a10))
        b02 (- (* a00 a13) (* a03 a10))
        b03 (- (* a01 a12) (* a02 a11))
        b04 (- (* a01 a13) (* a03 a11))
        b05 (- (* a02 a13) (* a03 a12))
        b06 (- (* a20 a31) (* a21 a30))
        b07 (- (* a20 a32) (* a22 a30))
        b08 (- (* a20 a33) (* a23 a30))
        b09 (- (* a21 a32) (* a22 a31))
        b10 (- (* a21 a33) (* a23 a31))
        b11 (- (* a22 a33) (* a23 a32))

        invDet (/ 1.0
                  (+ (- (* b00 b11) (* b01 b10))
                     (+ (* b02 b09) (* b03 b08))
                     (- (* b04 b07)) (* b05 b06)))]

    [(* (+ (- (* a11 b11) (* a12 b10)) (* a13 b09)) invDet)
     (* (+ (- (* (- a01) b11) (* (- a03) b09)) (* a02 b10)) invDet)
     (* (+ (- (* a31 b05) (* a32 b04)) (* a33 b03)) invDet)
     (* (+ (- (* (- a21) b05) (* (- a23) b03)) (* a22 b04)) invDet)

     (* (+ (- (* (- a10) b11) (* a13 b07)) (* a12 b08)) invDet)
     (* (+ (- (* a00 b11) (* a02 b08)) (* a03 b07)) invDet)
     (* (+ (- (* (- a30) b05) (* a33 b01)) (* a32 b02)) invDet)
     (* (+ (- (* a20 b05) (* a22 b02)) (* a23 b01)) invDet)

     (* (+ (- (* a10 b10) (* a11 b08)) (* a13 b06)) invDet)
     (* (+ (- (* (- a00) b10) (* a03 b06)) (* a01 b08)) invDet)
     (* (+ (- (* a30 b04) (* a31 b02)) (* a33 b00)) invDet)
     (* (+ (- (* (- a20) b04) (* a23 b00)) (* a21 b02)) invDet)

     (* (+ (- (* (- a10) b09) (* a12 b06)) (* a11 b07)) invDet)
     (* (+ (- (* a00 b09) (* a01 b07)) (* a02 b06)) invDet)
     (* (+ (- (* (- a30) b03) (* a32 b00)) (* a31 b01)) invDet)
     (* (+ (- (* a20 b03) (* a21 b01)) (* a22 b00)) invDet)]))

(assert (= (m-invert identity-matrix)
           (matrix-invert identity-matrix)))
(time-fun-and-cfun
  "matrix invert"
  m-invert matrix-invert
  identity-matrix)
