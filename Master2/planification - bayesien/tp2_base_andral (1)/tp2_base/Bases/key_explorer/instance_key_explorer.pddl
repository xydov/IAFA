(define (problem key_explorer)
  (:domain key_explorer)
  (:objects
    roomN1 roomN2 roomN3 roomS1 roomS2 roomS3 roomS4 roomStart - room
    keyN1 keyN2  keyS1 keyS2 - key
    treasure1 treasure2 - treasure
    door1 door2 - door
  )
  (:init
  
    (at-key keyN1 roomN2)
    (at-key keyN2 roomN2)
    (at-key keyS1 roomS1)
    (at-key keyS2 roomS3)
    
    
    (at-treasure treasure1 roomN3)
    (at-treasure treasure2 roomS4)
    (at-robby roomStart)
    
    (at-door door1 roomN1)
    (at-door door2 roomS2)
    
    ;init connection rooms N
    (connected roomN1 roomStart)
    (connected roomStart roomN1)
    (connected roomN2 roomN1)
    (connected roomN1 roomN2)
    (connected roomN3 roomN2)
    (connected roomN2 roomN3)
    
    ;init connection rooms S
    (connected roomS1 roomStart)
    (connected roomStart roomS1)
    (connected roomS2 roomS1)
    (connected roomS1 roomS2)
    (connected roomS3 roomS2)
    (connected roomS2 roomS3)
    (connected roomS4 roomS2)
    (connected roomS2 roomS4)
    
    (door-closed door1 roomN1)
    (door-closed door2 roomS2)
    
    (is-free roomStart)
    (not(is-free roomN1))
    (is-free roomN2)
    (is-free roomN3)
    
    (is-free roomS1)
    (not(is-free roomS2))
    (is-free roomS3)
    (is-free roomS4)
    
    (hand-free)
  )
  (:goal (and
    (not(at-treasure treasure1 roomN3))
    (not(at-treasure treasure2 roomS4))
    )
  )
)
