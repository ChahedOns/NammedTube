#include"ser_cli_fifo.h"
#include"handlers.h"

//Definition de handlers
void hand_wakeUpClt(int sig){

	printf("Bonne réception de la réponse!\n");
	
	
}
 
void hand_endServ(int sig){
	
	printf("Fin de tâche! \n");
	exit(2);
}
int f1,f2;
main(){
/*Déclarations */
struct response rs ; 
struct request rq ; 

/* Création des tubes nommés */

if ( mkfifo(FILE1,0666) == -1 ){
	perror("Error lors de la création du tube 1 !");
}
if ( mkfifo(FILE2,0666) == -1 ){
	perror("Error lors de la création du tube 2 !");
}

/*initialisation du générateur de nombres aléatoires*/

srand(getpid());

/* Ouverture des tubes nommés */

f1 = open(FILE1,O_RDONLY);
f2 = open(FILE2 ,O_WRONLY);
if ( f1 == -1 || f2 == -1)
{
printf (" Ouverture des tubes impossible \n");
exit(-1);
};
printf(" valeur de f1 = %d \n valeur de f2 = %d \n ", f1,f2 );
/* Installation des Handlers */
	
	signal(SIGINT,hand_endServ);
	signal(SIGUSR1,hand_wakeUpClt);
while(1){
	printf("im here!\n");
	/* lecture d’une question */
		 read (f1 ,&rq , sizeof ( struct request ));
		 printf("le nbr n = %d", rq.n);
		 /* construction de la réponse */
		 int i;
		 for (i = 0; i < rq.n; i++)
		 {
			 rs.t[i] = rand()%50;
			 printf("valeur  =%d \n", rs.t[i]);
		}
		rs.idc = rq.id;
		rs.ids = getpid();
	/* envoi de la réponse */
		write(f2,&rs, sizeof (struct response));
	/* envoi du signal SIGUSR1 au client concerné */
		kill(rs.idc,SIGUSR1);
}

}
