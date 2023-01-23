#include "../include/queries.h"

struct aux_driver{
    char *id;
    char* nome;
    double avaliacao;
    int contador;
};

struct aux_user{
    char *username;
    char *nome;
    int distotal;
    Data viagem_recente;
};


typedef struct aux_driver* AUX_DRIVER;
typedef struct aux_user* AUX_USER;

void query1_users(Catalogos catalogo, char *username, int linha){
    char* novousername = strsep(&username,"\n");
    User user = g_hash_table_lookup(catalogo->user, novousername);
    if(strcmp("active",get_account_status_user(user))==0){
        char buffer[128];
        sprintf(buffer, "Resultados/command%d_output.txt", linha);
        FILE *query1txt_user = fopen(buffer, "w");
        char *nome = get_name_list_user(catalogo, novousername);
        char *gender = get_gender_list_user(catalogo, novousername);
        int idade = get_idade_list_User(catalogo, novousername);
        double avaliacao_media = get_avaliacao_media_user(catalogo, novousername);
        int numero_viagens = get_numero_viagens_user(catalogo, novousername);
        double total_gasto = get_total_gasto(catalogo, novousername);
        fprintf(query1txt_user, "%s;%s;%i;%.3f;%i;%.3f\n", nome, gender, idade, avaliacao_media, numero_viagens, total_gasto);
        fclose(query1txt_user);        
    }
    else{
        char buffer[128];
        sprintf(buffer, "Resultados/command%d_output.txt", linha);
        FILE *query1txt_user = fopen(buffer, "w");
        fclose(query1txt_user);
    }
}

void query1_drivers(Catalogos catalogo, char *id, int linha){
    char* novoid = strsep(&id,"\n");
    Driver drivers = g_hash_table_lookup(catalogo->Driver, novoid);
    if(strcmp("active",get_account_status_driver(drivers))==0){
        char buffer[128];
        sprintf(buffer, "Resultados/command%d_output.txt", linha);
        FILE *query1txt_driver = fopen(buffer, "w");
        char *nome = get_name_list_driver(catalogo,novoid);
        char *gender = get_gender_list_driver(catalogo,novoid);
        int idade = get_idade_list_driver(catalogo,novoid);
        double avaliacao_media = get_avaliacao_media(catalogo,novoid);
        int numero_viagens = get_numero_viagens(catalogo,novoid);
        double total_euferido = get_total_euferido(catalogo,novoid);
        fprintf(query1txt_driver, "%s;%s;%i;%.3f;%i;%.3f\n", nome, gender, idade, avaliacao_media, numero_viagens, total_euferido);
        fclose(query1txt_driver);        
    }
    else{
        char buffer[128];
        sprintf(buffer, "Resultados/command%d_output.txt", linha);
        FILE *query1txt_driver = fopen(buffer, "w");
        fclose(query1txt_driver);
    }
}

void query2 (Catalogos catalogo, char* N, int linha){
    char buffer[128];
    sprintf(buffer, "Resultados/command%d_output.txt", linha);
    FILE *query2txt = fopen(buffer, "w");
    GList* sorted = auxquerie2(catalogo);
    for (size_t i = 0; i < atoi(N); i++) {
        AUX_DRIVER driver = g_list_nth_data(sorted, i);
        fprintf(query2txt, "%s;%s;%.3f\n", driver->id,driver->nome,(driver->avaliacao)/(driver->contador));
    }
}

void query3 (Catalogos catalogo, char* N, int linha){
    char buffer[128];
    sprintf(buffer, "Resultados/command%d_output.txt", linha);
    FILE *query3txt = fopen(buffer, "w");
    GList* sorted = auxquerie3(catalogo);
    for (size_t i = 0; i < atoi(N); i++) {
        AUX_USER user = g_list_nth_data(sorted, i);
        fprintf(query3txt, "%s;%s;%i\n", user->username, user->nome, user->distotal);
    }
}

void query4 (Catalogos catalogo, char* city, int linha){
    char buffer[128];
    sprintf(buffer, "Resultados/command%d_output.txt", linha);
    FILE *query4txt = fopen(buffer, "w");
    double preco_medio = get_preco_medio_city(catalogo, city);
    fprintf(query4txt, "%.3f\n", preco_medio);
    fclose(query4txt);
}

void query5 (Catalogos catalogo, char* data_inicial, char* data_final, int linha){
    char buffer[128];
    sprintf(buffer, "Resultados/command%d_output.txt", linha);
    FILE *query5txt = fopen(buffer, "w");
    double preco_medio_data = get_preco_medio_data(catalogo, data_inicial, data_final);
    fprintf(query5txt, "%.3f\n",preco_medio_data);
    fclose(query5txt);
}

void query6 (Catalogos catalogo, char* city, char* data_inicial, char* data_final, int linha){
    char buffer[128];
    sprintf(buffer, "Resultados/command%d_output.txt", linha);
    FILE *query6txt = fopen(buffer, "w");
    double distancia_media = get_distancia_media_city(catalogo,city,data_inicial,data_final);
    fprintf(query6txt, "%.3f\n",distancia_media);
    fclose(query6txt);
}