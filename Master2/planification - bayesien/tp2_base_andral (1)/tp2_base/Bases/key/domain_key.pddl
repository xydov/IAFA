(define (domain key)

  (:requirements
    :typing
  )

  (:types
    key room treasure
  )

  (:predicates
      (at-key ?k - key ?r - room)
      (at-treasure ?t - treasure ?r - room)
      (at-robby ?r - room)
      (connected ?r1 ?r2 - room )
      (carry-key)
      (hand-free)
  )

  (:action move
    :parameters (?start ?dest - room)
    :precondition (and (at-robby ?start) (connected ?start ?dest))
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
)