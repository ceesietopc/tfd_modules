;; Move in cartesians
;;

(define (domain move-in-cartesians)
  (:requirements :typing :durative-actions :fluents :equality :modules)
  (:types
        pose - object
  )
  (:modules
    (can_move ?p - pose conditionchecker can_move@libmyModule.so)

    ;(can_move
      ;?j0 - number
      ;?j1 - number
      ;?j2 - number
      ;?j3 - number
      ;?j4 - number
      ;?j5 - number
      ;?j6 - number
      ;?x  - number
      ;?y  - number
      ;?z  - number
      ;?qx - number
      ;?qy - number
      ;?qz - number
      ;?qw - number
      ;conditionchecker can_move_@libmyModule.so)

;    (move
;      ?j0 - number
;      ?j1 - number
;      ?j2 - number
;      ?j3 - number
;      ?j4 - number
;      ?j5 - number
;      ?j6 - number
;      ?x  - number
;      ?y  - number
;      ?z  - number
;      ?qx - number
;      ?qy - number
;      ?qz - number
;      ?qw - number
;      effect move@libmyModule.so
;    )
  )

  (:predicates
    (pending ?p - pose)
    (done ?p - pose)
    (discarded ?p - pose)
    (moving)
  )

  (:functions
    (j0) - number
  )

  (:durative-action go
    :parameters (?p - pose)
    :duration (= ?duration 1)
    :condition (and
      (at start (not (moving)))
      (at start (pending ?p))
      ;(at start (= (j0) ?j0))
      ;(at start (robot-configuration ?j0))
      ;(at start (coordinates ?p ?x))
      ;(at start (robot-configuration ?j0))
      ;(at start ([can_move ?j0]))
    )
    :effect (and
      (at start (moving))
      (at end (not (moving)))
      (at end (not (pending ?p)))
      (at end (done ?p))
      ;(at end ([can_move (j0) (j1) (j2) (j3) (j4) (j5) (j6) (x ?p) (y ?p) (z ?p) (qx ?p) (qy ?p) (qz ?p)]))
    )
  )

  (:durative-action discard
    :parameters (?p - pose)
    :duration (= ?duration 20)
    :condition (and
      (at start (pending ?p))
    )
    :effect (and
      (at end (not (pending ?p)))
      (at end (discarded ?p))
    )
  )

)
