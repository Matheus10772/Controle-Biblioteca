#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"functions.h"

void SalvaRegistro(Registro b){
	FILE* arq = fopen("registro.dat", "w");

	fwrite(&b, sizeof(Registro), 1, arq);

	fclose(arq);
}

void CarregaRegistro(Registro *b){
	FILE* arq = fopen("registro.dat", "r");

	if (arq == NULL) {
		fclose(arq);
		return;
	} else {
		printf("\nEXISTE UM REGISTRO SALVO, DESEJA CARREGA-LO? [Y/N]: ");
		char c;
		scanf("%c", &c);
		if (c == 'N') {
			fclose(arq);
			return;
		}
	}

	fread(b, sizeof(Registro), 1, arq);

	fclose(arq);
}

Data SomaData(Data data, int n){
	Data ret;
	ret.dia = data.dia + n;
	ret.mes = data.mes;
	ret.ano = data.ano;
	int mes30[4] = {4, 6, 9, 11};
	int mes31[7] = {1, 3, 5, 7, 8, 10, 12};
	for(int i = 0; i < 4; i++){
		if(mes30[i] == ret.mes && ret.dia > 30){
			ret.dia = ret.dia % 30;
			ret.mes++;
			if (ret.mes > 12) {
				ret.mes = ret.mes % 12;
				ret.ano++;
			}
			return ret;
		}
	}
	for(int i = 0; i < 7; i++){
		if(mes31[i] == ret.mes && ret.dia > 31){
			ret.dia = ret.dia % 31;
			ret.mes++;
			if (ret.mes > 12) {
				ret.mes = ret.mes % 12;
				ret.ano++;
			}
			return ret;
		}
	}
	if (ret.mes == 2) {
		if (ret.ano % 4 == 0 && ret.dia > 29) {
			ret.dia = ret.dia % 29;
			ret.mes++;
			if (ret.mes > 12) {
				ret.mes = ret.mes % 12;
				ret.ano++;
			}
		} else if (ret.dia > 28) {
			ret.dia = ret.dia % 29;
			ret.mes++;
			if (ret.mes > 12) {
				ret.mes = ret.mes % 12;
				ret.ano++;
			}
		}
		return ret;
	}
}

void ImprimeLinha(char c, int n){
	for(int i = 0; i < n; i++)
		printf("%c", c);
}

void ImprimeLivro(Livro livro){
	for(int i = 0; i < 30; i++) {
		if(livro.nome[i] == '\0'){
			ImprimeLinha(' ', 30 - i);
			break;
		} else {
			printf("%c", livro.nome[i]);
		}
	}
	for(int i = 0; i < 12; i++) {
		if(livro.editora[i] == '\0'){
			ImprimeLinha(' ', 12 - i);
			break;
		} else {
			printf("%c", livro.editora[i]);
		}
	}
	for(int i = 0; i < 8; i++) {
		if(livro.ano[i] == '\0'){
			ImprimeLinha(' ', 8 - i);
			break;
		} else {
			printf("%c", livro.ano[i]);
		}
	}
	printf("\n");
}

void ImprimeAluno(Aluno aluno){
	printf("%s", aluno.nome);
	ImprimeLinha(' ', 31 - strlen(aluno.nome));
	printf("%s", aluno.curso);
	printf("\n");
}

void ImprimeData(Data data){
	printf("%d/%d/%d", data.dia, data.mes, data.ano);
}

void ImprimeEmprestimo(Emprestimo emprestimo){

	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");
	ImprimeLinha(' ', 13);
	printf("COMPROVANTE DE EMPRESTIMO");
	ImprimeLinha(' ', 12);
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");

	printf("ALUNO: ");
	ImprimeAluno(emprestimo.aluno);

	printf("DATA: ");
	ImprimeData(emprestimo.dataEmprestimo);
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");
	
	printf("LIVROS:\n");
	for(int i = 0; i < emprestimo.qtdLivros; i++)
		ImprimeLivro(emprestimo.livros[i]);

	ImprimeLinha('*', 50);
	printf("\n");

	printf("TOTAL: %d LIVROS\n", emprestimo.qtdLivros);
	printf("DEVOLUCAO: ");
	ImprimeData(emprestimo.dataDevolucao);
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n\n");

}

void ImprimeAll(Registro b){
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");
	printf("qtdLivros: %d\n", b.qtdLivros);
	printf("qtdAlunos: %d\n", b.qtdAlunos);
	printf("qtdEmperstimos: %d\n", b.qtdEmprestimos);
	ImprimeLinha('*', 50);
	printf("\n");
	for (int i = 0; i < b.qtdLivros; i++)
		ImprimeLivro(b.livros[i]);
	printf("\n");
	for (int i = 0; i < b.qtdAlunos; i++)
		ImprimeAluno(b.alunos[i]);
	printf("\n");
	for (int i = 0; i < b.qtdEmprestimos; i++)
		ImprimeEmprestimo(b.emprestimos[i]);
}

Data CalcularDevolucao(Data data, Aluno aluno){

	int prazo = strcmp(aluno.curso, "GRADUACAO") == 0 ? 7 : 15;

	Data dataDevolucao = SomaData(data, prazo);

	return dataDevolucao;
}

