//AEP 2024 - Fernando Queiroz 24038237-2
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.c>
#include <ctype.h>
//variaveis globais
FILE *arquivo;
int op, erro=0, x=0;
char nome[50][20],senha[50][15],repitasenha[50][15];
//-----------------------------------------------------------------------------------------------------------
int verificasenha(char* s){
	int i, minuscula, maiuscula, numero, especial = 0;

	if (strlen(s) < 8 || strlen(s) > 12){ // c nao tiver dentro desse limite nem entra
		erro++;
		return 0;
	}
	for (int i = 0; i < strlen(s); i++){ // c passar pelo tamanho, vai ver c tem uma letra minuscula, maiuscula, numero e caracter especial
		if (islower(s[i])) minuscula = 1;
		if (isupper(s[i])) maiuscula = 1;
		if (isdigit(s[i])) numero = 1;
		if (ispunct(s[i])) especial = 1;
	}
	
	if(minuscula == 1 && maiuscula == 1 && numero == 1 && especial == 1) return 1; // só vai passar c tiver todos 1
	else {
		erro++;
		return 0;
	}
}
//-----------------------------------------------------------------------------------------------------------
void criptografia(char* n, char* s){ // vai criptografar o nome e a senha e armazenar
	char cripnome[20],cripsenha[15];
	for(int i = 0; i < strlen(n); i++){ // segundo a tabela ascii ira aumentar 64 em cada caracter no nome
		cripnome[i] = n[i] + 64;
	}
	for(int i = 0; i < strlen(s); i++){ // segundo a tabela ascii ira aumentar 64 em cada caracter na senha
		cripsenha[i] = s[i] + 64;
	}
	fprintf(arquivo,"%s %s\n",cripnome, cripsenha); // aqui é onde armazena os usuarios, nome atras e senha na frente, quebrando linha entre os usuarios ficando um em baixo do outro
}
//-----------------------------------------------------------------------------------------------------------
void criar(){ // criar novos usuarios
	system("cls");
	arquivo = fopen("Usuarios.txt","a"); // aqui abre o arquivo com a opçao "a" q é para adicionar coisas ao bloco
	textcolor(BLUE);
	printf("\n				     ____   ______ ______ ____ _____ ______ ____   ____ \n");
	printf("				    / __ | / ____// ____//  _// ___//_  __// __ | / __ |\n");
	printf("				   / /_/ // __/  / / __  / /  |__ |  / /  / /_/ // / / /\n");
	printf("				  / _  _// /___ / /_/ /_/ /  ___/ / / /  / _  _// /_/ / \n");
	printf("				 /_/ |_|/_____/ |____//___/ /____/ /_/  /_/ |_| |____/  \n");
	printf("\n\n\n\n\n\n\n\n\n");
	textcolor(WHITE);
	gotoxy(34,15);
	printf("Nome: ");
	gotoxy(33,16);
	printf("Senha: ");
	gotoxy(26,17);
	printf("Repita Senha: ");
	do{
		gotoxy(40,15);
    	printf("                                                              "); //limpa o campo
    	gotoxy(40,15);
		gets(nome[x]);
	} while (strlen(nome[x]) == 0 || strlen(nome[x]) >= 20);
	do{ // fica repitindo a senha no mesmo lugar
       gotoxy(40,16);
       printf("                "); //limpa o campo
       gotoxy(40,16);
       gets(senha[x]);
       if(verificasenha(senha[x]) == 0){ // c nao tiver os quisitos ele vai aparecer a mensagem
			gotoxy(26,17);
			printf("                                                                ");
			gotoxy(24,17);
			textcolor(RED);
    		printf("Deve conter um caracter especial, um numero, uma letra maiuscula e uma minuscula.");
    		gotoxy(26,18); // aqui ele vai abaixar o repita senha
    		textcolor(WHITE);
    		printf("Repita senha: ");
	   }
    } while (verificasenha(senha[x]) == 0);
    
	if(erro == 0){ // c nao teve nenhum erro ele vai direto
		do{
    		gotoxy(40,17);
    		printf("                                                                ");
    		gotoxy(40,17);
    		gets(repitasenha[x]);
    	} while (strcmp(repitasenha[x],senha[x]) != 0);
    } else { // c teve, vai abaixar a linha para pegar o repita senha
    	do{
    		gotoxy(40,18);
    		printf("                                                                ");
    		gotoxy(40,18);
    		gets(repitasenha[x]);
    	} while (strcmp(repitasenha[x],senha[x]) != 0);
	}
	criptografia(nome[x],senha[x]);
	x++;
	system("cls");
	textcolor(GREEN);
	gotoxy(10,11);
	printf("   ______ ___     ____   ___    _____ ______ ____   ____       ______ ______ ____ ______ ____     __\n");
	gotoxy(10,12);
	printf("  / ____//   |   / __ | /   |  / ___//_  __// __ | / __ |     / ____// ____//  _//_  __// __ |   / /\n");
	gotoxy(10,13);
	printf(" / /    / /| |  / / / // /| |  |__ |  / /  / /_/ // / / /    / /_   / __/   / /   / /  / / / /  / / \n");
	gotoxy(10,14);
	printf("/ /___ / ___ | / /_/ // ___ | ___/ / / /  / _  _// /_/ /    / __/  / /___ _/ /   / /  / /_/ /  /_/  \n");
	gotoxy(10,15);
	printf("|____//_/  |_|/_____//_/  |_|/____/ /_/  /_/ |_| |____/    /_/    /_____//___/  /_/   |____/  (_)   \n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	sleep(1);
}
//-----------------------------------------------------------------------------------------------------------
void remover(){
}
//-----------------------------------------------------------------------------------------------------------
void listar(){
}
//-----------------------------------------------------------------------------------------------------------
void menu (){
	system("cls");
	textcolor(GREEN);
	printf("\n                                                __  ___ ______ _   __ __  __\n");
	printf("                                               /  |/  // ____// | / // / / /\n");
	printf("                                              / /|_/ // __/  /  |/ // / / / \n");
	printf("                                             / /  / // /___ / /|  // /_/ /  \n");
	printf("                                            /_/  /_//_____//_/ |_/ |____/   \n");
	printf("\n\n\n\n\n\n\n\n");
	textcolor(WHITE);
	printf("						1 - Criar um usuário\n");
	printf("						2 - Remover um usuário\n");
	printf("						3 - Listar usuários\n");
	printf("						0 - Sair\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("Opção: ");
	op = getche();
	switch (op){
		case '1':
			criar();
			break;
		case '2':
			remover();
			break;
		case '3':
			listar();
			break;
		default:
			system("cls");
			break;	
	}
}
//-----------------------------------------------------------------------------------------------------------
int main(){
	setlocale(LC_ALL,"portuguese");
	do{
	menu();
	} while(op!= '0');
	return 0;
}
