Require Import Coq.extraction.ExtrOcamlBasic.
Require Import Coq.extraction.ExtrOcamlNatInt.
Require Import Coq.extraction.ExtrOcamlString.
Require Import Coq.extraction.ExtrOcamlZInt.
Require Import Strings.String.

Extract Inductive string => "string" [ """""" "(fun a b -> (string_of_char a) ^ b)"] "(fun e c s -> if s = "" then e else c s.[0] (String.sub s 1 (String.length s - 1)))".

Extract Inlined Constant fst => "fst".
Extract Inlined Constant snd => "snd".

Require transfo.

Extraction Library ast.
Extraction Library useless.
Extraction Library wrtonce.
Extraction Library listSet.
Extraction Library transfo.
