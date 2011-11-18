** INSTALLATION **

1) Kontakt Place2book (www.place2book.com) og få oprettet konti (test-konto og driftskonto)
2) Når kontoen er oprettet, kopieres API-key fra siden https://www.place2book.com/da/event_makers#tab4 
3) Indstil modulet i ding på siden "Place2book settings" ( /admin/settings/ding/place2book )


** DOKUMENTATION **

PLACE2BOOK:
Modulet kobler op mod Place2books API. Læs mere om denne API på https://github.com/place2book/place2book-api/wiki

INDSTILLINGER i D!NG (siden /admin/settings/ding/place2book):
- "Place2Book service URL" skal pege på Place2books Event API. URLen er https://www.place2book.com/da/event_api
- "Place2Book base API key" indeholder den generelle API nøgle når der forbindes til Place2book. Hvis du angiver API nøgler for et specifikt bibliotek (nedenfor), vil events relateret til det bibliotek bruge dén API nøgle i stedet for den generelle API nøgle. 
- API key {BIBLIOTEKSNAVN}. Disse vil være forskellige i antal fra installation til installation. Hvert bibliotek oprettet i ding kan tilknyttes sin egen konto hos Place2book. I det tilfælde tilsidesættes den generelle API nøgle til fordel for den angive nøgle når der sendes data på events relateret til dét bibliotek.
- Place2book-standardværdier (Kapacitet, Vedligehold kopi, Kultunaut Export). Disse felter findes på hver event oprettet i ding. Når nye events oprettes, er værdierne herfra allerede indsat i det event man er ved at oprette.

KULTUNAUT:
Modulet sender også de data til Place2book, som bruges når Place2book videresender oplysninger om arrangementet til Kultunaut. Som billede til Kultunaut bruges listevisningsbilledet fra indholdet i ding. Som emneord til Kultunaut medsendes eventets emneord fra Event Target og Event Category. Disse svarer typisk ikke til de emneord, der bruges på Kultunaut, men Kultunaut kan bruge disse til at placere arrangementet rigtigt. Til version 1.1 af ding_place2book planlægges indstillinger, hvormed man kan oversætte emneordene i ding til kultunat emneord, således at Kultunaut får de ønskede emneord fra starten. 


** VERSIONSINFORMATION **

v1.0.1: Rettelse der lukker sikkerhedshul, hvor alle brugertyper kunne tilgå indstillingerne (siden /admin/settings/ding/place2book). Ved opgradering fra version 1.0.0, skal update.php køres, eller cachen tømmes. 


** TIPS **

1) Man kan have flere konti hos Place2book. Der er i ding_place2book mulighed for at angive en separat API-key pr. bibliotek.

2) Eksempel på en SQL der kan køres på en eksisterende ding-hjemmeside for at trække indhold ud der har et link i brødteksten til Place2book. Vi har brugt den i Vejle til at generere ding_place2book tabellen, som anvendes af modulet. Vi kunne derved lave en mere glidende overgang da modulet blev taget i brug på vores driftssite og eksisterende driftskonto hos Place2book:

SELECT r.nid, substring(r.body, (LOCATE('place2book.com/event/', r.body)+21), (LOCATE('">Bestil billet', r.body) - (LOCATE('place2book.com/event/', r.body)) -21 ) ) AS place2book_id, 1 AS maintain_copy, 0 AS kultunaut_export FROM {node} n JOIN {node_revisions} r ON n.nid=r.nid WHERE n.type = 'event' AND r.body LIKE '%place2book.com/event/%';

Derefter var det dog nødvendigt manuelt at rette kapacitet til på alle events, der ikke havde ubegrænset adgang - ellers ville ding_place2book have overskrevet disse værdier på Place2book-kontoen.

