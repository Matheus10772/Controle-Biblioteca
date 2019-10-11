#ifndef functions_h
#define functions_h

typedef struct {
	char nome[30];
	char editora[12];
	char ano[8];
} Livro;

typedef struct {
	char nome[30];
	char curso[20];
} Aluno;

typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

typedef struct {
	Livro livros[10];
	int qtdLivros;
	Aluno aluno;
	Data dataEmprestimo;
	Data dataDevolucao;
} Emprestimo;

typedef struct {
	Livro livros[100];
	int qtdLivros;
	Aluno alunos[100];
	int qtdAlunos;
	Emprestimo emprestimos[100];
	int qtdEmprestimos;
} Registro;

void SalvaRegistro(Registro b);

void CarregaRegistro(Registro* b);

void ImprimeLinha(char c, int n);

void ImprimeLivro(Livro livro);

void ImprimeAluno(Aluno aluno);

void ImprimeData(Data data);

void ImprimeEmprestimo(Emprestimo emprestimo);

void ImprimeAll(Registro b);

Data CalcularDevolucao(Data data, Aluno aluno);

void NovoLivro(Registro* b);

void NovoAluno(Registro* b);

void NovoEmprestimo(Registro* b);

Registro NovoRegistro();

int MostraMenu();

void Menu(Registro* b);

#endif