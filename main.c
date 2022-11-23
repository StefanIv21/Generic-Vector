#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

int lungime_vector (void *add , int len) ///fuctie care calculeaza lungimea actuala a vectorului arr
{
	int lungime = 0;
	for(int i = 0; i < len; i++ )
	{
		lungime += sizeof(head) + ((head*)add)->len;
     	add = add + sizeof(head) + ((head*)add)->len;
	}
	return lungime;
}

int add_last (void **arr , int *len , data_structure *data)
{
    int lungime = 0;
	if(*len == 0)
	{
		*arr = malloc( sizeof(head) + data->header->len );
		if(*arr == NULL)
			return -1;
	}
	void *parcurgere = *arr; //"parcruge" retine adresa vectorului arr 
	if(*len !=0)
	{
		lungime = lungime_vector(*arr, *len); //calculez lungimea pt a stii cat trebuie realocat
    	*arr = realloc(*arr , lungime + sizeof(head) + data->header->len);
		if(*arr == NULL)
			return -1;
 		parcurgere = *arr + lungime;	
	}
	//copiez datele din data in arr
	memcpy(parcurgere, data->header, sizeof(head));
	parcurgere = parcurgere + sizeof(head);
	memcpy(parcurgere, data->data, data->header->len);
	free(data->data);
	free(data->header);
	free(data);
    (*len)++;
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
    if(index < 0)
      return -1;
	if(index > *len)
	  return add_last(arr, len, data);
	int lungime_actuala = lungime_vector(*arr, *len); //lungimea actuala a vectorului
	*arr = realloc(*arr, lungime_actuala + sizeof(head) + data->header->len);
	int inainte_elem = lungime_vector(*arr, index); // lungimea inainte de elemetul unde trebuie sa adaugam
	int cate_raman = lungime_actuala - inainte_elem;
    void *copie = NULL; //vector auxlir unde pun datele de dupa locul de inserare cerut
	void *inainte = *arr + inainte_elem; //adresa vectorului add de unde trebuie adaugat
	copie = malloc(cate_raman);
	memcpy(copie, inainte, lungime_actuala-inainte_elem); 
	memcpy(inainte ,data->header ,sizeof(head));//adaug in arr datele cerute
	inainte = (char*)inainte + sizeof(head);
	memcpy(inainte, data->data, data->header->len);
  	inainte = (char*)inainte + data->header->len;
	memcpy(inainte, copie, cate_raman);// adaug in arr datele de dinainte inserarii 
	free(data->data);
	free(data->header);
	free(data);
	free(copie);
  	(*len)++;
 	 return 0;
}
void find(void *data_block, int len, int index) 
{
	if(index < 0)
		return ;
	if(index > len)
		return ;
	while(index > 0) //parcurg vectorul pana la indexul cerut
	{
     	data_block = (char*)data_block + sizeof(head) + ((head*)data_block)->len;
		index--;
	}
	//variabile pentru a retine datele ce trebuiesc afisate
	char *persoana1;
	char *persoana2;
	head *tip_si_len = data_block;
	void *bani1;
	void *bani2;
	printf("Tipul %d\n", tip_si_len->type);
	if(tip_si_len->type == 1)
	{
		persoana1 = data_block + sizeof(head);
		bani1 = persoana1 + strlen(persoana1) + 1;
		bani2 = persoana1 + strlen(persoana1) + 1 + sizeof(int8_t);
		persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int8_t) + sizeof(int8_t);
		printf("%s pentru %s\n", persoana1, persoana2);
		printf("%"PRId8"\n", *((int8_t *)bani1));
		printf("%"PRId8"\n", *((int8_t *)bani2));
		printf("\n");
	}
	if(tip_si_len->type == 2)
	{
		persoana1 = data_block + sizeof(head);
		bani1 = persoana1 + strlen(persoana1) + 1;
		bani2 = persoana1 + strlen(persoana1) + 1 + sizeof(int16_t);
		persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int16_t) + sizeof(int32_t);
		printf("%s pentru %s\n", persoana1, persoana2); 
		printf("%"PRId16"\n", *((int16_t *)bani1));
		printf("%"PRId16"\n", *((int16_t *)bani2));
		printf("\n");
	}
		if(tip_si_len->type ==3)
	{
		persoana1 = data_block + sizeof(head);
		bani1 = persoana1 + strlen(persoana1) + 1;
		bani2 = persoana1 + strlen(persoana1) + 1 + sizeof(int32_t);
		persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int32_t) + sizeof(int32_t);
		printf("%s pentru %s\n", persoana1, persoana2);
		printf("%"PRId32"\n", *((int32_t *)bani1));
		printf("%"PRId32"\n", *((int32_t *)bani2));
		printf("\n");
	}
}
  
