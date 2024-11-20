(define (domain gripper)

  (:requirements
    :typing
  )

  (:types
    ball room
  )

  (:predicates
      (at-ball ?b - ball ?r - room)
      (at-robby ?r - room)
      (carry ?b - ball)
      (hand-free )
  )

  (:action move
    :parameters (?start ?dest - room)
    :precondition (and (at-robby ?start))
    :effect (and (at-robby ?dest)
                 (not (at-robby ?start))))

   (:action pick
    :parameters (?b - ball ?r - room)
    :precondition (and (at-robby ?r) (at-ball ?b ?r))
    :effect (and (carry ?b) not(hand-free) not(at-ball ?b ?r))
   )

   (:action drop
    :parameters (?b - ball ?r - (at-robby ?r - room))
    :precondition (and not(hand-free) (carry ?b))
    :effect (and (hand-free) not(carry ?b) (at-ball ?b ?r))
   )

)
