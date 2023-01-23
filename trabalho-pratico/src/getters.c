#include "../include/getters.h"
#define ANO "09/10/2022"

struct aux_driver{
    char *id;
    char* nome;
    double avaliacao;
    int contador;
    Data viagem_recente;
};

struct aux_user{
    char *username;
    char *nome;
    int distotal;
    int ativo;
    Data viagem_recente;
};


int sort_function_driver(gconstpointer a, gconstpointer b){
    struct aux_driver *da = (struct aux_driver *)a;
    struct aux_driver *db = (struct aux_driver *)b;

    double avaliacao_a = da->avaliacao / da->contador;
    double avaliacao_b = db->avaliacao / db->contador;

    Data data_a = da->viagem_recente;
    Data data_b = db->viagem_recente;

    if (avaliacao_a < avaliacao_b) return 1;
    else if (avaliacao_a > avaliacao_b) return -1;
    else if (compara_datas(data_a,data_b)) return -1;
    else if (!compara_datas(data_a,data_b)) return 1;
    else return strcmp(da->id, db->id);
}

int sort_function_user(gconstpointer a, gconstpointer b){
    struct aux_user *ua = (struct aux_user *)a;
    struct aux_user *ub = (struct aux_user *)b;

    Data data_a = ua->viagem_recente;
    Data data_b = ub->viagem_recente;

    if (ua->distotal < ub->distotal) return 1;
    else if (ua->distotal > ub->distotal) return -1;
    else if (compara_datas(data_a,data_b)) return -1;
    else if (!compara_datas(data_a,data_b)) return 1;
    else return strcmp(ua->username, ub->username);
}

GList *remove_users(GList *list) {
    GList *current = list;
    while (current) {
        struct aux_user *user = (struct aux_user *) current->data;
        if (user->ativo == 0) {
            current = g_list_remove(list, current->data);
            continue;
        }
        current = g_list_next(current);
    }
    return list;
}

//-------------------------------------------------------------------------USERS----------------------------------------------------------------------------------------------------------------

char* get_name_list_user(Catalogos catalogos, char* username){
  char* novousername = strsep(&username,"\n");
  User user = g_hash_table_lookup(catalogos->user, novousername);
  char* name = g_strdup(get_name_user(user));
  return name;
} 

char* get_gender_list_user(Catalogos catalogos, char* username){
  char* novousername = strsep(&username,"\n");
  User user = g_hash_table_lookup(catalogos->user, novousername);
  char* gender = g_strdup(get_gender_user(user));
  return gender;
}

int get_idade_list_User(Catalogos catalogos, char* username){
  char* novousername = strsep(&username,"\n");
  int idade = 0;
  User user = g_hash_table_lookup(catalogos->user, novousername);
  if(user){
    char* birth_day = g_strdup(get_birth_date_user(user));
    Data nascimento = build_data(birth_day);
    Data ref = build_data(g_strdup(ANO));
    int ano_nascimento = get_ano(nascimento);
    int ano_ref = get_ano(ref);
    int mes_nascimento = get_mes(nascimento);
    int mes_ref = get_mes(ref);
    int dia_nascimento = get_dia(nascimento);
    int dia_ref = get_dia(ref);

    idade = (ano_ref) - (ano_nascimento);

    if(mes_nascimento>mes_ref||(mes_nascimento==mes_ref&&dia_nascimento>dia_ref)){
      idade = idade - 1;
    }
  }
  return idade;
}

// void get_status(Catalogos catalogos, char* username){
//   char* novousername = strsep(&username,"\n");
//   User user = g_hash_table_lookup(catalogos->user, novousername);
//   if(strcmp("active",get_account_status_user(user))==0){
//     printf("1");
//   }
//   else printf("0");
// }

//-------------------------------------------------------------------------DRIVERS----------------------------------------------------------------------------------------------------------------

char* get_name_list_driver(Catalogos catalogos, char* id){
  char* novoid = strsep(&id,"\n");
  Driver drivers = g_hash_table_lookup(catalogos->Driver, novoid);
  char* name = g_strdup(get_name_driver(drivers));
  return name;
}        

char* get_gender_list_driver(Catalogos catalogos, char* id){
  char* novoid = strsep(&id,"\n");
  Driver driver = g_hash_table_lookup(catalogos->Driver, novoid);
  char* gender = g_strdup(get_gender_driver(driver));
  return gender;
}

int get_idade_list_driver(Catalogos catalogos, char* id){
  char* novoid = strsep(&id,"\n");
  int idade = 0;
  Driver driver = g_hash_table_lookup(catalogos->Driver, novoid);
  if(driver){
    char* birth_day = g_strdup(get_birth_driver(driver));
    Data nascimento = build_data(birth_day);
    Data ref = build_data(g_strdup(ANO));
    int ano_nascimento = get_ano(nascimento);
    int ano_ref = get_ano(ref);
    int mes_nascimento = get_mes(nascimento);
    int mes_ref = get_mes(ref);
    int dia_nascimento = get_dia(nascimento);
    int dia_ref = get_dia(ref);

    idade = (ano_ref) - (ano_nascimento);

    if(mes_nascimento>mes_ref||(mes_nascimento==mes_ref&&dia_nascimento>dia_ref)){
      idade = idade - 1;
    }
  }
  return idade;
}



