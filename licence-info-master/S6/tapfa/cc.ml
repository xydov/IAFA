type 'a expressionReguliere =
  | Symbole of 'a
  | MotVide
  | Plus of 'a expressionReguliere * 'a expressionReguliere
  | Concat of 'a expressionReguliere * 'a expressionReguliere
  | Etoile of 'a expressionReguliere


let it_regexp fSymbole fMotVide fPlus fConcat fEtoile =
  let rec trait t = match t with
    | Symbole(e) -> fSymbole e 
    | MotVide -> fMotVide
    | Plus(e1, e2) -> fPlus e1 e2 (trait e1) (trait e2)
    | Concat(e1, e2) -> fConcat e1 e2 (trait e1) (trait e2)
    | Etoile(e) -> fEtoile e (trait e)
  in trait
    
    
let contientVide expr = 
  let fSymbol _ = false
  and fPlusConcat _ _ te1 te2 = te1 || te2 
  and fEtoile _ te1 = te1
  in
  it_regexp fSymbol true fPlusConcat fPlusConcat fEtoile expr
    
    
let premiersEtContientVide expr = 
  let fSymbol s = ([Symbole(s)], false)
  and fMotVide = ([], true)
  and fPlus _ _ (lfe1, bfe1) (lfe2, bfe2) = (lfe1 @ lfe2, bfe1 || bfe2)
  and fConcat _ _ (lfe1, bfe1) (lfe2, bfe2) = (lfe1, bfe1 && bfe2)
  and fEtoile _ (l, b) = (l, true)
  in
  it_regexp fSymbol fMotVide fPlus fConcat fEtoile expr