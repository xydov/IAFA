(define (domain key_explorer)

  (:requirements
    :typing
  )

  (:types
    key room treasure door
  )

  (:predicates
      (at-key ?k - key ?r - room)
      (at-treasure ?t - treasure ?r - room)
      (at-robby ?r - room)
      (at-door ?d - door ?r - room)
      (connected ?r1 ?r2 - room )
      (door-closed ?d - door ?r - room)
      (is-free ?r - room)
      (carry-key)
      (hand-free)
  )

  (:action move
    :parameters (?start ?dest - room)
    :precondition (and (at-robby ?start) (connected ?start ?dest) (is-free ?start))
    :effect (and (at-robby ?dest)
                 (not (at-robby ?start))))

   (:action pick
    :parameters (?k - key ?r - room)
    :precondition (and (at-robby ?r) (at-key ?k ?r))
    :effect (and (carry-key) (not(hand-free)) (not(at-key ?k ?r)))
   )

   (:action open-treasure
    :parameters (?t - treasure ?r - room)
    :precondition (and (not(hand-free)) (carry-key) (at-treasure ?t ?r) (at-robby ?r))
    :effect (and (hand-free) (not(carry-key)) (not(at-treasure ?t ?r)))
    )
    
    (:action open-door
    :parameters (?d - door ?r - room)
    :precondition (and (hand-free) (at-door ?d ?r) (at-robby ?r) (door-closed ?d ?r) (not(is-free ?r))) 
    :effect (and (not(door-closed ?d ?r)) (is-free ?r))
    )
)