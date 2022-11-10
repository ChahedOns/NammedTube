#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
request r;
response * s;

void hand_wakeUpClt(int sig){

//nlawjo 3la l réponse mtee3i fel fifo 2 ! 
read(f2,s, 1);

}

main(){
/* Déclarations */

int x;
/* Création des tubes nommés */

if ( mkfifo(fifo1,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH) == -1 ){
	perror("Error lors de la création du tube 1 !");
}
if ( mkfifo(fifo2,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH) == -1 ){
	perror("Error lors de la création du tube 2 !");
}

/* Ouverture des tubes nommés */

	f1 = open(fifo1 , O_WRONLY);
	f2 = open(fifo2, O_RDONLY);

/* Installation des Handlers */
	signal(SIGUSR1, hand_wakeUpClt());

/* Construction et envoi d’une question */
		printf("Saisie un entier\n");
		scanf("%d",&x);
		//Construcction de la question
		r.id= getpid();
		r.n=x;
		//envoi
		write(f1,r);
/* Attente de la réponse */
		pause();
/* Lecture de la réponse */
		read(f2,s,1);
/* Envoi du signal SIGUSR1 au serveur */
		kill (s.ids,SIGUSR1);
/* Traitement local de la réponse */
		int i=0;
		printf("La réponse du Serveur est : ")
		for (int i=0 ; i<x;i++){
			printf("%d ", s.t[i]);
		}
	close(f1);
	close(f2);
}