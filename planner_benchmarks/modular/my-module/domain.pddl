;; Move in cartesians
;;

(define (domain move-in-cartesians)
  (:requirements :typing :durative-actions :fluents :equality :modules)
  (:types
        pose - object
  )
  (:modules

    ; Cost of moving from current robot configuration to pose p
    (can_move ?p - pose cost
              can_move@libmyModule.so)

    ; Modify robot configuration so the end effector ends up with pose p
    (move ?p - pose
          (j0) (j1) (j2) (j3) (j4) (j5) (j6) effect move@libmyModule.so)
  )

  (:predicates
    (pending ?p - pose)
    (done ?p - pose)
    (discarded ?p - pose)
    (moving)
  )

  (:functions
    (j0) (j1) (j2) (j3) (j4) (j5) (j6) - number ; robot configuration
    (x ?p - pose) - number ; x coordinate of a pose p
    (y ?p - pose) - number ; y coordinate of a pose p
    (z ?p - pose) - number ; z coordinate of a pose p
    (qx ?p - pose) - number ; qx component of a pose p
    (qy ?p - pose) - number ; qy component of a pose p
    (qz ?p - pose) - number ; qz component of a pose p
    (qw ?p - pose) - number ; qw component of a pose p
  )

  (:durative-action go
    :parameters (?p - pose)
    :duration (= ?duration [can_move ?p])
    :condition (and
      (at start (not (moving)))
      (at start (pending ?p))
      ;(at start ([can_move ?p]))
    )
    :effect (and
      (at start (moving))
      (at end (not (moving)))
      (at end (not (pending ?p)))
      (at end (done ?p))
      (at end ([move ?p]))
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
