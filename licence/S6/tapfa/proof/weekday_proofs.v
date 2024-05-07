Inductive day : Type :=
| sun : day
| mon : day
| tue : day
| wed : day
| thu : day
| fri : day
| sat : day.

Definition prev_day d :=
  match d with
  | sun => sat
  | mon => sun
  | tue => mon
  | wed => tue
  | thu => wed
  | fri => thu
  | sat => fri
  end.

Theorem tue_before_wed : prev_day wed = tue.
Proof.
  simpl. trivial.
Qed.