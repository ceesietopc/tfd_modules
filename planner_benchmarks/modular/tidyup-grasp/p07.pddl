; first grasp_location reached, object detection done - success
; 2 objects
(define (problem p07)
  (:domain tidyup-grasp)
  ;(:moduleoptions )
  (:objects right_arm - arm bottle bottle2 - movable_object
    lg0 lg1 lg2 - grasp_location)
  (:init 
      (at-base lg2)
      (can-navigate lg1 lg0)
      (can-navigate lg1 lg2)

      (handFree right_arm)

      (detected-objects lg1)
      (detected-objects lg2)

      (graspable-from bottle lg1 right_arm)
      (graspable-from bottle2 lg2 right_arm)

      (= (x l0) 0.0)
      (= (y l0) 0.0)
      (= (z l0) 0.0)
      (= (qx l0) 0.0)
      (= (qy l0) 0.0)
      (= (qz l0) 0.0)
      (= (qw l0) 1.0)

   )

   (:goal (and (clean lg0) (clean lg1) (clean lg2)))
)
