(define (problem key)
  (:domain key)
  (:objects
    roomN1 roomN2 roomS1 roomS2 roomStart - room
    keyN keyS - key
    treasure1 treasure2 - treasure
  )
  (:init
    (at-key keyN roomN2)
    (at-key keyS roomS1)
    (at-treasure treasure1 roomN1)
    (at-treasure treasure2 roomS2)
    (at-robby roomStart)
    (connected roomN1 roomStart)
    (connected roomN2 roomN1)
    (connected roomS1 roomStart)
    (connected roomS2 roomS1)
    (connected roomStart roomN1)
    (connected roomN1 roomN2)
    (connected roomStart roomS1)
    (connected roomS1 roomS2)
    (hand-free)
  )
  (:goal (and
    (not(at-treasure treasure1 roomN1))
    (not(at-treasure treasure2 roomS2))
    )
  )
)
