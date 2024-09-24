(define (problem rotation1)

  (:domain rotation)

  (:objects
    p1 p2 p3 p4 p5 - position
    c h i e n - value
  )

  (:init
    (next p1 p2)
    ...
    (occurence c p1)
    ...
    (= (total-cost) 0)
  )

  (:goal
    (and
    (occurence n p1)
    ...
    )
  )
  (:metric minimize (total-cost))
)
