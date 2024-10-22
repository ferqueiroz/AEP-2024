//AEP 2024 - Fernando Queiroz 24038237-2
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.c>
#include <ctype.h>
// variaveis globais
FILE *arquivo;
int op, erro=0, x=0;
char nome[50][20],senha[50][15],repitasenha[50][15];
//-----------------------------------------------------------------------------------------------------------
// declaração das funções
int verificasenha(char* s);
void criptografia(char* n, char* s);
void removernumero(int n);
void descriptografar();
void criar();
void remover();
void listar();
void menu();
//-----------------------------------------------------------------------------------------------------------
int main(){
	setlocale(LC_ALL,"portuguese");
	do{
	menu();
	} while(op!= '0');
	return 0;
}
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
	arquivo = fopen("Usuarios.txt","a+"); // aqui abre o arquivo com a opçao "a" q é para adicionar coisas ao bloco
	char cripnome[20],cripsenha[15];
	for(int i = 0; i < strlen(n); i++){ // segundo a tabela ascii ira aumentar 64 em cada caracter no nome
		cripnome[i] = n[i] + 52;
	}
	for(int i = 0; i < strlen(s); i++){ // segundo a tabela ascii ira aumentar 64 em cada caracter na senha
		cripsenha[i] = s[i] + 52;
	}
	fprintf(arquivo,"%s\n%s\n",cripnome, cripsenha); // aqui é onde armazena os usuarios, nome atras e senha na frente, quebrando linha entre os usuarios ficando um em baixo do outro
	fclose(arquivo);
}
//-----------------------------------------------------------------------------------------------------------
void criar(){ // criar novos usuarios
	system("cls");
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
	criptografia(nome[x],senha[x]); // vai chama a funçao pra criptografar e armazenar
	x++;
	system("cls");
	textcolor(GREEN);
	gotoxy(10,11);
	printf("    ______ ___     ____   ___    _____ ______ ____   ____       ______ ______ ____ ______ ____     __\n");
	gotoxy(10,12);
	printf("  / ____//   |   / __ | /   |  / ___//_  __// __ | / __ |     / ____// ____//  _//_  __// __ |   / /\n");
	gotoxy(10,13);
	printf(" / /    / /| |  / / / // /| |  |__ |  / /  / /_/ // / / /    / /_   / __/   / /   / /  / / / /  / / \n");
	gotoxy(10,14);
	printf("/ /___ / ___ | / /_/ // ___ | ___/ / / /  / _  _// /_/ /    / __/  / /___ _/ /   / /  / /_/ /  /_/  \n");
	gotoxy(10,15);
	printf("|____//_/  |_|/_____//_/  |_|/____/ /_/  /_/ |_| |____/    /_/    /_____//___/  /_/   |____/  (_)   \n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	sleep(1); // delay de 1 segundo
}
//-----------------------------------------------------------------------------------------------------------
void removernumero(int n) { // vai remover e apresentar que foi removido
	FILE *temp;
    char linha[100];
    int i = 1;
    arquivo = fopen("Usuarios.txt", "r+");
    temp = fopen("temp.txt", "w");
    while (fgets(linha, sizeof(linha), arquivo)) { // aqui ele vai passando linha por linha do arquivo usuarios
        if (i != n && i != n+1) { // caso a linha for diferente da q o usuario quis, ela vai ser armazena no arquivo temporario
            fputs(linha, temp);
            fgets(linha, sizeof(linha), arquivo); // aqui é a senha
            fputs(linha, temp);
        }
        i++;
    }
    fclose(temp);
    fclose(arquivo);
    remove("Usuarios.txt");
    rename("temp.txt","Usuarios.txt"); // vai apaga a Usuarios atual e trocar pela temporaria que esta sem o usuario removido
	system("cls");
	textcolor(GREEN);
	gotoxy(1,12);
	printf("        __  __ _____  __  __ ___     ____   ____ ____       ____   ______ __  ___ ____  _    __ ____ ____   ____ \n");
	printf("       / / / // ___/ / / / //   |   / __ | /  _// __ |     / __ | / ____//  |/  // __ || |  / //  _// __ | / __ |\n");
	printf("      / / / / |__ | / / / // /| |  / /_/ / / / / / / /    / /_/ // __/  / /|_/ // / / /| | / / / / / / / // / / /\n");
	printf("     / /_/ / ___/ // /_/ // ___ | / _  _/_/ / / /_/ /    / _  _// /___ / /  / // /_/ / | |/ /_/ / / /_/ // /_/ / \n");
	printf("     |____/ /____/ |____//_/  |_|/_/ |_|/___/ |____/    /_/ |_|/_____//_/  /_/ |____/  |___//___//_____/ |____/  \n");
	textcolor(WHITE);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	sleep(1);
}
//-----------------------------------------------------------------------------------------------------------
/*void descriptografar(){ // se o admin enviar 0 vai descriptografar o nome e senha do usuario
	char linha[100],linha1[100];
    int i = 1, y = 12, numero, z = 0;
    arquivo = fopen("Usuarios.txt", "r");
    textcolor(RED);
    system("cls");
    printf("\n				      ____   ______ __  ___ ____  _    __ ______ ____ \n");
    printf("				     / __ | / ____//  |/  // __ || |  / // ____// __ |\n");
    printf("				    / /_/ // __/  / /|_/ // / / /| | / // __/  / /_/ /\n");
    printf("				   / _  _// /___ / /  / // /_/ / | |/ // /___ / _  _/ \n");
    printf("				  /_/ |_|/_____//_/  /_/ |____/  |___//_____//_/ |_|  \n");
    if (arquivo == NULL){
    	gotoxy(50,16);
    	printf("O arquivo não existe.\n");
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	textcolor(WHITE);
    	printf("Pressione ENTER para voltar...");
    	getch();
	} else{
		textcolor(WHITE);
	    gotoxy(46,10);
		printf("NOME         |         SENHA\n");
		gotoxy(59,11);
		printf("|");
		gotoxy(59,12);
		printf("|");
		
		while (fgets(linha, sizeof(linha), arquivo)){ // vai percorrer a linha do arquivo
			gotoxy(35,y);
			printf("%d - ", i); // vai contar as linhas
        	gotoxy(40,y);
    		z = 0;
    		while(z != strlen(linha)-1){ //vai pegar caracter por caracter e descriptografar no nome
        		printf("%c", linha[z] - 52);
        		z++;
			}
        	gotoxy(59,y);
			printf("|");
			
			fgets(linha1, sizeof(linha1), arquivo); //vai pegar caracter por caracter e descriptografar na senha
			gotoxy(64,y);
			z = 0;
			while(z != strlen(linha1)-1){
				printf("%c", linha1[z] - 52);
				z++;
			}
        	i++;
        	y++;
    	}
    	fclose(arquivo);
    	printf("\n\n\n\n Número para remover: "); // pede para o usuario digitar um numero para excluir
    	scanf("%d",&numero);
    	if(numero == 0) remover();
    	else removernumero(numero);
    }
}*/
//-----------------------------------------------------------------------------------------------------------
void remover() { // vai listar os usuarios e pedir pro usuario escolher qual ele quer remover
    char linha[100],linha1[100];
    int i = 1, y = 12, numero, z = 0;
    arquivo = fopen("Usuarios.txt", "r");
    textcolor(RED);
    system("cls");
    printf("\n				      ____   ______ __  ___ ____  _    __ ______ ____ \n");
    printf("				     / __ | / ____//  |/  // __ || |  / // ____// __ |\n");
    printf("				    / /_/ // __/  / /|_/ // / / /| | / // __/  / /_/ /\n");
    printf("				   / _  _// /___ / /  / // /_/ / | |/ // /___ / _  _/ \n");
    printf("				  /_/ |_|/_____//_/  /_/ |____/  |___//_____//_/ |_|  \n");
    if (arquivo == NULL){ // c nao tiver arquivo ele fala que nao tem arquivo e pede pra voltar
    	gotoxy(51,16);
    	printf("O arquivo não existe.\n");
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	textcolor(WHITE);
    	printf("Pressione ENTER para voltar...");
    	getch();
	} else{
		textcolor(WHITE);
	    gotoxy(47,10);
		printf("NOME         |         SENHA\n");
		gotoxy(60,11);
		printf("|");
		gotoxy(60,12);
		printf("|");
		
		while (fgets(linha, sizeof(linha), arquivo)){ // vai percorrer a linha do arquivo
			gotoxy(36,y);
			printf("%d - ", i); // vai contar as linhas
        	gotoxy(41,y);
        	z = 0;
    		while(z != strlen(linha)-1){ //vai pegar caracter por caracter e descriptografar no nome
        		printf("%c", linha[z] - 52);
        		z++;
			}
        	gotoxy(60,y);
			printf("|");
			gotoxy(67,y);
			fgets(linha, sizeof(linha), arquivo); // vai escrever a senha sem descriptografar
			printf("%s", linha);
        	i++;
        	y++;
    	}
    	fclose(arquivo);
    	printf("\n\n\n\n Número para remover: "); // pede para o usuario digitar um numero para excluir
    	scanf("%d",&numero);
    	if(numero == 0) return;
    	else removernumero(numero);
    }
}
//-----------------------------------------------------------------------------------------------------------
void listar(){
	char linha[100];
    int i = 1, y = 12, numero, z = 0;
    arquivo = fopen("Usuarios.txt", "r");
	system("cls");
	textcolor(MAGENTA);
	printf("\n                                  __  __ _____  __  __ ___     ____   ____ ____  _____\n");
	printf("                                 / / / // ___/ / / / //   |   / __ | /  _// __ |/ ___/\n");
	printf("                                / / / / |__ | / / / // /| |  / /_/ / / / / / / /|__ | \n");
	printf("                               / /_/ / ___/ // /_/ // ___ | / _  _/_/ / / /_/ /___/ / \n");
	printf("                               |____/ /____/ |____//_/  |_|/_/ |_|/___/ |____//____/  \n");
	if (arquivo == NULL){ // c nao tiver arquivo ele fala que nao tem arquivo e pede pra voltar
    	gotoxy(51,16);
    	printf("O arquivo não existe.\n");
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	textcolor(WHITE);
    	printf("Pressione ENTER para voltar...");
    	getch();
	} else{
		textcolor(WHITE);
	    gotoxy(47,10);
		printf("NOME         |         SENHA\n");
		gotoxy(60,11);
		printf("|");
		gotoxy(60,12);
		printf("|");
		
		while (fgets(linha, sizeof(linha), arquivo)){ // vai percorrer a linha do arquivo
			gotoxy(36,y);
			printf("%d - ", i); // vai contar as linhas
        	gotoxy(41,y);
        	z = 0;
    		while(z != strlen(linha)-1){ //vai pegar caracter por caracter e descriptografar no nome
        		printf("%c", linha[z] - 52);
        		z++;
			}
        	gotoxy(60,y);
			printf("|");
			gotoxy(67,y);
			fgets(linha, sizeof(linha), arquivo); // vai escrever a senha sem descriptografar
			printf("%s", linha);
        	i++;
        	y++;
    	}
    	fclose(arquivo);
		gotoxy(1,25);
    	printf("\n\n\n\n\nAperte ENTER para voltar...");
		getch();
	}
}
//-----------------------------------------------------------------------------------------------------------
void menu(){
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