//-------------------------------------------------------------------------RIDES-DRIVER----------------------------------------------------------------------------------------------------------------

double get_avaliacao_media(Catalogos catalogos, char* id){
  char* novoid = strsep(&id,"\n");
  double total;
  double score;
  int contador=0;
  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;
    if(atoi(novoid) == atoi(get_driver_Rides(ride))){
      score += atof(get_score_driver_Rides(ride));
      contador++;
    }
  }
  
  total = (double)score/contador;

  return total;
}

int get_numero_viagens(Catalogos catalogos, char *id){
  char* novoid = strsep(&id,"\n");
  int contador=0;
  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;
    if(atoi(novoid) == atoi(get_driver_Rides(ride))){
      contador++;
    }
  }
  return contador;
}

double get_total_euferido(Catalogos catalogos, char *id){
  char* novoid = strsep(&id,"\n");
  Driver drivers = g_hash_table_lookup(catalogos->Driver, novoid);
  char* car_class = g_strdup(get_car_class_driver(drivers));

  double km=0;
  float tip = 0;
  double total = 0;

  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;
    
    if(atoi(novoid) == atoi(get_driver_Rides(ride))){
        km = atoi(get_distance_Rides(ride));
        tip = atof(get_tip_Rides(ride));


        if(strcmp("green",car_class)==0){
          total += 4 + 0.79 * km + tip;
        }

        if(strcmp("basic",car_class)==0){
          total += 3.25 + 0.62 * km + tip;
        }
          
        if(strcmp("premium",car_class)==0){
          total += 5.20 + 0.94 * km + tip;
      }
    }
  }

  return total;
}

//-------------------------------------------------------------------------RIDES-USER----------------------------------------------------------------------------------------------------------------

double get_avaliacao_media_user(Catalogos catalogos, char* username){
  char* novousername = strsep(&username,"\n");
  double total;
  double score;
  int contador=0;
  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;
    if(strcmp(novousername,get_user_Rides(ride)) == 0){
      score += atof(get_score_user_Rides(ride));
      contador++;
    }
  }
  total = (double)score/contador;

  return total;
}

int get_numero_viagens_user(Catalogos catalogos, char *username){
  char* novousername = strsep(&username,"\n");
  int contador=0;
  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;
    if(strcmp(novousername,get_user_Rides(ride)) == 0){
      contador++;
    }
  }
  return contador;
}

double get_total_gasto(Catalogos catalogos, char *username){
  char* novousername = strsep(&username,"\n");

  double km=0;
  float tip = 0;
  double total = 0;

  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;

    char* id = get_driver_Rides(ride);

    Driver drivers = g_hash_table_lookup(catalogos->Driver, id);
    char* car_class = g_strdup(get_car_class_driver(drivers));

    if(strcmp(novousername,get_user_Rides(ride)) == 0){
        km = atoi(get_distance_Rides(ride));
        tip = atof(get_tip_Rides(ride));


        if(strcmp("green",car_class)==0){
          total += 4 + 0.79 * km + tip;
        }

        if(strcmp("basic",car_class)==0){
          total += 3.25 + 0.62 * km + tip;
        }
          
        if(strcmp("premium",car_class)==0){
          total += 5.20 + 0.94 * km + tip;
      }
    }
  }

  return total;
}

double get_preco_medio_city(Catalogos catalogos, char *city){
  char* novacity = strsep(&city,"\n");

  double km=0;
  double total = 0;
  int contador=0;

  gpointer key, value;
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalogos->Rides); 
  while(g_hash_table_iter_next(&iter, &key, &value)){
    Rides ride = value;

    char* id = get_driver_Rides(ride);

    Driver drivers = g_hash_table_lookup(catalogos->Driver, id);
    char* car_class = g_strdup(get_car_class_driver(drivers));

    if(strcmp(novacity,get_city_Rides(ride)) == 0){
        km = atoi(get_distance_Rides(ride));
        if(strcmp("green",car_class)==0){
          total += 4 + 0.79 * km;
        }

        if(strcmp("basic",car_class)==0){
          total += 3.25 + 0.62 * km;
        }
          
        if(strcmp("premium",car_class)==0){
          total += 5.20 + 0.94 * km;
      }
      contador++;
    }
  }

  total = total / contador;

  return total;
}

