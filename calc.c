/* testcalc.c zum Testen der Belegaufgabe 4 */
#include <stdio.h> // fuer printf ()
#include <stdlib.h> // fuer free
// Deklaration der Aufgabenfunktion
char *preccalc(const char *const term[], int size);
unsigned long Get_String_Length(const char* InString);
double power(double base, double expoente);

// int main (int argc, const char *const *args){
//     const char text[] = "1+1"; 
//     argc = 3;
//     if ((argc == 0) || (argc % 2 != 0)){ // gerade Parameterzahl >0 uebergeben ?
//         return -1; // ( Parameter beginnen mit Programmnamen )
//     }
//     //char *result = preccalc(&text[1], argc-1);
//     char *result = preccalc(&args[1], argc-1);
//     printf (" Ergebnis :\"%s\".\n",result); // gibt Ergebnis aus
//     //convert_String_To_Array(&text);
//     free (result);
//     return 0; // 0 bedeutet alles okay
// }

char *preccalc(const char *const term[], int size){

    char *erro = "eingabe nicht korrekt";
    for (int i = 0; i < size; i++){
        if(*term[i] == ' '){ 
            return erro;
        }else if(*term[i] == '.'){ 
            return erro;
        }else if(*term[i] == ',' && (*term[i-1] < 48 || *term[i-1] > 57)){
            return erro;
        }else if(*term[i] == '\''){
            return erro;
        }else if(*term[i] == '0' && (*term[i-1] == '+' || *term[i-1] == '-') && (*term[i+1] > 48 || *term[i-1] < 57)){
            return erro;
        }else if(*term[i] == '0' && *term[i+1] == '0' && (*term[i+2] == '+' || *term[i+2] == '-')){
            return erro;
        }else if(*term[i] == 0 && (*term[i-1] == '-' || *term[i-1] == '+') && (*term[i+1] == '+' || *term[i+1] == '-')){
            return erro;
        }
    }

    char *res = calloc(size, sizeof(char));
    int count = 0;
    
    // count how many + and - are for size of int array
    for (int i = 0; i < size; i++){
            if(*term[i] == '+' || *term[i] == '-'){ 
            count++;
        }
    }
    
    double numbers[count+1];
    int position_to_put_the_numbers = 0;
    int count_numbers_after_comma = 0;
    int start = 0;
    double sum = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;
    int count6 = 0;
    int res_count = 0;
    int check_if_is_comma = 0;
    int position_to_sum = 0;
    int count_numbers_befor_dividing = 0;
    
    for (int i = 0; i <= size; i++){

        //if the number is not decimal
        if(*term[i] == '+' || *term[i] == '-' || *term[i] == '\0'){
            count6 = i;
            if(check_if_is_comma == 0){
                while(*term[count5+1] != '+' && *term[count5+1] != '-' && *term[count5+1] != '\0'){ 
                    res[count4] = *term[count5+1];
                    count4++;
                    start++;
                    count5++;
                }
                numbers[position_to_put_the_numbers] = atof(res);
                position_to_put_the_numbers++;
                count4 = 0;
            }
            check_if_is_comma = 0;
            count5 = i;
            count6++;
        }
        
        //count how many numbers are after the comma to divide in the future
        if(*term[i] == ','){
             count_numbers_after_comma = 0;
            int j = i;
            
            while(*term[j] != '+' && *term[j] != '-' && *term[j] != '\0'){
                count_numbers_after_comma++;
                j++;
            }
            count_numbers_after_comma -= 1;

            //put every separete numbers in the res. Bs. 1234+4896 only put 1234 and convert the 1234 to a int array
            count3 = start;
            while(*term[count6] != '+' && *term[count6] != '-' && *term[count6] != '\0'){
                if(*term[count2] == ','){
                    count2++;
                    start++;
                    count3++;
                    count6++;
                }else{
                    res[res_count] = *term[count2];
                    res_count++;
                    start++;
                    count2++;
                    count3++;
                    count_numbers_befor_dividing++;
                    count6++;
                }
            }
            count6++;
            count2 = count6;
            //convert the number in int an put inside a int array
            numbers[position_to_put_the_numbers] = atof(res);
            numbers[position_to_put_the_numbers] /= power(10, count_numbers_after_comma);
            position_to_put_the_numbers++;
            check_if_is_comma = 1;
            res_count = 0;
        }
        //turn all numbrs from res to 0
        for (int i = 0; i < start; i++){
            res[i] = 0;
        }
    }

    //adding and subtracting numbers 
    sum = numbers[0];
    for(int i = 0; i <= size; i++){
        if(*term[i] == '+'){
            ++position_to_sum;
            sum = sum + numbers[position_to_sum];
        }else if(*term[i] == '-'){
            ++position_to_sum;
            sum = sum - numbers[position_to_sum];
        }
    }

    // convert the sum to string so i can return 
    sprintf(res, "%f", sum);
    return res;
}

double power(double base, double expoente){
  if(expoente == 0)
    return 1;
  else
    return base * power(base, expoente - 1);
}

unsigned long Get_String_Length(const char* InString)
{
    if(InString[0] == 0){ 
        return 1;
    }
    return 1 + Get_String_Length(InString + 1);
}
