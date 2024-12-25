import itertools as it

fluents = set()
operators = set()

places = ['1', '2','3']
cars = ['A','B','C','D']

# Creation des fluents
#at_curb
for c in cars:
    fluents.add(f'at_curb_{c}')

#at_curb_num
for c,p in it.product(cars,places):
    fluents.add(f'at_curb_num_{c}_{p}')

#behind_car_
for c,d in it.product(cars,cars):
    if c == d:
        continue
    fluents.add(f'behind_car_{c}_{d}')

#car_clear
for c in cars:
    fluents.add(f'car_clear_{c}')

#curb_clear
for p in places:
    fluents.add(f'curb_clear_{p}')

#curb_clear
for p in places:
    fluents.add(f'curb_clear_{p}')

print(f"$F = [{', '.join(fluents)}]")
print()


# Creation des operateurs

# move_car_to_car
for r, s in it.product(places, places):
    op_name = f"A_move_{r}_{s}"
    operators.add(op_name)
    print(f"$Cond({op_name}) = [F_at_robby_{r}]")
    print(f"$Add({op_name}) = [F_at_robby_{s}]")
    print(f"$Del({op_name}) = [F_at_robby_{r}]")
    print()
    
print(f"$O = [{', '.join(operators)}]")
