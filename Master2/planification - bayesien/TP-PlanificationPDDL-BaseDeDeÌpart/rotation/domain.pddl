(define (domain rotation)
  (:requirements
    :typing :action-costs
  )

  (:types
    position value
  )

  (:predicates
    (next ?n ?npp - position)
    (occurence ?v - value ?n - position)
  )

  (:functions (total-cost) - number)

  (:action small-rotation
    :parameters (?n ?m - position ?v ?w - value)
    :precondition (and
        (next ?n ?m)
        (occurence ?v ?n)
        (occurence ?w ?m)
      )
    :effect (and
      (not (occurence ?v ?n))
      (not (occurence ?w ?m))
      (occurence ?w ?n)
      (occurence ?v ?m)
      (increase (total-cost) 1)
      ))

)
