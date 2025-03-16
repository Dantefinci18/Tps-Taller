# Threads
- Codigo de Sockets sacado por la catedra: https://github.com/eldipa/sockets-en-cpp , Martin Di Paola.

- El commmon_thread.h fue sacado por la catedra: 
https://github.com/eldipa/hands-on-threads/blob/master/libs/thread.h , Martin Di Paola

- El common_queque.h fue sacado por la catedra: 
https://github.com/eldipa/hands-on-threads/blob/master/libs/queue.h , Martin Di Paola

- Justificacion de queues:
    
    Todas las queues que implemente son unbounded. 
    
    Para enviar (popear) los comandos del receiver al gameloop use una queue no bloqueante. De esta manera si la queue esta vacia puedo proceder con el gameloop y no se queda esperando a que se haga un push de un comando. Para recibir los comandos la queue se comporta como bloqueante debido a que quiero recibir el comando de alguna o otra forma. 
    
    Tanto para enviar como para recibir los ejecutados use una queue bloqueante. En el caso de pop quiero enviar una vez que recibi algo sino quiero que se quede esperando hasta recibir. Y en el caso de push quiero asegurarme que se reciba la informacion.
