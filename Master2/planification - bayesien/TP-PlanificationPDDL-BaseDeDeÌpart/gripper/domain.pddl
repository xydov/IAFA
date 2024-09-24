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
     ;; Compléter le corps de l'action
   )

   (:action drop
     ;; Compléter le corps de l'action
   )

)
