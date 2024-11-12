Name: Mihai Dragos-Adnrei
Grupa: 342C5


    In cadrul acestei teme am avut de realizat un sistem de autentificare de tip OAuth2 utilizand protocolul RPC. 
Sunt imlpementate 2 componente principale client si server. Clientul la initializare citeste un fisier de comenzi si initializeaza o structura interna pentru a salva viitoarele credentiale. Server-ul la initializare citeste fisierele primite ca argumente si initializeaza structuri interne, Structurile folosite de server sunt: "users" care retine credentialele fiecarui posibil viitor user, "resourcesFiles" contine toate fisierele server-ului si "permissions" este o matrice in care fiecare linie reprezinta un set de permisiuni. 

    In cadrul proiectului sunt 2 flow principale, autentificare si executia unei comenzi

    1. Autentificare

        - Clientul trimite un requeste de authentificare in care adauga id sau si o valoare care identifica alegerea sa pentr auto refresh.

        - Server verifica in baza sa de date daca clientul trimite un id recunoscut. In caz afirmativ raspunde cu un token de autentificare. In caz negativ raspunde cu un mesaj de "USER_NOT_FOUND".

        - Clientul trimite un request de permisiuni catre server pentru a obtine permisiuni.

        - Server primeste token-ul de autentificare, si raspunde cu un signed_token. Signed token este construit prin alipirea auth_token cu permisiunile primite, acestea fiind separate de ",". Aceasta structura este criptata prin adunarea fiecarui caracter cu cheia secreta (key = 15). De exemplu, daca auth_token='123456789' si perms='Files' 'RX' atunci 
        unsigned_token = '123456789,Files,RX', apoi aceasta structura va fi criptate si trimisa catre server. In cazul in care clientul nu primeste permisiuni '*,-", server-ul va trimite "REQUEST_DENIED".

        - Clientul trimmite signet_token pentru a obtine un bearer token.

        - Serverul contruieste bearer token pe baza decriptarii signed token primit. Signed token este decriptate, descompus in auth token si permisiuni. Pe baza auth token acesta contruieste access token, refresh token(daca clientul a optat pentru el) si ttl.

        - Clientul primeste bearer token si il salveaza local.

    2. Executia unei comenzi

        - Clientul trimite un request de executare a unei actiuni pe un fisier. Ataseaza si access token. In cazul in care refresh token nu este NULL si ttl a expirat acesta trimite un request de reinoire a bearer token, folosind refresh_token. 

        - Server-ul verifica valabiitatea cererii si trimite un raspuns.
