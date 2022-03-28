(use ../build/freja-jaylib)

(assert (check-collision-recs [0 0 100 100]
                              [50 50 100 100]))

(assert (not (check-collision-recs [0 0 100 100]
                                   [101 101 100 100])))

(assert (check-collision-circles [0 0] 100
                                 [30 30] 10))

(assert (not (check-collision-circles [0 0] 10
                                      [30 30] 10)))

(assert (check-collision-circle-rec [0 0] 10
                                    [5 5 100 100]))

(assert (not (check-collision-circle-rec [0 0] 10
                                         [15 15 100 100])))

(assert (check-collision-point-rec [25 25]
                                   [12 12 100 100]))

(assert (not (check-collision-point-rec [6 6]
                                        [12 12 100 100])))

(assert (check-collision-point-circle [25 25]
                                      [20 20] 10))

(assert (not (check-collision-point-circle [35 35]
                                           [20 20] 10)))

(assert (check-collision-point-triangle [25 25]
                                        [25 10] [40 30] [10 30]))

(assert (not (check-collision-point-triangle [10 10]
                                             [25 10] [40 30] [10 30])))

(assert (= [50 50] (check-collision-lines [0 0] [100 100]
                                          [100 0] [0 100])))

(assert (not (check-collision-lines [0 0] [100 0]
                                    [0 100] [100 100])))

(assert (check-collision-point-line [25 25]
                                    [0 0] [100 100]
                                    1)) # threshold

(assert (not (check-collision-point-line [25 25]
                                         [0 0] [100 0]
                                         1))) # threshold

(assert (= [50 50 50 50] (get-collision-rec [0 0 100 100]
                                            [50 50 100 100])))

(assert (= [0 0 0 0] (get-collision-rec [0 0 100 100]
                                        [101 101 100 100])))
