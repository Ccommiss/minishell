Le parser

But : analyse syntaxique 

- Regrouper les tokens selon la grammaire
- Verifier la correspondance entre la grammaire attendue et la grammaire de l'input (bon enchainement des tokens)
	- Ici qu'on signale si on a un "unexpected token" (ex : echo < donne "parse error", car un file est attendu)