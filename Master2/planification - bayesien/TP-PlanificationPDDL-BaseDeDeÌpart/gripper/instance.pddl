(define (problem gripper3)
  (:domain gripper)
  (:objects
    roomL roomR - room
    ballA ballB ballC - ball
  )
  (:init
    (at-ball ballA roomL)
    (at-ball ballB roomL)
    (at-ball ballC roomL)
    (at-robby roomL)
    (hand-free)
  )
  (:goal (and
    (at-ball ballA roomR)
    (at-ball ballB roomR)
    (at-ball ballC roomR)
    )
  )
)