int delete_at(void **arr, int *len, int index)
{
	if(index < 0)
	   return -1;
	if(index  > *len)
		return -1;
	int inainte_elem = lungime_vector(*arr, index); 
	int lungime_act = lungime_vector(*arr, *len);
	int dupa_elem = lungime_vector(*arr, index + 1);
	int cate_trb_sterse = dupa_elem-inainte_elem;
	int cate_raman = lungime_act-dupa_elem;
	void *inainte = *arr + inainte_elem; //adresa vectorului arr de unde trebuie sters 
	void *add = NULL;  //vector auxlir unde pun datele de dupa locul de stergere cerut 
	void *dupa = (char*)*arr + dupa_elem; //adresa vectorului arr de dupa elementul ce trebuie sters
	add = malloc(cate_raman);
	memcpy(add,dupa, cate_raman);//pun in arr  datele de dupa elementul ce trebuie sters 
	memcpy(inainte, add, cate_raman); //suprascriu datele vechi cu cele noi
	*arr = realloc(*arr, lungime_act - cate_trb_sterse); //
	free(add);
    (*len)--;
    return 0;
}

void print(void *arr,int len)
{
	while(len>0)
	{
			//variabile pentru a retine datele ce trebuiesc afisate
		void *bani1;
		void *bani2;
		char *persoana1;
		char *persoana2;
		head *tip_si_len = arr;
		printf("Tipul %d\n", tip_si_len->type);
		if(tip_si_len->type == 1)
		{
			persoana1 = arr + sizeof(head);
			bani1 = persoana1 + strlen(persoana1) + 1;
			bani2 = persoana1 + strlen(persoana1) + 1 + sizeof(int8_t);
			persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int8_t) + sizeof(int8_t);
			printf("%s pentru %s\n", persoana1, persoana2);
			printf("%"PRId8"\n", *((int8_t *)bani1));
			printf("%"PRId8"\n", *((int8_t *)bani2));
			printf("\n");
	}
		if(tip_si_len->type == 2)
		{
			persoana1 = arr + sizeof(head);
			bani1 = persoana1+strlen(persoana1) + 1;
			bani2 = persoana1+strlen(persoana1) + 1 + sizeof(int16_t);
			persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int16_t) + sizeof(int32_t);
			printf("%s pentru %s\n", persoana1, persoana2);
			printf("%"PRId16"\n", *((int16_t *)bani1));
			printf("%"PRId16"\n", *((int32_t *)bani2));
			printf("\n");
		}
		if(tip_si_len->type == 3)
		{
			persoana1 = arr + sizeof(head);
			bani1 = persoana1 + strlen(persoana1) + 1;
			bani2 = persoana1 + strlen(persoana1) + 1 + sizeof(int32_t);
			persoana2 = persoana1 + strlen(persoana1) + 1 + sizeof(int32_t) + sizeof(int32_t);
			printf("%s pentru %s\n", persoana1, persoana2);
			printf("%"PRId32"\n", *((int32_t *)bani1));
			printf("%"PRId32"\n", *((int32_t *)bani2));
			printf("\n");
		}
		arr = (char*)arr + sizeof(head) + tip_si_len->len;
		len--;
  	}
}
	