double get_preco_medio_data(Catalogos catalogo, char* data_inicial, char* data_final){

  Data inicial = build_data(data_inicial);
  Data final = build_data(data_final);


  int contador = 0;
  int km = 0;
  double total = 0;

   gpointer key, value;
   GHashTableIter iter;

   g_hash_table_iter_init(&iter, catalogo->Rides); 
   while(g_hash_table_iter_next(&iter, &key, &value)){
     Rides ride = value;
     char* id = get_driver_Rides(ride);

     Driver drivers = g_hash_table_lookup(catalogo->Driver, id);
     char* car_class = g_strdup(get_car_class_driver(drivers));
     char* data_ref = get_date_Rides(ride);

    Data data_a_comparar = build_data(data_ref);
    
     if(compara_datas(data_a_comparar,inicial) && compara_datas(final,data_a_comparar)){
        contador++;
          km = atoi(get_distance_Rides(ride));

          if(strcmp("green",car_class)==0){
            total += 4 + 0.79 * km;
          }

          if(strcmp("basic",car_class)==0){
            total += 3.25 + 0.62 * km;
          }
            
          if(strcmp("premium",car_class)==0){
            total += 5.20 + 0.94 * km;
          }       
    }
  }
  total = total / contador;
return total;
}

double get_distancia_media_city(Catalogos catalogo, char* city, char* data_inicial, char* data_final){
  Data inicial = build_data(data_inicial);
  Data final = build_data(data_final);

  int contador = 0;
  int km = 0;
  double total = 0;

   gpointer key, value;
   GHashTableIter iter;
   g_hash_table_iter_init(&iter, catalogo->Rides); 
   while(g_hash_table_iter_next(&iter, &key, &value)){
     Rides ride = value;
     char* data_ref = get_date_Rides(ride);

    Data data_a_comparar = build_data(data_ref);
    
     if(compara_datas(data_a_comparar,inicial) && compara_datas(final,data_a_comparar) && strcmp(city,get_city_Rides(ride)) == 0){
      km += atoi(get_distance_Rides(ride));
      contador++;
     }
  }
  printf("%i\n",km);
  printf("%i",contador);
  total = (double)km / contador;

  return total;
}

GList* auxquerie2 (Catalogos catalogo){
  GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
    gpointer keyQuery2, valueQuery2;
    GHashTableIter iterQuery2;

    g_hash_table_iter_init(&iterQuery2,catalogo->Rides);
    while(g_hash_table_iter_next(&iterQuery2, &keyQuery2, &valueQuery2)) {
        Rides ride = valueQuery2;
        if(!g_hash_table_contains(map,get_driver_Rides(ride))){
            AUX_DRIVER elem = malloc(sizeof(struct aux_driver));
            elem->id = get_driver_Rides(ride);
            Driver drivers = g_hash_table_lookup(catalogo->Driver, elem->id);
            elem->nome = get_name_driver(drivers);
            elem->avaliacao = atof(get_score_driver_Rides(ride));
            elem->contador = 1;
            elem->viagem_recente = build_data(get_date_Rides(ride));
            g_hash_table_insert(map, elem->id, elem);
        }
        else {
            AUX_DRIVER elem = g_hash_table_lookup(map,get_driver_Rides(ride));
            elem->avaliacao = elem->avaliacao + atof(get_score_driver_Rides(ride));
            Data acomparar = build_data(get_date_Rides(ride));
            elem->viagem_recente = compara_datas(elem->viagem_recente,acomparar) ? elem->viagem_recente : acomparar;
            elem->contador++;
            g_hash_table_insert(map, elem->id, elem);
        }
    }
    
    GList* list = g_hash_table_get_values(map);
    GList* sorted = g_list_sort(list, sort_function_driver);

    return sorted;
}

GList* auxquerie3 (Catalogos catalogo){
  GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
    gpointer keyQuery3, valueQuery3;
    GHashTableIter iterQuery3;

    g_hash_table_iter_init(&iterQuery3,catalogo->Rides);
    while(g_hash_table_iter_next(&iterQuery3, &keyQuery3, &valueQuery3)) {
        Rides ride = valueQuery3;
        if(!g_hash_table_contains(map,get_user_Rides(ride))){
            AUX_USER elem = malloc(sizeof(struct aux_user));
            elem->username = get_user_Rides(ride);
            User user = g_hash_table_lookup(catalogo->user, elem->username);
            elem->nome = get_name_user(user);
            elem->distotal = atoi(get_distance_Rides(ride));
            elem->viagem_recente = build_data(get_date_Rides(ride));
            elem->ativo = strcmp(get_account_status_user(user),"active") == 0 ? 1 : 0;
            g_hash_table_insert(map, elem->username, elem);
        }
        else {
            AUX_USER elem = g_hash_table_lookup(map,get_user_Rides(ride));
            elem->distotal = elem->distotal + atoi(get_distance_Rides(ride));
            Data acomparar = build_data(get_date_Rides(ride));
            elem->viagem_recente = compara_datas(elem->viagem_recente,acomparar) ? elem->viagem_recente : acomparar;
            g_hash_table_insert(map, elem->username, elem);
        }
    }
    
    GList* list = g_hash_table_get_values(map);
    GList* sorted = g_list_sort(list, sort_function_user);
    GList* final = remove_users(sorted);

    return final;
}