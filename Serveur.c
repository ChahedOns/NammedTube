#include"ser_cli_fifo.h"
#include"handlers.h"

//Definition de handlers
void hand_wakeUpClt(int sig){

	printf("Bonne réception de la réponse!\n");
}
 
void hand_endServ(int sig){
	if (sig == SIGKIL){
	printf("Fin de tâche! \n");
	exit();}
}

main(){
/*Déclarations */
response rs ; 
request rq ; 

/* Création des tubes nommés */

if ( mkfifo(fifo1,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH) == -1 ){
	perror("Error lors de la création du tube 1 !");
}
if ( mkfifo(fifo2,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH) == -1 ){
	perror("Error lors de la création du tube 2 !");
}

/*initialisation du générateur de nombres aléatoires*/

srand(getpid());

/* Ouverture des tubes nommés */

f1 = open(fifo1, O_RDONLY);
f2 = open(fifo2 , O_WRONLY);


/* Installation des Handlers */
	
	signal(SIGINT,hand_endServ);
	signal(SIGUSR1,hand_wakeUpClt);
while(1){
	/* lecture d’une question */
		 read(f1,rq,1);
	/* construction de la réponse */
		for (int i=0 ; i<rq.n ; i++){
			rs.t[i] = rand();
		}
		rs.idc = rq.id;
		rs.ids = getpid();
	/* envoi de la réponse */
		write(f2,rs);
	/* envoi du signal SIGUSR1 au client concerné */
		kill(rs.id,SINGUSR1);
}
close(f1);
close(f2);

}