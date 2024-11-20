(define (domain key_explorer)

  (:requirements
    :typing
  )

  (:types
    car place
  )

  (:predicates
      (at-curb ?c - car)
      (at-curb-num ?c - car ?p - place)
      (behind-car ?c1 ?c2 - car)
      (car-clear ?c - car)
      (curb-clear ?p - place)
  )

  (:action move-car-car
    :parameters (?c1 ?c2 ?c3 - car)
    :precondition (and (behind-car ?c2 ?c1) (car-clear ?c3))
    :effect (and (behind-car ?c3 ?c1) (not(behind-car ?c2 ?c1)) (not(car-clear ?c3)) (car-clear ?c2))
    )

   (:action move-car-curb
    :parameters (?c1 ?c2 - car ?p - place)
    :precondition (and (curb-clear ?p) (behind-car ?c2 ?c1))
    :effect (and (not(curb-clear ?p)) (at-curb ?c1) (at-curb-num ?c1 ?p) (car-clear ?c2))
   )

   (:action move-curb-curb
    :parameters (?c - car ?p1 ?p2 - place)
    :precondition (and (not(curb-clear ?p1)) (curb-clear ?p2) (at-curb ?c) (at-curb-num ?c ?p1))
    :effect (and (curb-clear ?p1) (not(curb-clear ?p1)) (at-curb-num ?c ?p2))
    )
    
    (:action move-curb-car
    :parameters (?c1 ?c2 - car ?p - place)
    :precondition (and (not(curb-clear ?p)) (at-curb-num ?c1 ?p) (car-clear ?c2) (at-curb ?c2)) 
    :effect (and )
    )
)