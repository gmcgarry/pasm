%token <y_word> CSRR CSRW
%token <y_word> IMPLICIT
%token <y_word> JALR JR
%token <y_word> JAL JUMP
%token <y_word> BRANCH BRANCHZ BRANCHSW BRANCHZSW
%token <y_word> LOGICOP NEG

%token <y_word> ITYPE RTYPE STYPE UTYPE JTYPE
%token <y_word> REG CSR

%token <y_word> SIZE

%token <y_word> LI LA
%token <y_word> ITYPE_NODST

%type <y_word> optsz
%type <y_expr> imm5 imm12 imm13 imm20 imm21