void NovoLivro(Registro* b){
	Livro novoLivro;

	printf("\n");
	ImprimeLinha('*', 19);
	printf(" Novo Livro ");
	ImprimeLinha('*', 19);
	printf("\n");

	printf("Nome    : ");
	scanf("%s", novoLivro.nome);
	printf("Editora : ");
	scanf("%s", novoLivro.editora);
	printf("Ano     : ");
	scanf("%s", novoLivro.ano);

	*(b->livros + b->qtdLivros) = novoLivro;
	b->qtdLivros++;
}

void NovoAluno(Registro* b){
	Aluno novoAluno;

	printf("\n");
	ImprimeLinha('*', 19);
	printf(" Novo Aluno ");
	ImprimeLinha('*', 19);
	printf("\n");

	printf("Nome  : ");
	scanf("%s", novoAluno.nome);

	printf("Curso : ");
	scanf("%s", novoAluno.curso);

	*(b->alunos + b->qtdAlunos) = novoAluno;
	b->qtdAlunos++;
}

void NovoEmprestimo(Registro* b){

	Emprestimo novoEmprestimo;

	printf("\n");
	printf("INFORME O DIA DO EMPRESTIMO: ");
	scanf("%d", &novoEmprestimo.dataEmprestimo.dia);
	printf("INFORME O MES DO EMPRESTIMO: ");
	scanf("%d", &novoEmprestimo.dataEmprestimo.mes);
	printf("INFORME O ANO DO EMPRESTIMO: ");
	scanf("%d", &novoEmprestimo.dataEmprestimo.ano);

	int alunoEncontrado;
	do {
		alunoEncontrado = 0;
		char nomeAluno[30];

		printf("INFORME O ALUNO [0: cancelar]: ");
		scanf("%s", nomeAluno);

		if(strcmp(nomeAluno, "0") == 0) return;

		for(int i = 0; i < b->qtdAlunos; i++){
			if (strcmp(nomeAluno, b->alunos[i].nome) == 0){
				novoEmprestimo.aluno = b->alunos[i];
				alunoEncontrado = 1;
			}
		}

		if (!alunoEncontrado) printf("ALUNO NAO ENCONTRADO!\n");

	} while(!alunoEncontrado);

	novoEmprestimo.dataDevolucao = CalcularDevolucao(novoEmprestimo.dataEmprestimo, novoEmprestimo.aluno);

	novoEmprestimo.qtdLivros = 0;

	int livroEncontrado;
	int finalizar;
	do {
		livroEncontrado = 0;
		finalizar = 0;
		char nomeLivro[30];

		printf("INFORME O LIVRO [0: cancelar / 1: finalizar]: ");
		scanf("%s", nomeLivro);

		if (strcmp(nomeLivro, "0\0") == 0) return;
		if (strcmp(nomeLivro, "1\0") == 0) finalizar = 1;

		for (int i = 0; i < b->qtdLivros; i++)
			if (strcmp(nomeLivro, b->livros[i].nome) == 0){
				*(novoEmprestimo.livros + novoEmprestimo.qtdLivros) = b->livros[i];
				novoEmprestimo.qtdLivros++;
				livroEncontrado = 1;
			}

		if (!livroEncontrado) printf("LIVRO NAO ENCONTRADO!\n");
	} while(!finalizar);

	*(b->emprestimos + b->qtdEmprestimos) = novoEmprestimo;
	b->qtdEmprestimos++;

	printf("\nEMPRESTIMO REALIZADO\n");

}

Registro NovoRegistro(){
	Registro registro;
	registro.qtdAlunos = 0;
	registro.qtdLivros = 0;
	registro.qtdEmprestimos = 0;
	return registro;
}

int MostraMenu(){
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");
	ImprimeLinha(' ', 17);
	printf(" MENU DE OPCOES ");
	ImprimeLinha(' ', 17);
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");
	ImprimeLinha('*', 50);
	printf("\n");

	printf("0 - SALVAR REGISTRO E SAIR\n");
	printf("1 - CADASTRAR NOVO LIVRO\n");
	printf("2 - CADASTRAR NOVO ALUNO\n");
	printf("3 - REALIZAR EMPRESTIMO\n");
	printf("4 - VISUALIZAR TODOS OS LIVROS\n");
	printf("5 - VISUALIZAR TODOS OS ALUNOS\n");
	printf("6 - VISUALIZAR TODOS OS EMPRESTIMOS\n");
	ImprimeLinha('*', 50);
	printf("\nINFORME SUA OPCAO: ");
	int op;
	scanf("%d", &op);
	return op;
}

void Menu(Registro* b){

	CarregaRegistro(b);

	ImprimeLinha(' ', 13);
	printf("!! USE _ PARA ESPACOS !!");
	ImprimeLinha(' ', 13);
	printf("\n");

	while(1) {
		switch (MostraMenu()) {
			case 0:
				SalvaRegistro(*b);
				exit(1);
				break;
			case 1:
				NovoLivro(b);
				break;
			case 2:
				NovoAluno(b);
				break;
			case 3:
				NovoEmprestimo(b);
				break;
			case 4:
				printf("\n");
				for (int i = 0; i < b->qtdLivros; i++)
					ImprimeLivro(b->livros[i]);
				break;
			case 5:
				printf("\n");
				for (int i = 0; i < b->qtdAlunos; i++)
					ImprimeAluno(b->alunos[i]);
				break;
			case 6:
				printf("\n");
				for (int i = 0; i < b->qtdEmprestimos; i++)
					ImprimeEmprestimo(b->emprestimos[i]);
				break;
			case 23:
				ImprimeAll(*b);
				break;
			default:
				printf("\nOPCAO INVALIDA!\n");
				break;
		}
	}
}
