# Minishell

- Simple reproduction of a Bash shell.

[http://www.aosabook.org/en/bash.html](http://www.aosabook.org/en/bash.html)

# Minishell - sujet

---

- **Sujet**
    
    [en.subject.pdf](Minishell%20a0ea27d6695247ee8b9f1120dd730fcb/en.subject.pdf)
    
- Doc : writing your own shell (Pursue) : explains via lex and yacc
    
    [Chapter5-WritingYourOwnShell.pdf](Minishell%20a0ea27d6695247ee8b9f1120dd730fcb/Chapter5-WritingYourOwnShell.pdf)
    
- Video 42sh
    
    [https://www.youtube.com/watch?v=oIFRiwFRSRY](https://www.youtube.com/watch?v=oIFRiwFRSRY)
    

[https://www.gnu.org/software/bash/manual/html_node/Definitions.html](https://www.gnu.org/software/bash/manual/html_node/Definitions.html)

[https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

https://brennan.io/2015/01/16/write-a-shell-in-c/

[https://segfault42.github.io/posts/minishell/](https://segfault42.github.io/posts/minishell/)

### Bash grammar

---

[https://stackoverflow.com/questions/15598878/posix-sh-ebnf-grammar/15599860#15599860](https://stackoverflow.com/questions/15598878/posix-sh-ebnf-grammar/15599860#15599860)

[https://pastebin.com/qpsK4TF6](https://pastebin.com/qpsK4TF6)

[https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10)

[https://codes-sources.commentcamarche.net/forum/affich-10047436-developper-un-shell-de-base](https://codes-sources.commentcamarche.net/forum/affich-10047436-developper-un-shell-de-base) 

## Steps to follow :

---

![Source : [https://ruslanspivak.com/lsbasi-part7/](https://ruslanspivak.com/lsbasi-part7/) ](Minishell%20a0ea27d6695247ee8b9f1120dd730fcb/Untitled.png)

Source : [https://ruslanspivak.com/lsbasi-part7/](https://ruslanspivak.com/lsbasi-part7/) 

![Untitled](Minishell%20a0ea27d6695247ee8b9f1120dd730fcb/Untitled%201.png)

[https://medium.com/swlh/lets-build-a-linux-shell-part-ii-340ecf471028](https://medium.com/swlh/lets-build-a-linux-shell-part-ii-340ecf471028) 

![http://www.aosabook.org/images/bash/bash-article-diagram.png](http://www.aosabook.org/images/bash/bash-article-diagram.png)

Figure 3.1: Bash Component Architecture

- **Lexer** or "**tokenizer**"
    
    C’est l’**analyse lexicale**. Une analyse caractere par caractere, qui doit matcher certaines expressions régulières (ou regex). Forme les **tokens** qui seront donnés au parser : les tokens sont des unités logiques.  Voir la fonction strtok. C’est un tableau de **ptrs**.
    
    - *Exemple* :
        
        ls -a && echo "je fais un \"ls\" -a (youpi)" || (echo "fail" | cat -A) & # un commentaire 
        
        <aside>
        👉 ls
        -a
        &&
        echo
        "je fais un \"ls\" -a (youpi)"
        ||
        (
        echo
        "fail"
        |
        cat
        -A
        )
        &
        
        </aside>
        
    
    [https://shell.multun.net/lexer.html](https://shell.multun.net/lexer.html)
    
- **Parser**
    
    Analyse syntaxique. Va egalement grouper les tokens ensemble, et creer un AST, Abstract Syntax Tree.  [https://medium.com/swlh/lets-build-a-linux-shell-part-iii-a472c0102849](https://medium.com/swlh/lets-build-a-linux-shell-part-iii-a472c0102849) 
    
- Expansion
    
    
    `field` : A unit of text that is the result of one of the shell expansions.  After
    expansion, when executing a command, the resulting fields are used as
    the command name and arguments.
    
- **Execution**

## Les Tokens

---

Il existe trois types de Token : 

- **Word** : A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters. Exemple : une commande, ou un argument de commande.
- **Reserved word :** those that have meaning to the shell and its programming language; usually these words introduce flow control constructs, like if and while. 
⇒ Pas a gerer pour minishell
- **Operator** : A control operator or a redirection operator. See [Redirections](https://www.gnu.org/software/bash/manual/html_node/Redirections.html), for a list of redirection operators. Operators contain at least one unquoted metacharacter.
    
    [What are the shell's control and redirection operators?](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)
    

*Sources* : [http://www.aosabook.org/en/bash.html](http://www.aosabook.org/en/bash.html) 
+ [https://www.gnu.org/software/bash/manual/html_node/Definitions.html](https://www.gnu.org/software/bash/manual/html_node/Definitions.html) 

```
/* -------------------------------------------------------
   The grammar symbols 
   ------------------------------------------------------- */

%token  WORD
%token  ASSIGNMENT_WORD
%token  NAME
%token  NEWLINE
%token  IO_NUMBER

/* The following are the operators mentioned above. */

%token  AND_IF    OR_IF    DSEMI
/*      '&&'      '||'     ';;'    */

AND 
&   &&   (   )   ;   ;;   newline   |   ||

%token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH
/*      '<<'   '>>'    '<&'     '>&'      '<>'       '<<-'   */

%[token](https://pubs.opengroup.org/onlinepubs/9699919799.2016edition/basedefs/V1_chap03.html#tag_03_318) (a definir) 
/*       <     >     >|     <<     >>     <&     >&     <<-     <> 

%token  CLOBBER
/*      '>|'   */

/* The following are the reserved words. */

%token  If    Then    Else    Elif    Fi    Do    Done
/*      'if'  'then'  'else'  'elif'  'fi'  'do'  'done'   */

%token  Case    Esac    While    Until    For
/*      'case'  'esac'  'while'  'until'  'for'   */

/* These are reserved words, not operator tokens, and are
   recognized when reserved words are recognized. */

%token  Lbrace    Rbrace    Bang
/*      '{'       '}'       '!'   */

%token  In
/*      'in'   */

```

[http://www.cs.ecu.edu/karl/5220/spr16/Notes/Lexical/finitestate.html](http://www.cs.ecu.edu/karl/5220/spr16/Notes/Lexical/finitestate.html) 

⇒ finite state machine 

> *Theorem. Any set of strings that can be described by a regular expression can also be described by a finite state machine, and vice versa.*
> 

[https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html](https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html) 

[https://ix-56h.github.io/how-to-make-a-tokenizer/](https://ix-56h.github.io/how-to-make-a-tokenizer/) 

## What is an AST and how to use it ?

---

AST : abstract syntax tree

[https://ruslanspivak.com/lsbasi-part7/](https://ruslanspivak.com/lsbasi-part7/) => Theories

[http://www.gaudry.be/langages-analyse-syntaxique-ast.html](http://www.gaudry.be/langages-analyse-syntaxique-ast.html) ⇒ en francais 

[https://files.gogaz.org/42sh-appsinges.html](https://files.gogaz.org/42sh-appsinges.html)

[https://dev.to/oyagci/generating-a-parse-tree-from-a-shell-grammar-f1](https://dev.to/oyagci/generating-a-parse-tree-from-a-shell-grammar-f1)

## Grammaire, AST et Recursive Descent Parser

---

Le but pour le parser va etre de bien formaliser **une grammaire** a priori, pour ensuite verifier que l'input la respecte bien. 

Voici une representation visuelle de la grammaire :

![([Source](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)) ](Minishell%20a0ea27d6695247ee8b9f1120dd730fcb/Screen_Shot_2021-09-16_at_5.53.58_PM.png)

([Source](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)) 

La grammaire va avoir pour but de nous donner les patterns qu'il faudra valider. En gros, tel token doit être suivi par tel autre, sinon on a une erreur de syntaxe. 

On peut la représenter comme suit : 

```
/* -------------------------------------------------------
   The Grammar a completer
   ------------------------------------------------------- */

pipe_sequence    : simple_command
                 | pipe_sequence '|' simple_command
                 ;
cmd_suffix       : cmd_word
                 | cmd_word cmd_word
                 ;
simple_command   : cmd_name
                 | cmd_name cmd_suffix
                 ;
cmd_name         : WORD
                 ;
cmd_word         : WORD
                 ;
complete_command : list separator
                 | list
list             : list separator_op and_or
                 |                   and_or
separator_op     : '&'
                 | ';'
                 ;
separator        : separator_op linebreak
                 | newline_list
newline_list     :              NEWLINE
                 | newline_list NEWLINE
                 ;
linebreak        : newline_list
                 | /* empty */
pattern          :             WORD         /* Apply rule 4 */
                 | pattern '|' WORD         /* Do not apply rule 4 */

simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
cmd_name         : WORD                   /* Apply rule 7a */
                 ;
cmd_word         : WORD                   /* Apply rule 7b */
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here
                 ;
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT  >>  filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end

here_end         : WORD                      /* Apply rule 3 */
                 ;

```

On le lit de cette maniere :

- Une pipe sequence contient : une commande simple OU une pipe sequence | une commande
- Une simple command : contient un cmd_name OU un cmd_name et un cmd_suffixe

etc, etc. 

But : s'assurer que **le prochain token est bien le token attendu** ; sinon, il s'agira d'une erreur de syntaxe. 

> **La methode "eat"** 
*After matching the passed token type, the eat method gets the next token and assigns it to the current_token variable, thus effectively “eating” the currently matched token and advancing the imaginary pointer in the stream of tokens. If the structure in the stream of tokens doesn’t correspond to the expected sequence of tokens, the eat method throws an exception.

[Source](https://ruslanspivak.com/lsbasi-part1/)*
> 

[https://github.com/lienardale/alientest_minishell/blob/master/redir_nb.sh](https://github.com/lienardale/alientest_minishell/blob/master/redir_nb.sh) 

## Les quotes

---

## Commandes "builtin"

---

Definition : 

## Les redirections

---

[Shell redirections explained](https://dev.to/oyagci/shell-redirections-explained-2h9)

[Taches ](https://www.notion.so/Taches-c9dc13597d424997907b1905f965301e)

## Les retours et le $?

---

<aside>
💡 **Exit :** 

- when a process calls the `exit` system call, the kernel stores the value passed to the system call (an `int`) even after the process dies.

- The exit system call is called by the `exit()` ANSI C function, and indirectly when you do `return` from `main`.

- the process that called the exiting child process (Bash), often with `fork` + `exec`, can retrieve the exit status of the child with the `wait` system call

</aside>

[https://stackoverflow.com/questions/6834487/what-is-the-dollar-question-mark-variable-in-shell-scripting](https://stackoverflow.com/questions/6834487/what-is-the-dollar-question-mark-variable-in-shell-scripting)

Differentes valeurs de retours 

[Exit Codes With Special Meanings](https://tldp.org/LDP/abs/html/exitcodes.html)

Les retours chelous 

[https://unix.stackexchange.com/questions/251996/why-does-bash-set-exit-status-to-non-zero-on-ctrl-c-or-ctrl-z](https://unix.stackexchange.com/questions/251996/why-does-bash-set-exit-status-to-non-zero-on-ctrl-c-or-ctrl-z)
