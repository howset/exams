Confirmed pass on exam. (17.4.25 - hs)

```
START main()
|
├── Check arguments
|   └── If not exactly one argument, print usage and exit
|
├── Set input = command line argument
|
├── Call parse_expr(&input) to create syntax tree
|   |
|   ├── parse_expr(&input) --> ADD
|   |   |
|   |   ├── Call parse_term(&input) to get left subtree --> MULTI
|   |   |   |
|   |   |   ├── Call parse_fact(&input) to get left subtree --> PARENTHESIS
|   |   |   |   |
|   |   |   |   ├── If input starts with '('
|   |   |   |   |   ├── Skip '('
|   |   |   |   |   ├── Recursively call parse_expr(&input)
|   |   |   |   |   └── Expect ')' (return NULL if missing)
|   |   |   |   |
|   |   |   |   └── Else call parse_nbr(&input) --> NUMBERS
|   |   |   |       |
|   |   |   |       ├── If input starts with digit
|   |   |   |       |   ├── Create "VAL" node with digit
|   |   |   |       |   └── Advance input pointer
|   |   |   |       |
|   |   |   |       └── Else print unexpected token and return NULL
|   |   |   |
|   |   |   └── While next token is '*'
|   |   |       ├── Skip '*'
|   |   |       ├── Call parse_fact(&input) to get right subtree
|   |   |       └── Create "MULTI" node with left and right subtrees
|   |   |
|   |   └── While next token is '+'
|   |       ├── Skip '+'
|   |       ├── Call parse_term(&input) to get right subtree
|   |       └── Create "ADD" node with left and right subtrees
|   |
|   └── Return the syntax tree
|
├── Check parsing results
|   |
|   ├── If tree is NULL, destroy tree and exit with error
|   |
|   └── If input isn't empty
|       ├── Print unexpected token
|       ├── Destroy tree
|       └── Exit with error
|
├── Evaluate tree with eval_tree(tree)
|   |
|   ├── If node type is ADD
|   |   └── Return eval_tree(left) + eval_tree(right)
|   |
|   ├── If node type is MULT
|   |   └── Return eval_tree(left) * eval_tree(right)
|   |
|   └── If node type is VAL
|       └── Return node value
|
├── Print result
├── Free memory with destroy_tree(tree)
└── Return success
```
