//AEP 2024 - Fernando Queiroz 24038237-2 | Murilo Pagotto Specian 24055172-2 | Daniel Mitsuo Tsuyama 24160006-2 
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.c>
#include <ctype.h>
#define SHIFT 5
// variaveis globais
FILE *arquivo;
int tot = 0;
char nomes[50][20],senhas[50][15];
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// declaração das funções
int verificasenha(char* s, int *p);
void criptografia(char* n, char* s);
void editarnumero(int n);
void descriptografar();
void armazenarnomes();
void organizanomes();
void gravarnomes();
void criar();
void remover();
void listar();
void creditos();
void editar();
void menu(char *p);
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
	const char* frase = "Obrigado pela sua participação, espero que tenha gostado.";
	const char* carinha = "=)";
	char op;
	int i;
	setlocale(LC_ALL,"portuguese"); // seta a linguagem pra portugues, dai da pra usar acento e esses bglh
	armazenarnomes(); // vai armazenar os nomes que estão salvos no arquivo
	do{
		organizanomes();
		menu(&op);
	} while(op!= '0');
	gravarnomes(); // vai gravar os nomes que estão dentro do vetor
	system("cls");
	i=0;
	gotoxy(35,15);
	// vai escrever a frase final parecendo q esta sendo escrito mó massa
	while(frase[i] != '\0'){
		printf("%c", frase[i]);
		fflush(stdout);
        Sleep(100);
        i++;
	}
	i=0;
	printf("\n");
	gotoxy(60,16);
	while(carinha[i] != '\0'){
		printf("%c", carinha[i]);
		fflush(stdout);
    	Sleep(100);
        i++;
	}
	Sleep(1);
	gotoxy(1,25);
	printf("\n\n\n\n\n");
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int verificasenha(char* s, int *p){ // vai verificar se a senha está nas regras
	int i, minuscula, maiuscula, numero, especial = 0;

	if (strlen(s) < 8 || strlen(s) > 12){ // c nao tiver dentro desse limite nem entra
		*p += 1;
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
		*p += 1;
		return 0;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void gravarnomes(){ // gravar os nomes alterados no vetor dentro do txt
	arquivo = fopen("Usuarios.txt", "w");
	for(int x = 0; x < tot; x++){
		if(x == 0) fprintf(arquivo, "%s\n%s", nomes[0], senhas[0]); // c for o primeiro a ser escrito, ele nao vai pular a linha antes
		else fprintf(arquivo, "\n%s\n%s", nomes[x], senhas[x]); // c nao foi o primeiro, ele vai pular antes, pq c ficar o \n na senha final, fica com um espaço sobrando
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void armazenarnomes(){ // armazena os nomes nas variaveis
	char linha[20];
	arquivo = fopen("Usuarios.txt", "r");
	tot = 0;
	
	if (arquivo == NULL){ // esse bglh é quando o arquivo nao existe
		arquivo = fopen("Usuarios.txt", "w"); // c o arquivo nao existir ele vai criar um
		fclose(arquivo);
		return;
	}
	fseek(arquivo, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    if (ftell(arquivo) == 0) return;
	fseek(arquivo, 0, SEEK_SET);
	
	while(!feof(arquivo)){ // passa o txt linha por linha
		fgets(nomes[tot], 100, arquivo);
		nomes[tot][strcspn(nomes[tot], "\n")] = '\0'; // aqui ele finaliza o vetor com \0
		fgets(senhas[tot], 100, arquivo);
		senhas[tot][strcspn(senhas[tot], "\n")] = '\0'; // mema coisa
		tot++; // vai aumentar o total de nomes
	}
	fclose(arquivo);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void organizanomes(){ // vai organizar os nomes por ordem alfabetica
	char ntmp[20],stmp[15];
	for(int x = 0; x < tot; x++){
		for(int y = x + 1; y < tot; y++){
			if(strcmp(nomes[x],nomes[y]) > 0){
				// caso o nome y for maior que o nome x, vai inverter com o nome x
				strcpy(ntmp, nomes[x]);
				strcpy(nomes[x], nomes[y]);
				strcpy(nomes[y], ntmp);
				// aqui vai trocar a senha de acordo que trocar o nome
				strcpy(stmp, senhas[x]);
				strcpy(senhas[x], senhas[y]);
				strcpy(senhas[y], stmp);
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void criptografia(char* n, char* s){ // vai criptografar o nome e a senha e armazenar
	int i;
	char criptonome[20], criptosenha[15];
	// vai pegar cada caracter do nome e aumentar 5 caracteres a mais
	for (i = 0; i < strlen(n); i++) {
        criptonome[i] = n[i] + SHIFT;
    	}
    	criptonome[i] = '\0';
	// mema coisa só q na senha 
	for (i = 0; i < strlen(s); i++) {
        criptosenha[i] = s[i] + SHIFT;
    }
    criptosenha[i] = '\0';
	// aqui ele vai armazenar o nome e a senha no ultimo vetor e aumentar o total de usuarios
    strcpy(nomes[tot], criptonome);
    strcpy(senhas[tot], criptosenha);
    tot++;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void criar(){ // criar novos usuarios
	char nome[20],senha[15],repitasenha[15],opcao;
	int erro = 0;
	do{
		system("cls");
		textcolor(WHITE);
		printf("Envie 0 para voltar.\n");
		textcolor(BLUE);
		printf("				     ____   ______ ______ ____ _____ ______ ____   ____ \n");
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
			gets(nome);
		} while (strlen(nome) == 0 || strlen(nome) >= 20);
		nome[strcspn(nome, "\n")] = '\0';
		if(nome[0] == '0') return;
		do{ // fica repitindo a senha no mesmo lugar
	       gotoxy(40,16);
	       printf("                "); //limpa o campo
	       gotoxy(40,16);
	       gets(senha);
	       if(senha[0] == '0') return;
	       if(verificasenha(senha, &erro) == 0){ // c nao tiver os quisitos ele vai aparecer a mensagem
				gotoxy(26,17);
				printf("                                                                ");
				gotoxy(7,17);
				textcolor(RED);
	    		printf("Deve conter entre 8 a 12, caracteres um caracter especial, um numero, uma letra maiuscula e uma minuscula.");
	    		gotoxy(26,18); // aqui ele vai abaixar o repita senha
	    		textcolor(WHITE);
	    		printf("Repita senha: ");
		   }
	    } while (verificasenha(senha, &erro) == 0);
	    senha[strcspn(senha, "\n")] = '\0';
	    
		if(erro == 0){ // c nao teve nenhum erro ele vai direto
			do{
	    		gotoxy(40,17);
	    		printf("                                                                ");
	    		gotoxy(40,17);
	    		gets(repitasenha);
	    		if(repitasenha[0] == '0') return;
	    	} while (strcmp(repitasenha,senha) != 0);
	    } else { // c teve, vai abaixar a linha para pegar o repita senha
	    	do{
	    		gotoxy(40,18);
	    		printf("                                                                ");
	    		gotoxy(40,18);
	    		gets(repitasenha);
	    		if(repitasenha[0] == '0') return;
	    	} while (strcmp(repitasenha,senha) != 0);
		}
		
		criptografia(nome,senha); // vai chama a funçao pra criptografar e armazenar
		system("cls");
		textcolor(GREEN);
		
		printf("\n\n\n\n\n\n\n\n\n\n\n            ______ ___     ____   ___    _____ ______ ____   ____      ______ ______ ____ ______ ____     __\n");
		printf("           / ____//   |   / __ | /   |  / ___//_  __// __ | / __ |    / ____// ____//  _//_  __// __ |   / /\n");
		printf("          / /    / /| |  / / / // /| |  |__ |  / /  / /_/ // / / /   / /_   / __/   / /   / /  / / / /  / / \n");
		printf("         / /___ / ___ | / /_/ // ___ | ___/ / / /  / _  _// /_/ /   / __/  / /___ _/ /   / /  / /_/ /  /_/  \n");
		printf("         |____//_/  |_|/_____//_/  |_|/____/ /_/  /_/ |_| |____/   /_/    /_____//___/  /_/   |____/  (_)   \n");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		Sleep(1); // delay de 1 segundo
	} while(nome[0] != '0' && senha[0] != '0');
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void remover() { // vai listar os usuarios e pedir pro usuario escolher qual ele quer remover
    int numero, opcao;
    do{
    	organizanomes();
	    system("cls");
	    textcolor(WHITE);
	    printf("Envie 0 para voltar.\n");
	    textcolor(RED);
	    printf("				      ____   ______ __  ___ ____  _    __ ______ ____ \n");
	    printf("				     / __ | / ____//  |/  // __ || |  / // ____// __ |\n");
	    printf("				    / /_/ // __/  / /|_/ // / / /| | / // __/  / /_/ /\n");
	    printf("				   / _  _// /___ / /  / // /_/ / | |/ // /___ / _  _/ \n");
	    printf("				  /_/ |_|/_____//_/  /_/ |____/  |___//_____//_/ |_|  \n");
	    
	    arquivo = fopen("Usuarios.txt", "r");
		int c = fgetc(arquivo);  // Lê o primeiro caractere do arquivo
		if (c == EOF && tot == 0){ // c nao tiver nada no arquivo ele fala que nao tem nada e pede pra voltar
	    	gotoxy(47,16);
	    	textcolor(WHITE);
	    	printf("Nenhum usuário cadastrado.\n");
	    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	    	printf("Pressione ENTER para voltar...");
	    	getch();
	    	fclose(arquivo);
	    	return;
		}
		
		textcolor(WHITE);
	    gotoxy(47,10);
		printf("NOME         |         SENHA\n");
		gotoxy(60,11);
		printf("|");
		gotoxy(60,12);
		printf("|");
		
		for(int i = 0; i < tot; i++){ // vai passar por todos os nomes que tem cadastrados
			gotoxy(36, 12 + i);
			printf("%d - ", i + 1); // vai contar as linhas
			gotoxy(41, 12 + i);
    		for(int x = 0; x < strlen(nomes[i]); x++){ //vai pegar caracter por caracter e descriptografar o nome
        		printf("%c", nomes[i][x] - 5);
			}
        	gotoxy(60, 12 + i);
			printf("|");
			gotoxy(67, 12 + i);
			printf("%s", senhas[i]);
    	}
    	
    	do{
    		printf("\n\n\n\nNúmero para remover: "); // pede para o usuario digitar um numero para excluir
    		scanf("%d",&numero);
    	} while(numero > tot);
    	
    	if(numero == 0) return;
    	
		for(int x = numero-1; x < tot-1; x++){
			// aqui ele vai tirar o usario que quer ser removido, fznd os que estao em cima vir pra baixo
    		strcpy(nomes[x], nomes[x+1]);
    		strcpy(senhas[x], senhas[x+1]);
    	}
    	
    	tot--;
		system("cls");
		textcolor(GREEN);
		gotoxy(1,12);
		printf("        __  __ _____  __  __ ___     ____   ____ ____       ____   ______ __  ___ ____  _    __ ____ ____   ____ \n");
		printf("       / / / // ___/ / / / //   |   / __ | /  _// __ |     / __ | / ____//  |/  // __ || |  / //  _// __ | / __ |\n");
		printf("      / / / / |__ | / / / // /| |  / /_/ / / / / / / /    / /_/ // __/  / /|_/ // / / /| | / / / / / / / // / / /\n");
		printf("     / /_/ / ___/ // /_/ // ___ | / _  _/_/ / / /_/ /    / _  _// /___ / /  / // /_/ / | |/ /_/ / / /_/ // /_/ / \n");
		printf("     |____/ /____/ |____//_/  |_|/_/ |_|/___/ |____/    /_/ |_|/_____//_/  /_/ |____/  |___//___//_____/ |____/  \n");
		textcolor(WHITE);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
		Sleep(1);
    } while (numero != 0);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void listar(){ // listar os usuarios
	char t;
	system("cls");
	textcolor(MAGENTA);
	printf("                                  __  __ _____  __  __ ___     ____   ____ ____  _____\n");
	printf("                                 / / / // ___/ / / / //   |   / __ | /  _// __ |/ ___/\n");
	printf("                                / / / / |__ | / / / // /| |  / /_/ / / / / / / /|__ | \n");
	printf("                               / /_/ / ___/ // /_/ // ___ | / _  _/_/ / / /_/ /___/ / \n");
	printf("                               |____/ /____/ |____//_/  |_|/_/ |_|/___/ |____//____/  \n");
	arquivo = fopen("Usuarios.txt", "r");
	int c = fgetc(arquivo);  // Lê o primeiro caractere do arquivo
    if (c == EOF && tot == 0) { // c nao tiver nada no arquivo ele fala que nao tem nada e pede pra voltar
    	gotoxy(47,16);
    	textcolor(WHITE);
    	printf("Nenhum usuário cadastrado.\n");
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	printf("Pressione ENTER para voltar...");
    	getch();
    	fclose(arquivo);
    	return;
	}
	
	else{
		textcolor(WHITE);
	    gotoxy(47,10);
		printf("NOME         |         SENHA\n");
		gotoxy(60,11);
		printf("|");
		gotoxy(60,12);
		printf("|");
		
		for(int i = 0; i < tot; i++){ // vai passar por todos os nomes que tem cadastrados
        	gotoxy(41,12 + i);
    		for(int z = 0; z < strlen(nomes[i]); z++){ //vai pegar caracter por caracter e descriptografar no nome
        		printf("%c", nomes[i][z] - SHIFT);
			}
        	gotoxy(60,12 + i);
			printf("|");
			gotoxy(67,12 + i);
			printf("%s", senhas[i]);
    	}

		gotoxy(1,25);
    	printf("\n\n\n\n\nAperte ENTER para voltar...");
		getch();
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void editar(){ // editar os usuarios
	char t;
    int numero;
    do{
    	system("cls");
    	organizanomes();
    	textcolor(WHITE);
    	printf("Envie 0 para voltar.\n");
	    textcolor(YELLOW);
		printf("\n                                          ______ ____   ____ ______ ___     ____ \n");
		printf("                                         / ____// __ | /  _//_  __//   |   / __ |\n");
		printf("                                        / __/  / / / / / /   / /  / /| |  / /_/ /\n");
		printf("                                       / /___ / /_/ /_/ /   / /  / ___ | / _  _/ \n");
		printf("                                      /_____//_____//___/  /_/  /_/  |_|/_/ |_|  \n");
		
		arquivo = fopen("Usuarios.txt", "r");
		int c = fgetc(arquivo);  // Lê o primeiro caractere do arquivo
    	if (c == EOF && tot == 0) { // c nao tiver nada no arquivo ele fala que nao tem nada e pede pra voltar
	    	gotoxy(47,16);
	    	textcolor(WHITE);
	    	printf("Nenhum usuário cadastrado.\n");
	    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	    	printf("Pressione ENTER para voltar...");
	    	getch();
	    	fclose(arquivo);
	    	return;
		}
		
		else{
			textcolor(WHITE);
		    gotoxy(47,10);
			printf("NOME         |         SENHA\n");
			gotoxy(60,11);
			printf("|");
			gotoxy(60,12);
			printf("|");
			
			for(int i = 0; i < tot; i++){ // vai passar por todos os nomes que tem cadastrados
				gotoxy(36,12 + i);
				printf("%d - ", i + 1); // vai contar as linhas
				gotoxy(41,12 + i);
				
	    		for(int z = 0; z < strlen(nomes[i]); z++){ //vai pegar caracter por caracter e descriptografar no nome
	        		printf("%c", nomes[i][z] - SHIFT);
				}
				
	        	gotoxy(60,12 + i);
				printf("|");
				gotoxy(67,12 + i);
				printf("%s", senhas[i]);
	    	}
	    	

	    	printf("\n\n\n\nNúmero para editar (0 para voltar): "); // pede para o usuario digitar um numero para excluir
	    	scanf("%d",&numero);
	    	
	    	if(numero == 0) return;
	    	editarnumero(numero);
		}
    } while (numero != 0);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void editarnumero(int n){ // vai enviar o usuario que vai ser editado, e a opcao que foi escolhido
    char novonome[20], novasenha[15];
	int i, o, erro = 0;
	system("cls");
	printf("Envie 0 para voltar.\n");
	textcolor(YELLOW);
	printf("                                          ______ ____   ____ ______ ___     ____ \n");
	printf("                                         / ____// __ | /  _//_  __//   |   / __ |\n");
	printf("                                        / __/  / / / / / /   / /  / /| |  / /_/ /\n");
	printf("                                       / /___ / /_/ /_/ /   / /  / ___ | / _  _/ \n");
	printf("                                      /_____//_____//___/  /_/  /_/  |_|/_/ |_|  \n");
	textcolor(WHITE);
	gotoxy(50,15);
	printf("1 - Editar o nome\n");
	gotoxy(50,16);
	printf("2 - Editar a senha\n");
	gotoxy(50,17);
	printf("3 - Editar o nome e senha\n");
	gotoxy(50,18);
	printf("0 - Voltar\n");
	gotoxy(1,25);
	do{
		printf("\n\n\n\n\nOpção: ");
		scanf("%d",&o);
	} while (o != 1 && o != 2 && o != 3 && o != 0);
	
	if(o == 0) return;

    for(int i = 15; i < 19; i++){
    	gotoxy(40,i);
    	printf("                                                                             \n"); // vai limpar a parte de baixo do editar
	}
	
	gotoxy(1,25);
    printf("\n\n\n\n\n          "); // apaga a opcao
    
	switch (o){
		case 1: // nome
    		gotoxy(42,15);
    		printf("Novo nome: ");
    		getchar();
    		do{
				gotoxy(53,15);
    			printf("                                                              "); //limpa o campo
    			gotoxy(53,15);
    			gets(novonome);
			} while (strlen(novonome) < 0 || strlen(novonome) > 20); // repete até ter menos q 20 caracter e mais q 0
    		
			if(novonome[0] == '0') return; // c o cara enviar 0 ele volta
			
			for (i = 0; i < strlen(novonome); i++) {
		        novonome[i] = novonome[i] + SHIFT;
		    }
		    novonome[i] = '\0';
			
			strcpy(nomes[n-1], novonome); // vai armazenar o novo nome criptografado no vetor que foi selecionado
    		break;
    	case 2: // senha
    		gotoxy(41,15);
    		printf("Nova senha: ");
    		getchar();
    		do{ // fica repitindo a senha no mesmo lugar
				gotoxy(53,15);
				printf("                "); //limpa o campo
				gotoxy(53,15);
    			gets(novasenha);
        		if(verificasenha(novasenha, &erro) == 0){ // c nao tiver os quisitos ele vai aparecer a mensagem
					gotoxy(7,16);
					textcolor(RED);
	    			printf("Deve conter entre 8 a 12, caracteres um caracter especial, um numero, uma letra maiuscula e uma minuscula.");
	    			textcolor(WHITE);
	   			}
    		} while (verificasenha(novasenha, &erro) == 0);
    		
			if(novasenha[0] == '0') return;
    		
			for (i = 0; i < strlen(novasenha); i++) {
		        novasenha[i] = novasenha[i] + SHIFT;
		    }
		    novasenha[i] = '\0';
    		
    		strcpy(senhas[n-1], novasenha); // // vai armazenar a nova senha criptografada no vetor que foi selecionado
    		break;
    	case 3: // nome e senha
    		gotoxy(42,15);
    		printf("Novo nome: ");
    		gotoxy(41,16);
    		printf("Nova senha: ");
    		getchar();
    		do{
				gotoxy(53,15);
    			printf("                                                              "); //limpa o campo
    			gotoxy(53,15);
    			gets(novonome);
			} while (strlen(novonome) == 0 || strlen(novonome) >= 20); // repete até ter menos q 20 caracter e mais q 0
			
			do{ // fica repitindo a senha no mesmo lugar
				gotoxy(53,16);
				printf("                "); //limpa o campo
				gotoxy(53,16);
    			gets(novasenha);
        		if(verificasenha(novasenha, &erro) == 0){ // c nao tiver os quisitos ele vai aparecer a mensagem
					gotoxy(7,17);
					textcolor(RED);
	    			printf("Deve conter entre 8 a 12, caracteres um caracter especial, um numero, uma letra maiuscula e uma minuscula.");
	    			textcolor(WHITE);
	   			}
    		} while (verificasenha(novasenha, &erro) == 0);
    		// c o cara enviar 0 ele retorna
    		if(novonome[0] == '0') return;
    		if(novasenha[0] == '0') return;
    		
    		// mema coisa da criptografia passada
			for (i = 0; i < strlen(novonome); i++) {
		        novonome[i] = novonome[i] + SHIFT;
		    }
		    novonome[i] = '\0';
		    
			for (i = 0; i < strlen(novasenha); i++) {
		        novasenha[i] = novasenha[i] + SHIFT;
		    }
		    novasenha[i] = '\0';
		    // armazena os dois
    		strcpy(nomes[n-1], novonome);
    		strcpy(senhas[n-1], novasenha);
    		
    		break;
	}

	system("cls");
	textcolor(GREEN);
	gotoxy(1,12);
	printf("          __  __ _____  __  __ ___     ____   ____ ____       ______ ____   ____ ______ ___     ____   ____ \n");
	printf("         / / / // ___/ / / / //   |   / __ | /  _// __ |     / ____// __ | /  _//_  __//   |   / __ | / __ |\n");
	printf("        / / / / |__ | / / / // /| |  / /_/ / / / / / / /    / __/  / / / / / /   / /  / /| |  / / / // / / /\n");
	printf("       / /_/ / ___/ // /_/ // ___ | / _  _/_/ / / /_/ /    / /___ / /_/ /_/ /   / /  / ___ | / /_/ // /_/ /  \n");
	printf("       |____/ /____/ |____//_/  |_|/_/ |_|/___/ |____/    /_____//_____//___/  /_/  /_/  |_|/_____/ |____/  \n");
	textcolor(WHITE);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	Sleep(1);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void creditos(){ // criadores (foi só o fernando que fez kkk)
	int o;
	while(o != 48){
		system("cls");
		textcolor(CYAN);
		printf("\n				     ______ ____   ______ ____   ____ ______ ____  _____\n");
		printf("				    / ____// __ | / ____// __ | /  _//_  __// __ |/ ___/\n");
		printf("				   / /    / /_/ // __/  / / / / / /   / /  / / / /|__ | \n");
		printf("				  / /___ / _  _// /___ / /_/ /_/ /   / /  / /_/ /___/ / \n");
		printf("				  |____//_/ |_|/_____//_____//___/  /_/   |____//____/  \n");
		textcolor(WHITE);
		gotoxy(50,16);
		printf("1 - Fernando Queiroz\n");
		gotoxy(50,17);
		printf("2 - Daniel Mitsuo Tsuyama\n");
		gotoxy(50,18);
		printf("3 - Murilo Pagotto Specian\n");
		gotoxy(50,19);
		printf("0 - Voltar");
		gotoxy(6,25);
		printf("\n\n\n\n\nOpção: ");
		o = getch();
		printf("%d",o);
		switch (o){
			case 49: // 1 em tabela ascii
				system("cls");
				textcolor(RED);
				printf("\n				     ______                                      __     \n");
				printf("				    / ____/___   _____ ____   ____ _ ____   ____/ /____ \n");
				printf("				   / /_   / _ | / ___// __ | / __ `// __ | / __  // __ |\n");
				printf("				  / __/  /  __// /   / / / // /_/ // / / // /_/ // /_/ /\n");
				printf("				 /_/     |___//_/   /_/ /_/ |__,_//_/ /_/ |__,_/ |____/ \n");
				gotoxy(1,16);
				textcolor(WHITE);
				printf("				  RA: 24038237-2\n");
				printf("			    Linkedin: https://www.linkedin.com/in/fernando-queiroz-6023a2304/\n");
				printf("			      GitHub: https://github.com/ferqueiroz\n"); // AEP parte por parte la
				printf("			   Instagram: @_ferqueiroz\n");
				gotoxy(1,25);
				printf("\n\n\n\n\nAperte ENTER para voltar...");
				getch();
				break;
			case 50: // 2 em tabela ascii
				system("cls");
				textcolor(RED);
				printf("\n					       ____                 _        __\n");
				printf("					      / __ | ____ _ ____   (_)___   / /\n");
				printf("					     / / / // __ `// __ | / // _ | / / \n");
				printf("					    / /_/ // /_/ // / / // //  __// /  \n");
				printf("					   /_____/ |__,_//_/ /_//_/ |___//_/   \n");
				gotoxy(1,16);
				textcolor(WHITE);
				printf("					  RA: 24160006-2\n");
				printf("			     Linkedin: https://www.linkedin.com/in/daniel-tsuyama-109841334/\n");
				printf("				   \n");
				printf("				   \n");
				gotoxy(1,25);
				printf("\n\n\n\n\nAperte ENTER para voltar...");
				getch();
				break;
			case 51:
				system("cls");
				textcolor(RED);
				printf("\n					       __  ___              _  __     \n");
				printf("					      /  |/  /__  __ _____ (_)/ /____ \n");
				printf("					     / /|_/ // / / // ___// // // __ |\n");
				printf("					    / /  / // /_/ // /   / // // /_/ /\n");
				printf("					   /_/  /_/ |__,_//_/   /_//_/ |____/ \n");
				gotoxy(1,16);
				textcolor(WHITE);
				printf("					  RA: 24055172-2\n");
				printf("			     Linkedin: https://www.linkedin.com/in/murilo-pagotto-6042b0305/\n");
				printf("				   \n");
				printf("				\n");
				gotoxy(1,25);
				printf("\n\n\n\n\nAperte ENTER para voltar...");
				getch();
				break;
		}
	}
	return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void menu(char *p){ // menu
	system("cls");
	textcolor(GREEN);
	printf("\n                                                __  ___ ______ _   __ __  __\n");
	printf("                                               /  |/  // ____// | / // / / /\n");
	printf("                                              / /|_/ // __/  /  |/ // / / / \n");
	printf("                                             / /  / // /___ / /|  // /_/ /  \n");
	printf("                                            /_/  /_//_____//_/ |_/ |____/   \n");
	printf("\n\n\n\n\n\n\n");
	textcolor(WHITE);
	printf("						1 - Criar usuários\n");
	printf("						2 - Remover usuários\n");
	printf("						3 - Editar usuários\n");
	printf("						4 - Listar usuários\n");
	printf("						5 - Créditos\n");
	printf("						0 - Sair e salvar\n"); // precisa enviar o 0 para salvar as alterações, se não nao salva
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("Opção: ");
	*p = getch();
	switch (*p){
		case '1':
			criar();
			break;
		case '2':
			remover();
			break;
		case '3':
			editar();
			break;
		case '4':
			listar();
			break;
		case '5':
			creditos();
			break;
		default:
			system("cls");
			break;
	}
}
