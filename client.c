#include "ser_cli_fifo.h"
#include "handlers.h"
struct request r;
struct response s;
int f1,f2;
void hand_wakeUpClt(int sig){
printf("Client is up!");
printf("\n" );

}

main(){
/* Déclarations */

int x;
/* Création des tubes nommés */

/*if ( mkfifo(F1,0666) == -1 ){
	perror("Error lors de la création du tube 1 !");
}
if ( mkfifo(F2,0666) == -1 ){
	perror("Error lors de la création du tube 2 !");
}*/

/* Ouverture des tubes nommés */

	f1 = open(FILE1,O_WRONLY);
	f2 = open(FILE2,O_RDONLY);
	if ( f1 == -1 || f2 == -1)
	{
	printf (" Ouverture des tubes impossible ");
	exit(-1);
	};
	printf(" valeur de f1 = %d \n valeur de f2 = %d ", f1,f2 );

/* Installation des Handlers */
	signal(SIGUSR1, hand_wakeUpClt);

/* Construction et envoi d’une question */
		printf("Saisie un entier\n");
		scanf("%d",&x);
		//Construcction de la question
		r.id= getpid();
		r.n=x;
		//envoi
		write(f1,&r , sizeof(struct request ));
/* Attente de la réponse */
		pause();
/* Lecture de la réponse */
		read(f2,&s , sizeof (struct response ));
/* Envoi du signal SIGUSR1 au serveur */
		kill (s.ids,SIGUSR1);
/* Traitement local de la réponse */
		
		printf("La réponse du Serveur est : ");
		int i;
		for (i=0; i<x;i++){
			printf("%d ", s.t[i]);
		}
	close(f1);
	close(f2);
}