int main() 
	{
	void *arr = NULL;
	int len = 0;
	while(1)
	{
		char linie[256]; //buffer unde retin linia
		char linie2[256]; //alt buffer unde retin linia
		fgets(linie, 256, stdin);
		strcpy(linie2, linie);
		char *token = strtok(linie, "\n ");
		if(strcmp (token, "insert") == 0) //iau cu strtok primul cuvant pentru a mi da seama ce comanda trebuie sa aplic
	 	{ 
			unsigned char type; 
			int dim_pers1 = 0; //calculez dimensiunea primului cuvant
			int dim_pers2 = 0; ///calculez dimensiunea ultimului cuvant
			token = strtok(NULL,"\n ");
			type = atoi(token);
			unsigned int lungime = 0; //calculez dimensiuna persoanei care dedica,banii si persoana pentru care se face dedicatia
			token = strtok (NULL, "\n ");
			dim_pers1 = strlen(token);
			token = strtok (NULL, "\n ");
			token = strtok (NULL, "\n ");
			token = strtok (NULL, "\n ");
			dim_pers2 = strlen(token);
			if(type == 1)
			{
				lungime  += dim_pers1 + 1 + dim_pers2 + 1 + 2 * sizeof(int8_t);
			}
			if(type == 2)
				lungime += dim_pers1+1 + dim_pers2+1 + sizeof(int16_t) + sizeof(int32_t);
			if(type == 3)
				lungime += dim_pers1 + 1 + dim_pers2 + 1 + 2 * sizeof(int32_t);	
			data_structure *data = malloc(sizeof(data_structure)); //pointer la structura data_structure
			data->header = malloc(sizeof(head));
			//pun tipul inserarii si lungimea in data_structure
			data->header->type  = type; 
			data->header->len = lungime;
			data->data = malloc(data->header->len);
			token = strtok (linie2,"\n ");
			token = strtok (NULL,"\n ");
			token = strtok (NULL,"\n ");
			char *dedica = malloc (strlen(token) + 1); //variabila unde pun numele primei persoane si aloc pentru dimensiunea lui
			strcpy(dedica, token);
			dedica[strlen(dedica)] = '\0';
			memcpy(data->data, dedica, strlen(dedica)+1);//pun bytii  de la variabila "dedica" in pointerul de tip data_structure
			void *parcurgere = data->data; //retine adresa variabilei de tip data_structure
			parcurgere += strlen(dedica) + 1; //parcurg structura data_strcuture  pentru a nu suprascrie datele 
			if(type == 1)
			{	
				int8_t *ban1; //variabila unde pun datele  primei bancnote 
				int8_t *ban2;//variabila unde pun datele  celei de a doua bancnota
				ban1 = malloc (sizeof(int8_t));
				ban2 = malloc (sizeof(int8_t));
				*ban1 = atoi (strtok(NULL, "\n "));
				*ban2 = atoi (strtok(NULL, "\n "));
				//pun bytii  din vairabile  in pointerul de tip data_structuree
				memcpy(parcurgere, ban1, sizeof(int8_t));
				parcurgere +=sizeof(int8_t);
				memcpy(parcurgere, ban2, sizeof(int8_t));
				parcurgere += sizeof(int8_t);
				free(ban1);
				free(ban2);
			}
			if(type == 2)
			{	
				int16_t *ban1; //variabila unde pun datele  primei bancnote 
				int32_t *ban2;//variabila unde pun datele  celei de a doua bancnota
				ban1 = malloc (sizeof(int16_t));
				ban2 = malloc (sizeof(int32_t));
				*ban1 = atoi (strtok(NULL, "\n "));
				*ban2 = atoi (strtok(NULL, "\n "));
					//pun bytii  din vairabile  in pointerul de tip data_structuree
				memcpy(parcurgere, ban1, sizeof(int16_t));
				parcurgere +=sizeof(int16_t);
				memcpy(parcurgere, ban2, sizeof(int32_t));
				parcurgere += sizeof(int32_t);
				free(ban1);
			    free(ban2);
			}
			if(type == 3)
			{	
				int32_t *ban1;//variabila unde pun datele  primei bancnote 
				int32_t *ban2;;//variabila unde pun datele  celei de a doua bancnota
				ban1 = malloc (sizeof(int32_t));
				ban2 = malloc (sizeof(int32_t));
				*ban1 = atoi (strtok(NULL, "\n "));
				*ban2 = atoi( strtok(NULL, "\n "));
				//pun bytii  din vairabile  in pointerul de tip data_structuree
				memcpy(parcurgere, ban1, sizeof(int32_t));
				parcurgere +=sizeof(int32_t);
				memcpy(parcurgere, ban2, sizeof(int32_t));
				parcurgere += sizeof(int32_t);
				free(ban1);
				free(ban2);
			}
			token = strtok(NULL, "\n ");
			char *sededica = malloc (strlen(token) + 1);//variabila unde pun numele ultimei  persoane si aloc pentru dimensiunea lui
			strcpy(sededica,token);
			sededica[strlen(sededica)] = '\0';
			memcpy(parcurgere, sededica, strlen(sededica) + 1); //pun bytii  de la variabila "dedica" in pointerul de tip data_structure
			add_last(&arr ,&len, data); 
			free(dedica);
			free(sededica);
        }
		if(strstr(token, "print"))
	 	{
		 	print(arr,len);
	 	}
		if(strstr(token, "exit"))
	  	{
	   		break;
	  	}
	    if(strstr(token, "find"))
		{
			int index;
			token = strtok(NULL, "\n ");
			index = atoi(token);
			find(arr, len, index);
	 	}
	  	if(strstr(token, "delete_at"))
	 	{
		 	int index;
	     	token = strtok(NULL, "\n ");
			index = atoi(token);
			delete_at(&arr, &len, index);
	 	}
	  	if(strstr(token,"insert_at"))
	 	{
			//acelesi comenzi ca si la  "insert"
			int index;
			token = strtok( NULL,"\n ");
			index = atoi (token);
			unsigned char type;
			unsigned int lungime = 0;
			int dim_pers1=0;
			int dim_pers2=0;
			token = strtok (NULL,"\n ");
			type = atoi (token);
			token = strtok (NULL,"\n ");
			dim_pers1 = strlen(token);
			token = strtok (NULL,"\n ");
			token = strtok (NULL,"\n ");
			token = strtok (NULL,"\n ");
			dim_pers2 = strlen(token);
			if(type == 1)
				lungime += dim_pers1 + 1 + dim_pers2 + 1 + 2*sizeof(int8_t);
			if(type == 2)
				lungime += dim_pers1+1+dim_pers2 + 1 + sizeof(int16_t) + sizeof(int32_t);
			if(type == 3)
				lungime += dim_pers1 + 1 + dim_pers2 + 1 + 2*sizeof(int32_t);	
			data_structure *data = malloc(sizeof(data_structure));
			data->header = malloc(sizeof(head));
			data->header->len = lungime;
			data->header->type = type;
			data->data = malloc (data->header->len);
			token = strtok (linie2, "\n ");
			token = strtok (NULL, "\n ");
			token = strtok (NULL, "\n ");
			token = strtok (NULL, "\n ");
			char *dedica = malloc (strlen(token)+1);
			strcpy(dedica, token);
			dedica[strlen(dedica)] = '\0';
			memcpy(data->data, dedica, strlen(dedica) + 1);
			void* parcurgere = data->data;
			parcurgere += strlen(dedica) + 1;
			if(type == 1)
			{	
				int8_t *ban1;
				int8_t *ban2;
				ban1 = malloc (sizeof(int8_t));
				ban2 = malloc (sizeof(int8_t));
				*ban1 = atoi (strtok(NULL,"\n "));
				*ban2 = atoi (strtok(NULL,"\n "));
				memcpy(parcurgere, ban1, sizeof(int8_t));
				parcurgere += sizeof(int8_t);
				memcpy(parcurgere, ban2, sizeof(int8_t));
				parcurgere += sizeof(int8_t);
			    free(ban1);
			    free(ban2);
			}
			if(type == 2)
			{	
				int16_t *ban1;
				int32_t *ban2;
				ban1 = malloc (sizeof(int16_t));
				ban2 = malloc (sizeof(int32_t));
				*ban1 = atoi (strtok(NULL,"\n "));
				*ban2 = atoi (strtok(NULL,"\n "));
				memcpy(parcurgere, ban1, sizeof(int16_t));
				parcurgere += sizeof(int16_t);
				memcpy(parcurgere, ban2, sizeof(int32_t));
				parcurgere += sizeof(int32_t);
				free(ban1);
				free(ban2);
			}
			if(type == 3)
			{	
				int32_t *ban1;
				int32_t *ban2;
				ban1 = malloc (sizeof(int32_t));
				ban2=malloc (sizeof(int32_t));
				*ban1 = atoi(strtok(NULL, "\n "));
				*ban2 = atoi(strtok(NULL, "\n "));
				memcpy(parcurgere, ban1, sizeof(int32_t));
				parcurgere += sizeof(int32_t);
				memcpy(parcurgere, ban2 ,sizeof(int32_t));
				parcurgere += sizeof(int32_t);
				free(ban1);
				free(ban2);
			}
			token = strtok(NULL,"\n ");
			char *sededica = malloc(strlen(token) + 1);
			strcpy(sededica, token);
			sededica[strlen(sededica)] = '\0';
			memcpy(parcurgere, sededica, strlen(sededica) + 1);
			add_at(&arr,&len, data, index);
			free(dedica);
			free(sededica);
	 	}
	}
	if(arr!=NULL)
		free(arr);
	return 0;
}
