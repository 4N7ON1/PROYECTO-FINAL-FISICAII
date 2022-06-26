#include <stdio.h>
#include <stdlib.h>

struct Elemento{
    int id;
    char nome[30];
    float calor_especifico;
    float temp_fusao;
    float temp_ebulicao;
    float massa;
    float temp_atual;
};

typedef struct Elemento El;

static El el[13] = {{1,"Hielo",0.53,273,373},
                    {2,"Agua",1,273,373},
                    {3,"Etanol",0.58,159,351},
                    {4,"Mercurio",0.033,234,629},
                    {5,"Vidro",0.2,1523,3000},
                    {6,"Granito",0.19,1488,3000},
                    {7,"Latón",0.092,1173,3000},
                    {8,"Alumínio",0.215,933,2743},
                    {9,"Cobre",0.0923,1356,2868},
                    {10,"Plata",0.0564,1235,2323},
                    {11,"Tungsteno",0.0321,3695,5828},
                    {12,"PLOMO",0.0305,601,2017}};

El ProcuraElemento(int id){
    for(int i = 0; i < 13 ; i++){
        if(el[i].id == id) return el[i];
        else continue;
    }
}

void TemperaturaFinal(El x , El y){
    float TF;
    int cont = 0;
    //TF = (m1*c1*t1+m2*c2*t2)/(m1*c1+m2*c2);
    TF = (x.massa*x.calor_especifico*x.temp_atual+y.massa*y.calor_especifico*y.temp_atual)/(x.massa*x.calor_especifico+y.massa*y.calor_especifico);

    //Verificando si houve transformação em x;
    if(x.temp_atual < x.temp_fusao){
        if(TF < x.temp_fusao) cont++;;
    }
    else if(x.temp_fusao < x.temp_atual && x.temp_atual < x.temp_ebulicao){
        if(x.temp_fusao < TF && TF < x.temp_ebulicao) cont++;
    }
    else if(x.temp_ebulicao < x.temp_atual){
        if(x.temp_ebulicao < TF) cont++;
    }

    //Verificando si houve transformação em y;
    if(y.temp_atual < y.temp_fusao){
        if(TF < y.temp_fusao) cont++;;
    }
    else if(y.temp_fusao < y.temp_atual && y.temp_atual < y.temp_ebulicao){
        if(y.temp_fusao < TF && TF < y.temp_ebulicao) cont++;
    }
    else if(y.temp_ebulicao < y.temp_atual){
        if(y.temp_ebulicao < TF) cont++;
    }

    if(cont == 2){
        printf("La temperatura de equilibrio entre los elementos es: %.2f K",TF);
    }else{
        printf("¡HAY CAMBIOS DE FASE!");
    }

}

El trata_erro(El x){
    if(x.id == 1 && x.temp_atual > x.temp_fusao){
        do{
        printf(" --------------- ERROR! ----------------\n");
        printf("El elemento [%s] no existe a esta temperatura (%.2fK)!\n",x.nome,x.temp_atual);
        printf("Ingrese la temperatura del elemento [%s] nuevamente: ",x.nome);
        scanf("%f",&x.temp_atual);
        printf("\n -------------------------------------- \n");
        }while(x.temp_atual > x.temp_fusao);
        return x;
    }
    else if(x.id == 2 && x.temp_atual < x.temp_fusao){
        do{
        printf(" --------------- ERROR! ----------------\n");
        printf("El elemento [%s] no existe a esta temperatura (%.2fK)!\n",x.nome,x.temp_atual);
        printf("Ingrese la temperatura del elemento [%s] nuevamente: ",x.nome);
        scanf("%f",&x.temp_atual);
        printf("\n -------------------------------------- \n");
        }while(x.temp_atual < x.temp_fusao);
    }
    else return x;
}



int main(){

    char resp;

    do{
    El x , y;
    int id1 , id2;

    printf("INGRESE EL NUMERO DEL PRIMER ELEMENTO:\n1-Hielo\n"
                                                  "2-Agua \n"
                                                  "3-Etanol \n"
                                                  "4-Mercurio \n"
                                                  "5-Vidro \n"
                                                  "6-Granito \n"
                                                  "7-Laton \n"
                                                  "8-Aluminio \n"
                                                  "9-Cobre \n"
                                                  "10-Plata \n"
                                                  "11-Tungsteno \n"
                                                  "12-Plomo \n\n");
    printf("RESPUESTA.LIC LEYNA: ");
    scanf("%d",&id1);

    printf("INGRESE EL NUMERO DEL SEGUNDO ELEMENTO: \n1-Gelo \n"
                                                  "2-Agua \n"
                                                  "3-Etanol \n"
                                                  "4-Mercurio \n"
                                                  "5-Vidro \n"
                                                  "6-Granito \n"
                                                  "7-Laton \n"
                                                  "8-Aluminio \n"
                                                  "9-Cobre \n"
                                                  "10-Plata \n"
                                                  "11-Tungsteno \n"
                                                  "12-Plomo \n\n");
    printf("RESPUESTA.LIC LEYNA: ");
    scanf("%d",&id2);

    x = ProcuraElemento(id1);
    y = ProcuraElemento(id2);

    printf("\n-------------------------------------- \n");
    printf("ATENCION: MASA EN GRAMOS!");
    printf("\n-------------------------------------- \n");
    //Coletando as massas
    printf("Introduzca la masa del elemento 1[%s]: ",x.nome);
    scanf("%f",&x.massa);
    printf(" Introduzca la masa del elemento 2[%s]: ",y.nome);
    scanf("%f",&y.massa);

    printf("\n -------------------------------------- \n");
    printf("ATENCION:  TEMPERATURA KELVIN");
    printf("\n -------------------------------------- \n");
    //Coletando as temperaturas
    printf("Introduzca la temperatura del elemento 1[%s]: ",x.nome);
    scanf("%f",&x.temp_atual);
    printf("Introduzca la temperatura del elemento 2[%s]: ",y.nome);
    scanf("%f",&y.temp_atual);
    printf("\n -------------------------------------- \n");

    x = trata_erro(x);
    y = trata_erro(y);

    TemperaturaFinal(x , y);

    printf("\n\n Quiere tomar otra medida? [s/n]\n");
    printf("-> ");
    scanf("%s",&resp);
    printf("\n\n\n");


    }while(resp == 's' || resp == 'S');

}